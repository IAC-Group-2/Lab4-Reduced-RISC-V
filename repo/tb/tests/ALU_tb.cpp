/*
 *  TEST BENCH COPY CODE 
 */

#include "base_testbench.h"

#define TB_NAME ALUTestbench 

Valu *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->in0 = 0;
        top->in1 = 0;
        top->ctrl = 0;
        // outputs: out, eq
    }
};


// ADD
TEST_F(TB_NAME, AddWorksTest)
{
    top->ctrl = 0b000;   
    top->in0 = 10;
    top->in1 = 20;

    top->eval();

    EXPECT_EQ(top->out, 30);
    EXPECT_EQ(top->eq, 0);
}

// SUB
TEST_F(TB_NAME, SubWorksTest)
{
    top->ctrl = 0b001;   
    top->in0 = 20;
    top->in1 = 5;

    top->eval();

    EXPECT_EQ(top->out, 15);
}

// AND
TEST_F(TB_NAME, AndWorksTest)
{
    top->ctrl = 0b010;   
    top->in0 = 0b1100;
    top->in1 = 0b1010;

    top->eval();

    EXPECT_EQ(top->out, 0b1000);
}

// OR
TEST_F(TB_NAME, OrWorksTest)
{
    top->ctrl = 0b011;   
    top->in0 = 0b1100;
    top->in1 = 0b0110;

    top->eval();

    EXPECT_EQ(top->out, 0b1110);
}

// SLT (a < b)
TEST_F(TB_NAME, SltWorksTest)
{
    top->ctrl = 0b101;   
    top->in0 = 5;
    top->in1 = 9;

    top->eval();

    EXPECT_EQ(top->eq, 1);
}

// undefined opcode
TEST_F(TB_NAME, DefaultCaseTest)
{
    top->ctrl = 0b111;   
    top->in0 = 1234;
    top->in1 = 5678;

    top->eval();

    EXPECT_EQ(top->out, 0);
    EXPECT_EQ(top->eq, 0);
}


int main(int argc, char **argv)
{
    top = new Valu;
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
