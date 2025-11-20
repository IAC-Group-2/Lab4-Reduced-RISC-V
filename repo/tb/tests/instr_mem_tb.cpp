#include "base_testbench.h"
#include <fstream>

#define TB_NAME InstrMemTestbench

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->A = 0;
    }
};


// ------------------- HELPER --------------------

// Create a small test ROM file to be read by $readmemh
void create_hex_file()
{
    std::ofstream hex("../rtl/program.hex");
    /*
    Instr0 = 0x11223344
    Instr1 = 0xAABBCCDD
    */

    //ins 0
    hex << "44\n33\n22\n11\n"; // 0x11223344

    //ins 1
    hex << "DD\nCC\nBB\nAA\n"; // 0xAABBCCDD

    //fill rest with zeros
    for (int i = 8; i < 1024; i++)
        hex << "00\n";

    hex.close();
}

-


//ins 0 read properly
TEST_F(TB_NAME, ReadInstruction0)
{
    create_hex_file();

    top->A = 0;
    top->eval();

    EXPECT_EQ(top->RD, 0x11223344u);
}


//ins 1 read properly
TEST_F(TB_NAME, ReadInstruction1)
{
    create_hex_file();

    top->A = 4;   //index = A[9:2] = 1 so 4
    top->eval();

    EXPECT_EQ(top->RD, 0xAABBCCDDu);
}


//check an unused location returns zero
TEST_F(TB_NAME, ReadZeroInstruction)
{
    create_hex_file();

    top->A = 8;   //idx = 2
    top->eval();

    EXPECT_EQ(top->RD, 0u);
}


int main(int argc, char **argv)
{
    top = new Vdut;
    tfp = new VerilatedVcdC;

    //create rom file before testing
    create_hex_file();

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
