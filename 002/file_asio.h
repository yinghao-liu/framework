#ifndef _FILE_ASIO_
#define _FILE_ASIO_

#include <stdio.h>
namespace file_asio {

extern int init(size_t buff_len = 1024);
extern void start(void);

}
#endif
