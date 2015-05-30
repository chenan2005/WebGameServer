#include "iod_utility.h"

namespace iod_utility {

	ev_uint64_t get_time_usec()
	{
		static timeval _start_timeval = {0};
		static bool _has_start_timeval = false;
		static timeval _current_timeval = {0};
		static timeval _timeinterval = {0};

		if (!_has_start_timeval) {
			evutil_gettimeofday(&_start_timeval, 0);
			_has_start_timeval = true;
			return 0;
		}
		evutil_gettimeofday(&_current_timeval, 0);
		evutil_timersub(&_current_timeval, &_start_timeval, &_timeinterval);
		return (ev_uint64_t)_timeinterval.tv_sec * 1000000 + _timeinterval.tv_usec;
	}

}