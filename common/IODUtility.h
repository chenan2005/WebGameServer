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

	//��tm����time_t���Զ���ȡ��ǰ������ʱ���
	time_t mktimeDaylyTimeFlag(struct tm *);

	inline bool isWordChar(char c) {
		return ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0') || (c == '_'));
	}

	bool isWordInList(const char* wordList, const char* word);
};

#endif

