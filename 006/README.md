# 006 
fsanitize flag in gcc

## Description
check if it can detecte those situation listed below 
- [ ] invoke one function which would cause memory leak several times, and do not exit. 
- [x] invoke one function from shared library which compliled without fsanitize 

## reference
1. man gcc
