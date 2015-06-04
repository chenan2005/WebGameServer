#ifndef __IOD_UTILITY_H__
#define __IOD_UTILITY_H__

#include "IODCommon.h"

namespace IODUtility {

	//获取当前微秒数
	ev_uint64_t get_time_usec();

	//获取当前毫秒数
	inline ev_uint32_t get_time_msec() {
		return (ev_uint32_t)(get_time_usec() / 1000);
	}

	//从tm生成time_t，自动获取当前的夏令时标记
	time_t mktimeDaylyTimeFlag(struct tm *);

	inline bool isWordChar(char c) {
		return ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0') || (c == '_'));
	}

	bool isWordInList(const char* wordList, const char* word);
};

#endif

