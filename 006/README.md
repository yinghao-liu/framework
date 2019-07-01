# 006 
fsanitize flag in gcc

## Description
check if it can detecte those situation listed below 
- [ ] a prog which compiled with fsanitize invoke one function which in the same file and would cause memory leak several times, and do not exit. 
- [x] a prog which compiled with fsanitize invoke one function from shared library which compiled without fsanitize 
- [ ] a prog which compiled without fsanitize invoke one function from shared library which compiled with fsanitize
- [ ] a prog which compiled with fsanitize invoke one function from shared library which compiled with fsanitize 
- [ ] a prog which compiled with fsanitize invoke one function from dlopened library which compiled without fsanitize
- [ ] a prog which compiled without fsanitize invoke one function from dlopened library which compiled with fsanitize
- [ ] a prog which compiled with fsanitize invoke one function from dlopened library which compiled with fsanitize

## Notes
run `make help` show how to use, typically, run `make CASE=3` for situation 3.

## reference
1. man gcc
