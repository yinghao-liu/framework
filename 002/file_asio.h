#ifndef _FILE_ASIO_
#define _FILE_ASIO_

#include <stdio.h>
namespace file_asio {

constexpr int g_max_tick = 100000;
constexpr const char *write_string = "2019-07-20 [DEBUG] uv_test: \
									  file io test for a general line length just like this one, and just a little more,\
									  and olaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaolaola\n";


extern int init(size_t buff_len = 1024);
extern void start(void);

}
#endif
