# 050
out-of-bounds

gdb-watch

normaly, Stack address is consecutive, when compile with fsanitize flag, 
it add "left redzone"(f1), "mid redzone"(f2), and "right redzone"(f3) to split
different stack variables.
