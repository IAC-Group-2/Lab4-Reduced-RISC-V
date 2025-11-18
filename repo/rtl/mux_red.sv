module mux #(
    DATA_WIDTH = 32
) (
    input   logic [DATA_WIDTH-1:0]  regOp2, //output when ALUsrc = 0
    input   logic [DATA_WIDTH-1:0]  ImmOp, //output when ALUsrc = 1
    input   logic                   ALUsrc, //from control bit
    output  logic [DATA_WIDTH-1:0]  ALUop2 //output
);
    //MUX outputs ImmOp when ALUsrc = 1, outputs regOp2 otherwise
    assign ALUop2 = ALUsrc ? ImmOp : regOp2;

endmodule
