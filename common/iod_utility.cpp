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

	time_t MKTime( struct tm * _Tm )
	{
		static int s_dst_flag = -1;
		if (s_dst_flag == -1)
		{
			struct tm temp_tm;
			memcpy(&temp_tm, _Tm, sizeof(temp_tm));	//复制一份_Tm防止指针内容被localtime覆盖		
			time_t currentGMTimeT = time(NULL);
			tm *plt = localtime(&currentGMTimeT);
			s_dst_flag = plt->tm_isdst;
			temp_tm.tm_isdst = s_dst_flag;
			return mktime(&temp_tm);
		}
		else
		{
			_Tm->tm_isdst = s_dst_flag;
			return mktime(_Tm);
		}
	}

}