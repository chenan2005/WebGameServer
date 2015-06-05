#ifndef __IOD_TIMER_HANDLER_H__
#define __IOD_TIMER_HANDLER_H__

#include "IODCommon.h"

class IODTimerHandler
{
public:

	typedef void (IODTimerHandler:: *FNC_TIMER_CALLBACK)(void*);

	class timer_info
	{
	public:

		inline timer_info(): ev(0)
			, handler(0)
			, cb_fnc(0)
			, cb_fnc_arg(0)
			, repeat(false)
			, auto_release_arg(false)
			, timeout_ms(0)
			, triggered_times(0)
			, uid(auto_inc_timer_info_uid++) {}

		inline ev_uint64_t get_uid() { return uid; }

		struct event* ev;
		IODTimerHandler* handler;
		FNC_TIMER_CALLBACK cb_fnc;
		void* cb_fnc_arg;
		bool repeat;
		bool auto_release_arg;
		int timeout_ms;
		int triggered_times;

	private:

		static ev_uint64_t auto_inc_timer_info_uid;

		ev_uint64_t uid;
	};

	IODTimerHandler(void);

	virtual ~IODTimerHandler(void);

	static void timeout_cb(evutil_socket_t fd, short ev, void *arg);

	ev_uint64_t shedule_timer(int timeout_ms, FNC_TIMER_CALLBACK cb_fnc, void* cb_fnc_arg = 0, bool repeat = false, bool auto_release_arg = false);

	inline timer_info* get_timer_info(ev_uint64_t uid) {
		std::map< ev_uint64_t, timer_info* >::iterator it = timer_map.find(uid);
		if (it == timer_map.end())
			return 0;
		return it->second;
	}

	inline bool remove_timer(ev_uint64_t uid) {
		timer_info* ti = get_timer_info(uid);
		if (!ti)
			return false;
		destroy_timer_info(ti);
		timer_map.erase(uid);
		return true;
	}

	inline bool remove_timer(timer_info* t) {
		return remove_timer(t->get_uid());
	}

private:

	void destroy_timer_info(timer_info* t);

	std::map< ev_uint64_t, timer_info* > timer_map;
};

#endif
