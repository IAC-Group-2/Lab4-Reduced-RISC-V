#include "base_testbench.h"

#define TB_NAME PCRegTestbench 

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->clk   = 0;
        top->rst   = 0;
        top->PCsrc = 0;
        top->ImmOp = 0;
    }

    // toggle clock
    void tick()
    {
        top->clk = 0;
        top->eval();
        top->clk = 1;
        top->eval();
    }
};



//reset behaviour: PC_out should go to 0
TEST_F(TB_NAME, ResetClearsPC)
{
    top->rst = 1;
    tick();
    EXPECT_EQ(top->PC_out, 0);

    top->rst = 0; //release reset
}


//PC should increment by 4 when PCsrc = 0
TEST_F(TB_NAME, PCIncrementsBy4)
{
    top->PCsrc = 0;
    top->ImmOp = 0;

    uint32_t prev = top->PC_out;

    tick();   // clock
    EXPECT_EQ(top->PC_out, prev + 4);

    prev = top->PC_out;

    tick();
    EXPECT_EQ(top->PC_out, prev + 4);
}


//PC should branch: PC_out = PC_out + ImmOp
TEST_F(TB_NAME, PCBranchesCorrectly)
{
    //set PC at a known value
    top->rst = 1;
    tick();
    top->rst = 0;

    //PC = 4
    top->PCsrc = 0;
    tick();

    EXPECT_EQ(top->PC_out, 4);

    //trigger branch (+16)
    top->ImmOp = 16;   
    top->PCsrc = 1;

    tick();
    EXPECT_EQ(top->PC_out, 4 + 16);
}


//branch should not trigger when PCsrc=0
TEST_F(TB_NAME, BranchIgnoredWhenPCsrcLow)
{

    top->rst = 1;
    tick();
    top->rst = 0;

    //PC = 4
    top->PCsrc = 0;
    tick();
    EXPECT_EQ(top->PC_out, 4);

    //try to branch but PCsrc=0
    top->ImmOp = 100;
    top->PCsrc = 0;

    tick();
    EXPECT_EQ(top->PC_out, 8);   
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
