; This program adds 5 to Register A in an infinite loop and outputs the result

LDI 5       ; Load 5 into Register A
STA 255     ; Store the value in the A Register into RAM at address 255
OUT         ; Output the value in Register A

loop:
ADD 255     ; Add the value at memory address 255 to Register A	
OUT         ; Output the value in Register A
JMP loop    ; Jump up to the "loop" label to continue the loop
