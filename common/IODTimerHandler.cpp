#include "IODTimerHandler.h"
#include "IODNetwork.h"

IODTimerHandler::timer_info* IODTimerHandler::shedule_timer(int timeout_ms, FNC_TIMER_CALLBACK cb_fnc, void* cb_fnc_arg/* = 0*/, bool repeat/* = false*/, bool auto_release_arg/* = false*/)
{
	int flag = 0;
	if (repeat)
		flag = EV_PERSIST;
	timer_info* cb_arg = new timer_info;
	struct event* ev = event_new(IODNetwork::evbase, -1, flag, IODTimerHandler::timeout_cb, cb_arg);
	cb_arg->ev = ev;
	cb_arg->handler = this;
	cb_arg->cb_fnc = cb_fnc;
	cb_arg->cb_fnc_arg = cb_fnc_arg;
	cb_arg->repeat = repeat;
	cb_arg->auto_release_arg = auto_release_arg;
	cb_arg->timeout_ms = timeout_ms;
	cb_arg->triggered_times = 0;

	struct timeval tv;
	evutil_timerclear(&tv);
	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;

	event_add(ev, &tv);

	timer_set.insert(cb_arg);

	return cb_arg;
}

bool IODTimerHandler::remove_timer(timer_info* t)
{
	if (timer_set.find(t) != timer_set.end()) {
		destroy_timer_info(t);
		timer_set.erase(t);

		return true;
	}

	return false;
}

void IODTimerHandler::timeout_cb(evutil_socket_t fd, short event, void *args)
{
	timer_info* cb_arg = (timer_info*)args;

	//trigger callback function
	(cb_arg->handler->*(cb_arg->cb_fnc))(cb_arg->cb_fnc_arg);

	if (cb_arg->repeat) {
		struct timeval tv;
		tv.tv_sec = cb_arg->timeout_ms / 1000;
		tv.tv_usec = (cb_arg->timeout_ms % 1000) * 1000;
		event_add(cb_arg->ev, &tv);
		cb_arg->triggered_times++;
	}
	else {
		if (cb_arg->auto_release_arg && cb_arg->cb_fnc_arg)
			delete cb_arg->cb_fnc_arg;
		cb_arg->handler->timer_set.erase(cb_arg);
		event_free(cb_arg->ev);
		delete cb_arg;
	}
}

IODTimerHandler::IODTimerHandler(void)
{
}

IODTimerHandler::~IODTimerHandler(void)
{
	std::set< timer_info* >::iterator it = timer_set.begin();
	while (it != timer_set.end()) {
		destroy_timer_info(*it);
		it++;
	}
}

void IODTimerHandler::destroy_timer_info(timer_info* t)
{
	event_del(t->ev);
	if (t->auto_release_arg && t->cb_fnc_arg)
		delete t->cb_fnc_arg;
	event_free(t->ev);
	delete t;
}

