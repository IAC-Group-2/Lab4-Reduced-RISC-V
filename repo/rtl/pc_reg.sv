module pc_reg #(
    parameter DATA_WIDTH = 32
)(
    input logic clk,
    input logic rst,
    input logic PCsrc,
    input logic [DATA_WIDTH-1:0] ImmOp,

    output logic [DATA_WIDTH-1:0] PC_out

);

    logic [DATA_WIDTH-1:0] branch_PC;
    logic [DATA_WIDTH-1:0] inc_PC;
    

always_comb begin
    branch_PC = PC_out + ImmOp;
    inc_PC    = PC_out + 'd4;
end


always_ff @(posedge clk, posedge rst) 
    if (rst) 
        PC_out <= '0;
    else if (PCsrc) 
        PC_out <= branch_PC;
    else 
        PC_out <= inc_PC; 

endmodule
