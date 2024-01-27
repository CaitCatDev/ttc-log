#include "ttc-log.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
	/*Init the log to output to stderr*/
	ttc_log_init_from_file(stderr);
	
	TTC_LOG_INFO("Information\n");
	ttc_log_printf(TtcLogInfo, "\tContinued Information\n");
	TTC_LOG_DEBUG("%s", "Debug Info\n");
	TTC_LOG_WARN("Warning Info %d\n", 5);
	TTC_LOG_ERROR("Error information\n");
	TTC_LOG_FATAL("Fatal Error\n");

	ttc_log(400, "Madeup.c", 405, "Custom call to see if strings are right\n");

	/*Change logger to text file*/
	if(ttc_log_init_file("log.txt")) {
		/*This will goto stderr*/
		TTC_LOG_ERROR("Logger could not open text file log.txt: %s\n", strerror(errno));
		return 1;
	}
	
	
	if(ttc_log_init_file("/log.txt")) {
		/*This will go to log.txt*/
		TTC_LOG_ERROR("Logger could not open text file /log.txt: %s\n", strerror(errno));
		ttc_log_deinit_file(); /*Logger state is unchanged due to the failure*/
		/*So we still have to close the log file log.txt*/
		return 1;
	}
	
	/*This goes to stderr as we want the user to see it*/
	fprintf(stderr, "\x1b[1;41mThis example is meant to fail. But it didn't on you PC.\nAre you running this as root?\x1b[0m\n");

	/*Assuming the above somehow succeded we should free it*/
	ttc_log_deinit_file();
	return 0;
}
