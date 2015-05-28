#pragma once
#include "iod_singleton.h"

#define iod_log_info(format, ...) iod_log_debug(format, __VA_ARGS__)
#define iod_log_error(format, ...) iod_log_debug(format, __VA_ARGS__)
#define iod_log_warn(format, ...) iod_log_debug(format, __VA_ARGS__)
#define iod_log_crit(format, ...) iod_log_debug(format, __VA_ARGS__)
#define iod_log_debug(format, ...) { printf("[debug] : [%s, line %d, %s] : "format##"\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }

class iod_logsystem :
	public iod_singleton< iod_logsystem >
{
private:
	iod_logsystem(void);
	virtual ~iod_logsystem(void);
};
