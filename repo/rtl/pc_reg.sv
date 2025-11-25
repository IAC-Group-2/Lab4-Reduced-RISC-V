module pc_reg #(
    parameter DATA_WIDTH = 32
)(
    input logic clk,
    input logic rst,
    input logic next_pc,
    input logic [DATA_WIDTH-1:0] ImmOp,

    output logic [DATA_WIDTH-1:0] PC_o

);

always_ff @(posedge clk, posedge rst) 
    if (rst) 
        PC_out <= '0;
    else 
        PC_out <= next_pc;

endmodule
