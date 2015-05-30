#ifndef __IOD_TIMER_HANDLER_H__
#define __IOD_TIMER_HANDLER_H__

#include "iod_common.h"

class iod_timer_handler
{
public:

	typedef void (iod_timer_handler:: *FNC_TIMER_CALLBACK)(void*);

	struct timer_info
	{
		struct event* ev;
		iod_timer_handler* handler;
		FNC_TIMER_CALLBACK cb_fnc;
		void* cb_fnc_arg;
		bool repeat;
		bool auto_release_arg;
		int timeout_ms;
		int triggered_times;
	};

	timer_info* shedule_timer(int timeout_ms, FNC_TIMER_CALLBACK cb_fnc, void* cb_fnc_arg = 0, bool repeat = false, bool auto_release_arg = false);

	bool remove_timer(timer_info* t);

	static void timeout_cb(evutil_socket_t fd, short ev, void *arg);

protected:

	iod_timer_handler(void);

	virtual ~iod_timer_handler(void);

private:

	std::set< timer_info* > timer_set;
};

#endif
