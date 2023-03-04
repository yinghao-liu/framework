# 035
disassemble
Environment: X86-64

objdump -dS main
gdb - disassemble

## arguments
前六个参数分别存放在以下寄存器中
rdi            0x1                 1
rsi            0x2                 2
rdx            0x3                 3
rcx            0x4                 4
r8             0x5                 5
r9             0x6                 6
之后的参数存放在堆栈里，按堆栈增长顺序，参数从后至前。例如：0x10(%rbp)，0x18(%rbp)


## return
rax 


## reference
