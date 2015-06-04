#ifndef __IOD_LOGSYSTEM_H__
#define __IOD_LOGSYSTEM_H__

#include "IODSingleton.h"

#define iod_log_info(format, ...) iod_log_debug(format, __VA_ARGS__)
#define iod_log_error(format, ...) iod_log_debug(format, __VA_ARGS__)
#define iod_log_warn(format, ...) iod_log_debug(format, __VA_ARGS__)
#define iod_log_crit(format, ...) iod_log_debug(format, __VA_ARGS__)
#define iod_log_debug(format, ...) { printf("[debug] : [%s, line %d, %s] : "format##"\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }

class IODLogSystem :
	public IODSingleton< IODLogSystem >
{
private:

	IODLogSystem(void);

	virtual ~IODLogSystem(void);
};

#endif
