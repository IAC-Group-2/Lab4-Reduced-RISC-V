/*
 *  TEST BENCH COPY CODE 
 */

#include "base_testbench.h"

#define TB_NAME RegfileTestbench

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->clk = 0;
        top->ad1 = 0;
        top->ad2 = 0;
        top->ad3 = 0;
        top->wd3 = 0;
        top->we3 = 0;
    }

    void tick()
    {
        top->clk = 0;
        top->eval();
        top->clk = 1;
        top->eval();
    }
};




//writing to a register
TEST_F(TB_NAME, WriteRegisterTest)
{
    top->ad3 = 5;      //address
    top->wd3 = 1234;   //data
    top->we3 = 1;      //write en

    tick();  //posedge write

    top->ad1 = 5;
    top->eval();

    EXPECT_EQ(top->rd1, 1234);
}


//test simultaneous read of two registers
TEST_F(TB_NAME, DualReadTest)
{
    //reg 3 = 1111
    top->ad3 = 3;
    top->wd3 = 1111;
    top->we3 = 1;
    tick();

    //reg 7 = 2222
    top->ad3 = 7;
    top->wd3 = 2222;
    top->we3 = 1;
    tick();

    //read both
    top->ad1 = 3;
    top->ad2 = 7;
    top->eval();

    EXPECT_EQ(top->rd1, 1111);
    EXPECT_EQ(top->rd2, 2222);
}


//write disabled so no memory change
TEST_F(TB_NAME, WriteEnableOffTest)
{
    //addr 4 write
    top->ad3 = 4;
    top->wd3 = 5555;
    top->we3 = 1;
    tick();

    //overwrite with write disabled
    top->ad3 = 4;
    top->wd3 = 9999;
    top->we3 = 0;
    tick();

    top->ad1 = 4;
    top->eval();

    EXPECT_EQ(top->rd1, 5555);
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
