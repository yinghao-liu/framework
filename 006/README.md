# 006 
fsanitize flag in gcc  
environment: Ubuntu 18.04.1 && gcc 7.4.0

## Description
check if it can detecte those situation listed below
1. a prog compiled with fsanitize invoke one function which in the same file, and
   - [x] cause out-of-bounds bug
   - [x] cause use-after-free bug
   - [x] cause memory leak several times, and exit.
   - [ ] cause memory leak several times, and do not exit.
2. a prog compiled with fsanitize invoke one function from shared library which compiled without fsanitize
   - [ ] cause out-of-bounds bug
   - [ ] cause use-after-free bug
   - [x] cause memory leak several times, and exit.
   - [ ] cause memory leak several times, and do not exit.
3. a prog compiled without fsanitize invoke one function from shared library which compiled with fsanitize
   - [x] cause out-of-bounds bug
   - [x] cause use-after-free bug
   - [x] cause memory leak several times, and exit.
   - [ ] cause memory leak several times, and do not exit.
4. a prog compiled with fsanitize invoke one function from shared library which compiled with fsanitize
   - [x] cause out-of-bounds bug
   - [x] cause use-after-free bug
   - [x] cause memory leak several times, and exit.
   - [ ] cause memory leak several times, and do not exit.
5. a prog compiled with fsanitize invoke one function from dlopened library which compiled without fsanitize
   - [ ] cause out-of-bounds bug
   - [ ] cause use-after-free bug
   - [x] cause memory leak several times, and exit.
   - [ ] cause memory leak several times, and do not exit.
6. a prog compiled without fsanitize invoke one function from dlopened library which compiled with fsanitize
   - [x] cause out-of-bounds bug
   - [x] cause use-after-free bug
   - [x] cause memory leak several times, and exit.
   - [ ] cause memory leak several times, and do not exit.
7. a prog compiled with fsanitize invoke one function from dlopened library which compiled with fsanitize
   - [x] cause out-of-bounds bug
   - [x] cause use-after-free bug
   - [x] cause memory leak several times, and exit.
   - [ ] cause memory leak several times, and do not exit.

## Notes
run `make help` show how to use, typically, run `make CASE=3` for situation 3.  
To enable continue-after-error, compile with `-fsanitize-recover=address` and then run your code with `ASAN_OPTIONS=halt_on_error=0`

## reference
1. man gcc
2. https://github.com/google/sanitizers/wiki/AddressSanitizer
3. https://github.com/google/sanitizers/wiki/AddressSanitizerFlags#run-time-flags
