# 005 
backtrace

## Note
about the `-rdynamic` flag passed to `LDFLAGS` 
> Pass the flag -export-dynamic to the ELF linker, on targets that support it. 
> This instructs the linker to add all symbols, not only used ones, to the
> dynamic symbol table. This option is needed for some uses of "dlopen" or to allow obtaining backtraces from within a program.


## Example
there is a version without `-rdynamic`(main_nodynamic), you can use `addr2line` to convert addresses into file names and line numbers
typically, run `addr2line -e main_nodynamic addr` to get the information.

`./main(fun_exit+0x5a) [0x56208e612b54]`
use `nm main | grep fun_exit` we'll get `0000000000000afa T fun_exit`, then the address is 0xafa+0x5a=0xb54


## reference
1. man backtrace
2. man gcc
3. man addr2line
4. man nm
