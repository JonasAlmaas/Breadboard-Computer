# Micro Instructions

## Fetch

Every instruction starts by running the fetch sequence.

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| xxxx   | 0000&nbsp;(0) | |     | X   |     |     |     |     |     |     |     |     |     |     |     | X   |     |     |     |
| xxxx   | 0001&nbsp;(1) | |     |     |     | X   | X   |     |     |     |     |     |     |     |     |     | X   |     |     |


## NOP - No Operation

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0000   | 0010&nbsp;(2) | |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |


## LDA - Load A

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0001   | 0010&nbsp;(2) | |     | X   |     |     |     | X   |     |     |     |     |     |     |     |     |     |     |     |
| 0001   | 0011&nbsp;(3) | |     |     |     | X   |     |     | X   |     |     |     |     |     |     |     |     | X   |     |


## ADD - Add

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0010   | 0010&nbsp;(2) | |     | X   |     |     |     | X   |     |     |     |     |     |     |     |     |     |     |     |
| 0010   | 0011&nbsp;(3) | |     |     |     | X   |     |     |     |     | X   |     |     |     |     |     |     |     |     |
| 0010   | 0100&nbsp;(4) | |     |     |     |     |     |     | X   |     |     | X   |     |     |     |     |     | X   | X   |


## SUB - Subtract

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0011   | 0010&nbsp;(2) | |     | X   |     |     |     | X   |     |     |     |     |     |     |     |     |     |     |     |
| 0011   | 0011&nbsp;(3) | |     |     |     | X   |     |     |     |     | X   |     |     |     |     |     |     |     |     |
| 0011   | 0100&nbsp;(4) | |     |     |     |     |     |     | X   |     |     | X   | X   |     |     |     |     | X   | X   |


## STA - Store A

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0100   | 0010&nbsp;(2) | |     | X   |     |     |     | X   |     |     |     |     |     |     |     |     |     |     |     |
| 0100   | 0011&nbsp;(3) | |     |     | X   |     |     |     |     | X   |     |     |     |     |     |     |     | X   |     |


## LDI - Load Immediate

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0101   | 0010&nbsp;(2) | |     |     |     |     |     | X   | X   |     |     |     |     |     |     |     |     | X   |     |


## JMP - Jump

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 0010&nbsp;(2) | |     |     |     |     |     | X   |     |     |     |     |     |     | X   |     |     | X   |     |


## JZ - Jump If Carry

### Carry = 0
| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 0010&nbsp;(2) | |     |     |     |     |     | X   |     |     |     |     |     |     | X   |     |     | X   |     |

### Carry = 1
| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 0010&nbsp;(2) | |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |


## JZ - Jump If Zero

### Zero = 0
| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 0010&nbsp;(2) | |     |     |     |     |     | X   |     |     |     |     |     |     | X   |     |     | X   |     |

### Zero = 1
| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0111   | 0010&nbsp;(2) | |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |



## OUT - Output

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 1110   | 0010&nbsp;(2) | |     |     |     |     |     |     |     | X   |     |     |     | X   |     |     |     | X   |     |


## HLT - Halt

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | II  | IO  | AI  | AO  | BI  | ΣO  | SU  | OI  | PCI | PCO | PCE | MCR | SFE |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 1111   | 0010&nbsp;(2) | | X   |     |     |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |
