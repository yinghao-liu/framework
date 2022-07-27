#include <syslog.h>

int syslog_test(){

	openlog("syslog_test", LOG_PID, 0);
	syslog(LOG_NOTICE, "this is a test of syslog");
	closelog();
	return 0;
}
int main(void){
	syslog_test();
}
