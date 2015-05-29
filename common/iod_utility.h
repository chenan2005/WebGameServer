#ifndef __IOD_UTILITY_H__
#define __IOD_UTILITY_H__

#include "iod_common.h"

namespace iod_utility {

	//��ȡ��ǰ΢����
	ev_uint64_t get_time_usec();

	//��ȡ��ǰ������
	inline ev_uint32_t get_time_msec() {
		return (ev_uint32_t)(get_time_usec() / 1000);
	}

}

#endif

