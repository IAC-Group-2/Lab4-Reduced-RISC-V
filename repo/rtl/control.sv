module control(
    input   logic   [6:0]   op,
    input   logic           eq,
    output  logic           RegWrite,
    output  logic   [2:0]   ALUctrl,
    output  logic           ALUsrc,
    output  logic           Immsrc, // 1 bit for type I (0) and B (1) for now
    output  logic           PCsrc
);

logic branch;

always_comb begin
    RegWrite = 0;
    ALUctrl = 3'b0;
    ALUsrc = 0;
    Immsrc = 0;
    branch = 0;

    case (op) 
    7'b0010011 begin // addi
        RegWrite = 1;
        ALUctrl = 3'b0; // add
        ALUsrc = 1; // immediate
        Immsrc = 0; // I type
        branch = 0;    
    end

    7'b1100011 begin // bne
        RegWrite = 0;
        ALUctrl = 3'b1; // sub
        ALUsrc = 0; // reg
        Immsrc = 1; // B type
        branch = 1; // ben 
    end
    endcase
    
    PCsrc = branch & ~eq;

end
endmodule
