#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#include "ttc-log.h"

typedef struct ttc_log_cfg {
	ttc_log_level level;
	FILE *fp;
} ttc_log_cfg_t;

/**Default settings for logger*/
static ttc_log_cfg_t ttc_log_cfg = {
	.level = TtcLogDebug,
	.fp = NULL,
};

static const char *ttc_log_get_level_str(ttc_log_level level) {
	switch (level) {
		case TtcLogInfo: return "INFO";
		case TtcLogDebug: return "DEBUG";
		case TtcLogWarn: return "WARN";
		case TtcLogError: return "ERROR";
		case TtcLogFatal: return "FATAL";
		default: return "UNKNOWN"; /*Here for bad input*/
	}
}

void ttc_log_set_level(ttc_log_level level) {
	ttc_log_cfg.level = level;
}

int ttc_log_init_file(const char *path) {
	FILE *fp;

	fp = fopen(path, "w");
	if(!fp) {
		return 1;
	}

	ttc_log_cfg.fp = fp;
	return 0;
}

int ttc_log_deinit_file(void) {
	FILE *tmp = ttc_log_cfg.fp;
	
	ttc_log_cfg.fp = NULL;

	return fclose(tmp);
}

void ttc_log_init_from_file(FILE *fp) {
	ttc_log_cfg.fp = fp;
}

int ttc_log(ttc_log_level level, const char *file,
		uint32_t line, const char *fmt, ...) {
	va_list args;
	int res;


	va_start(args, fmt);
	if(ttc_log_cfg.fp) {
		fprintf(ttc_log_cfg.fp, "%s %s(%d):", ttc_log_get_level_str(level), file, line);
		res = vfprintf(ttc_log_cfg.fp, fmt, args);
		fflush(ttc_log_cfg.fp);
	}
	va_end(args);

	return res;
}

int ttc_log_printf(ttc_log_level level, const char *fmt, ...) {
	va_list args;
	int res;

	va_start(args, fmt);
	if(ttc_log_cfg.fp) {
		res = vfprintf(ttc_log_cfg.fp, fmt, args);
	}
	va_end(args);

	return res;	
}
