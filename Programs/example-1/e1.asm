; This program adds 2 to Register A in an infinite loop and outputs the result

NOP         ; This has to be here, because something is wrong ...
LDI 2       ; Load 2 into Register A
STA 255     ; Store the value in the A Register into RAM at address 255

loop:
OUT         ; Output the value in Register A
ADD 255     ; Add the value at memory address 255 to Register A	
JMP loop    ; Jump up to the "loop" label to continue the loop
