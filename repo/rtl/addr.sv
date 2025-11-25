module addr #(
    parameter DATA_WIDTH = 32
)(
    input logic [DATA_WIDTH-1:0] PC_o,
    input logic [DATA_WIDTH-1:0] ImmOp,

    output logic [DATA_WIDTH-1:0] branch_PC,
    output logic [DATA_WIDTH-1:0] inc_PC

);

    always_comb begin
        branch_PC = PC + ImmOp;
        inc_PC    = PC + 'd4;
    end
    
endmodule
