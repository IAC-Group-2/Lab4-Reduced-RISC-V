module top #(
    DATA_WIDTH = 32
) (
    input   logic clk,
    input   logic rst,
    output  logic [DATA_WIDTH-1:0] a0    
);
    //PC Path

    logic [31:0] pc;

    //Instruction
    logic[31:0] instr;

    //ImmOp
    logic[31:0] ImmOp;

    //Register File
    logic[4:0] rs1;
    logic[4:0] rs2;
    logic[4:0] rd;

    logic[DATA_WIDTH-1:0] ALUop1;
    logic[DATA_WIDTH-1:0] ALUop2;
    logic[DATA_WIDTH-1:0] regOp2;
    logic[DATA_WIDTH-1:0] ALUout;
    logic       eq;


    //green
    logic [6:0]   op;

    logic           RegWrite;
    logic [2:0]     ALUctrl;
    logic           ALUsrc;
    logic           Immsrc; // 1 bit for type I (0) and B (1) for now
    logic           PCsrc;
    
    pc_reg pc_reg (
        .clk(clk),
        .rst(rst),
        .PCsrc(PCsrc),
        .ImmOp(ImmOp),
        .PC_out(pc)
    );

    instr_mem instr_mem (
        .A(pc),
        .RD(instr)
    );


    assign rs2 = instr[24:20];
    assign rs1 = instr[19:15];
    assign rd  = instr[11:7];
    assign op = instr[6:0];


    control control_unit(
        .op(op),
        .eq(eq),
        .RegWrite(RegWrite),
        .ALUctrl(ALUctrl),
        .ALUsrc(ALUsrc),
        .Immsrc(Immsrc),
        .PCsrc(PCsrc)
    );

    sign_extend sign_extend (
        .imm_src(Immsrc),
        .imm_instr(instr),
        .imm_ext(ImmOp)
    );

    regfile regfile(
        .clk(clk),
        .ad1(rs1),
        .ad2(rs2),
        .ad3(rd),
        .wd3(ALUout),
        .we3(RegWrite),
        .rd1(ALUop1),
        .rd2(regOp2),
        .a0(a0)
    );

    assign ALUop2 = ALUsrc ? ImmOp : regOp2;

    ALU ALU (
        .in0(ALUop1),
        .in1(ALUop2),
        .ctrl(ALUctrl),
        .out(ALUout),
        .eq(eq)


    );    
endmodule

