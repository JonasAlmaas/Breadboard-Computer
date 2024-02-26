# Micro Instructions

## ISSUE_ROtoRI
Try doing RO & RI in the same cycle.
Commonly, micro cycle: 011 and 100.
Remove BO control signals if this is possible

| RI  | RO  |
| :-: | :-: |
| X   | X   |

## Fetch

Every instruction starts by running the fetch sequence.

| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| xxxx   | 000&nbsp;(0) | |     | X   |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |     |     |
| xxxx   | 001&nbsp;(1) | |     |     |     | X   | X   |     |     |     |     |     |     |     |     |     |     | X   |     |     |


## NOP - No Operation

| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  |  ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |  :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0000   | 010&nbsp;(2) | |     |     |     |     |     |     |     |     |     |     |      |     |     |     |     |     | X   |     |


## LDA - Load A

TODO: ISSUE_ROtoRI

| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0001   | 010&nbsp;(2) | |     | X   |     |     |     |     |     |     |     |     |     |     |     |     | X   | X   |     |     |
| 0001   | 011&nbsp;(3) | |     |     |     | X   |     |     | X   |     |     |     |     |     |     |     |     |     |     |     |
| 0001   | 100&nbsp;(4) | |     | X   |     |     |     |     |     | X   |     |     |     |     |     |     |     |     |     |     |
| 0001   | 101&nbsp;(5) | |     |     |     | X   |     |     | X   |     |     |     |     |     |     |     |     |     | X   |     |


## ADD - Add

TODO: ISSUE_ROtoRI

| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | B0  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0010   | 010&nbsp;(2) | |     | X   |     |     |     |     |     |     |     |     |     |     |     |     | X   | X   |     |     |
| 0010   | 011&nbsp;(3) | |     |     |     | X   |     |     |     |     | X   |     |     |     |     |     |     |     |     |     |
| 0010   | 100&nbsp;(4) | |     | X   |     |     |     |     |     |     |     | X   |     |     |     |     |     |     |     |     |
| 0010   | 101&nbsp;(5) | |     |     |     | X   |     |     |     |     | X   |     |     |     |     |     |     |     |     |     |
| 0010   | 110&nbsp;(6) | |     |     |     |     |     |     | X   |     |     |     | X   |     |     |     |     |     | X   | X   |


## SUB - Subtract

TODO: ISSUE_ROtoRI

| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0011   | 010&nbsp;(2) | |     | X   |     |     |     |     |     |     |     |     |     |     |     |     | X   | X   |     |     |
| 0011   | 011&nbsp;(3) | |     |     |     | X   |     |     |     |     | X   |     |     |     |     |     |     |     |     |     |
| 0011   | 100&nbsp;(4) | |     | X   |     |     |     |     |     |     |     | X   |     |     |     |     |     |     |     |     |
| 0011   | 101&nbsp;(5) | |     |     |     | X   |     |     |     |     | X   |     |     |     |     |     |     |     |     |     |
| 0011   | 110&nbsp;(6) | |     |     |     |     |     |     | X   |     |     | X   | X   |     |     |     |     |     | X   | X   |


## STA - Store A

TODO: ISSUE_ROtoRI

| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0100   | 010&nbsp;(2) | |     | X   |     |     |     |     |     |     |     |     |     |     |     |     | X   | X   |     |     |
| 0100   | 011&nbsp;(3) | |     |     |     | X   |     |     |     |     | X   |     |     |     |     |     |     |     |     |     |
| 0100   | 100&nbsp;(4) | |     | X   |     |     |     |     |     |     |     | X   |     |     |     |     |     |     |     |     |
| 0100   | 101&nbsp;(5) | |     |     | X   |     |     |     |     | X   |     |     |     |     |     |     |     |     | X   |     |


## LDI - Load Immediate

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0101   | 010&nbsp;(2)  | |     | X   |     |     |     |     |     |     |     |     |     |     |     |     | X   | X   |     |     |
| 0101   | 011&nbsp;(3)  | |     |     |     | X   |     |     | X   |     |     |     |     |     |     |     |     |     | X   |     |


## JMP - Jump

| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 010&nbsp;(2) | |     | X   |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |     |     |
| 0111   | 011&nbsp;(3) | |     |     |     | X   |     |     |     |     |     |     |     |     |     | X   |     |     | X   |     |


## JZ - Jump If Carry

TODO: Is this logic inverted?

### Carry = 0
| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 010&nbsp;(2) | |     | X   |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |     |     |
| 0111   | 011&nbsp;(3) | |     |     |     | X   |     |     |     |     |     |     |     |     |     | X   |     |     | X   |     |

### Carry = 1
| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 010&nbsp;(2) | |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |


## JZ - Jump If Zero

TODO: Is this logic inverted?

### Zero = 0
| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 010&nbsp;(2) | |     | X   |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |     |     |
| 0111   | 011&nbsp;(3) | |     |     |     | X   |     |     |     |     |     |     |     |     |     | X   |     |     | X   |     |

### Zero = 1
| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 010&nbsp;(2) | |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |



## OUT - Output

| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 1110   | 010&nbsp;(2) | |     |     |     |     |     |     |     | X   |     |     |     |     | X   |     |     |     | X   |     |


## HLT - Halt

| Opcode | Cycle        | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | BO  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 1111   | 010&nbsp;(2) | | X   |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |


# Micro Instruction EEPROM Connections

SG0-SG1: Segment select bits. Can be removed later if expansion is needed.

| A10 | A9  | A8  | A7  | A6  | A5  | A4  | A3  | A2  | A1  | A0  |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| SG1 | SG0 | ZF  | CF  | OP3 | OP2 | OP1 | OP0 | t2  | t1  | t0  |

| Segment      | O7  | O6  | O5  | O4  | O3  | O2  | O1  | O0  |
| :----------: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 2 ( left )   |     |     |     |     |     |     | SFE | MRC |
| 1 ( center ) | PCE | PCO | PCI | OI  | SU  | ΣO  | BO  | BI  |
| 0 ( right )  | AO  | AI  | IO  | II  | RO  | RI  | MI  | HLT |
