/*
 *  TEST BENCH COPY CODE 
 */

#include "base_testbench.h"

#define TB_NAME ControlTestbench

Vcontrol *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->op = 0;
        top->eq = 0;
    }

    // no clock needed, purely combinational module
};


// Test ADDI instruction decoding
TEST_F(TB_NAME, AddiDecodeTest)
{
    top->op = 0b0010011; // ADDI opcode
    top->eq = 0;
    top->eval();

    EXPECT_EQ(top->RegWrite, 1);
    EXPECT_EQ(top->ALUctrl, 0b000); // add
    EXPECT_EQ(top->ALUsrc, 1);      // immediate
    EXPECT_EQ(top->Immsrc, 0);      // I-type
    EXPECT_EQ(top->PCsrc, 0);       // no branch
}


//test BNE instruction when eq = 0
TEST_F(TB_NAME, BneBranchTaken)
{
    top->op = 0b1100011; // BNE opcode
    top->eq = 0;
    top->eval();

    EXPECT_EQ(top->RegWrite, 0);
    EXPECT_EQ(top->ALUctrl, 0b001);
    EXPECT_EQ(top->ALUsrc, 0);
    EXPECT_EQ(top->PCsrc, 1);
}


//test BNE instruction when eq = 1
TEST_F(TB_NAME, BneBranchNotTaken)
{
    top->op = 0b1100011; // BNE opcode
    top->eq = 1;
    top->eval();

    EXPECT_EQ(top->RegWrite, 0);
    EXPECT_EQ(top->ALUctrl, 0b001); 
    EXPECT_EQ(top->ALUsrc, 0);
    EXPECT_EQ(top->Immsrc, 1);
    EXPECT_EQ(top->PCsrc, 0);
}


//unknown opcode
TEST_F(TB_NAME, DefaultCaseTest)
{
    top->op = 0b0000000; // not ADDI or BNE
    top->eq = 0;
    top->eval();

    EXPECT_EQ(top->RegWrite, 0);
    EXPECT_EQ(top->ALUctrl, 0b000);
    EXPECT_EQ(top->ALUsrc, 0);
    EXPECT_EQ(top->Immsrc, 0);
    EXPECT_EQ(top->PCsrc, 0);
}



int main(int argc, char **argv)
{
    top = new Vdut;
    tfp = new VerilatedVcdC;

    Verilated::traceEverOn(true);
    top->trace(tfp, 99);
    tfp->open("waveform.vcd");

    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();

    top->final();
    tfp->close();

    delete top;
    delete tfp;

    return res;
}
