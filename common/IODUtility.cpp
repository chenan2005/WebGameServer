#include "IODUtility.h"

namespace IODUtility {

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

	time_t mktimeDaylyTimeFlag( struct tm * tmInput )
	{
		static int localDayLightTimeFlag = -1;
		if (localDayLightTimeFlag == -1) {
			struct tm tmTemp;
			memcpy(&tmTemp, tmInput, sizeof(tmTemp));	//复制一份tmInput防止指针内容被localtime覆盖		
			time_t currentGMTimeT = time(NULL);
			tm *tmLocal = localtime(&currentGMTimeT);
			localDayLightTimeFlag = tmLocal->tm_isdst;
			tmTemp.tm_isdst = localDayLightTimeFlag;
			return mktime(&tmTemp);
		}
		else {
			tmInput->tm_isdst = localDayLightTimeFlag;
			return mktime(tmInput);
		}
	}

	bool isWordInList(const char* wordList, const char* word)
	{
		int wordStart = 0;
		int wordEnd = 0;
		int listLength = (int)strlen(wordList);
		int fieldLength = (int)strlen(word);
		while (wordStart < listLength && wordEnd < listLength + 1){

			//寻找单词开头
			while (wordStart < listLength && !isWordChar(wordList[wordStart])) {
				wordStart++;
			}

			//寻找单词结尾
			wordEnd = wordStart + 1;
			while (wordEnd < listLength + 1 && isWordChar(wordList[wordEnd])) {
				wordEnd++;
			}

			//比较单词
			if (wordEnd - wordStart == fieldLength && memcmp(wordList + wordStart, word, wordEnd - wordStart) == 0) {
				return true;
			}

			wordStart = wordEnd + 1;
		}

		return false;
	}

}
