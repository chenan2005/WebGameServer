#ifndef __IOD_UTILITY_H__
#define __IOD_UTILITY_H__

#include "iod_common.h"

namespace iod_utility {

	//获取当前微秒数
	static inline ev_uint64_t get_time_usec() {
		static timeval _start_timeval = {0};
		static bool _has_start_timeval = false;
		if (!_has_start_timeval) {
			evutil_gettimeofday(&_start_timeval, 0);
			_has_start_timeval = true;
			return 0;
		}
		static timeval _current_timeval = {0};
		static timeval _timeinterval = {0};
		evutil_gettimeofday(&_current_timeval, 0);
		evutil_timersub(&_current_timeval, &_start_timeval, &_timeinterval);
		return _timeinterval.tv_sec * 1000000 + _timeinterval.tv_usec;
	}

	//获取当前毫秒数
	static inline ev_uint32_t get_time_msec() {
		return (ev_uint32_t)(get_time_usec() / 1000);
	}

}

#endif

