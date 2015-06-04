#ifndef __IOD_UTILITY_H__
#define __IOD_UTILITY_H__

#include "iod_common.h"

namespace iod_utility {

	//获取当前微秒数
	ev_uint64_t get_time_usec();

	//获取当前毫秒数
	inline ev_uint32_t get_time_msec() {
		return (ev_uint32_t)(get_time_usec() / 1000);
	}

	time_t MKTime(struct tm * _Tm);

}

#endif

