module regfile #(
    ADDRESS_WIDTH = 5,
    DATA_WIDTH = 32
) (
    input   logic                       clk,
    input   logic [ADDRESS_WIDTH-1:0]   ad1,
    input   logic [ADDRESS_WIDTH-1:0]   ad2,
    input   logic [ADDRESS_WIDTH-1:0]   ad3,
    input   logic [DATA_WIDTH-1:0]      wd3,
    input   logic                       we3,
    output  logic [DATA_WIDTH-1:0]      rd1,
    output  logic [DATA_WIDTH-1:0]      rd2,
    output  logic [DATA_WIDTH-1:0]      a0
);
    //create ram with the defined logic
    logic [DATA_WIDTH-1:0] mem [2**ADDRESS_WIDTH-1:0];

    //write on posedge of clock
    always_ff@(posedge clk) begin
        if (we3)
            mem[ad3] <= wd3;
    end

    //read commands
    assign rd1 = mem[ad1];
    assign rd2 = mem[ad2];
    assign a0 = mem[10];
endmodule
