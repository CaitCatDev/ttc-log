#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	TtcLogAll,
	TtcLogInfo,
	TtcLogDebug,
	TtcLogWarn,
	TtcLogError,
	TtcLogFatal,
	TtcLogNone
} ttc_log_level;

enum {
	TtcLogDisabled = false,
	TtcLogEnabled = true,
};

/**This function closes a previously opened log file
 * and sets the log file value back to NULL
 * Disabling the log from printing.
 *
 * NOTE This function will close stderr/stdout if you used
 * that as you log file. Though you do not need to manually
 * close these and you can skip using this function when they are 
 * your log file
 */
int ttc_log_deinit_file(void);

int ttc_log_init_file(const char *path);
void ttc_log_init_from_file(FILE *fp);	
void ttc_log_set_level(ttc_log_level level);
void ttc_log_set_output_con(bool enabled);
int ttc_log(ttc_log_level level, const char *file,
		uint32_t line, const char *fmt, ...);
int ttc_log_printf(ttc_log_level level, const char *fmt, ...);

#define TTC_LOG_INFO(...) ttc_log(TtcLogInfo, __FILE__, __LINE__, __VA_ARGS__)
#define TTC_LOG_DEBUG(...) ttc_log(TtcLogDebug, __FILE__, __LINE__, __VA_ARGS__)
#define TTC_LOG_WARN(...) ttc_log(TtcLogWarn, __FILE__, __LINE__, __VA_ARGS__)
#define TTC_LOG_ERROR(...) ttc_log(TtcLogError, __FILE__, __LINE__, __VA_ARGS__)
#define TTC_LOG_FATAL(...) ttc_log(TtcLogFatal, __FILE__, __LINE__, __VA_ARGS__)
