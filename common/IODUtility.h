#ifndef __IOD_UTILITY_H__
#define __IOD_UTILITY_H__

#include "IODCommon.h"

namespace IODUtility {

	//��ȡ��ǰ΢����
	ev_uint64_t get_time_usec();

	//��ȡ��ǰ������
	inline ev_uint32_t get_time_msec() {
		return (ev_uint32_t)(get_time_usec() / 1000);
	}

	time_t MKTime(struct tm * _Tm);

}

#endif

