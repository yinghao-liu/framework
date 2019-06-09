# 006 
fsanitize flag in gcc

## Description
check if it can detecte those situation listed below 
- [ ] invoke one function which would cause memory leak several times, and do not exit. 
- [x] invoke one function from shared library which compliled without fsanitize 
- [ ] a prog which compliled without fsanitize invoke one function from shared library which compliled with fsanitize

## Notes
run `make help` show how to use, typically, run `make CASE=3` for situation 3.

## reference
1. man gcc
