#ifndef __IOD_TIMER_HANDLER_H__
#define __IOD_TIMER_HANDLER_H__

#include "IODCommon.h"

class IODTimerHandler
{
public:

	typedef void (IODTimerHandler:: *FNC_TIMER_CALLBACK)(void*);

	struct timer_info
	{
		struct event* ev;
		IODTimerHandler* handler;
		FNC_TIMER_CALLBACK cb_fnc;
		void* cb_fnc_arg;
		bool repeat;
		bool auto_release_arg;
		int timeout_ms;
		int triggered_times;
	};

	IODTimerHandler(void);

	virtual ~IODTimerHandler(void);

	static void timeout_cb(evutil_socket_t fd, short ev, void *arg);

	timer_info* shedule_timer(int timeout_ms, FNC_TIMER_CALLBACK cb_fnc, void* cb_fnc_arg = 0, bool repeat = false, bool auto_release_arg = false);

	bool remove_timer(timer_info* t);

private:

	void destroy_timer_info(timer_info* t);

	std::set< timer_info* > timer_set;
};

#endif
