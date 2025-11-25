module mux_reg #(
    DATA_WIDTH = 32
) (
    input   logic [DATA_WIDTH-1:0]  inc_PC,
    input   logic [DATA_WIDTH-1:0]  branch_PC,
    input   logic                   PC_src,
    output  logic [DATA_WIDTH-1:0]  next_pc
);
    assign next_pc = PC_src ? branch_PC : inc_PC;

endmodule
