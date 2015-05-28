#ifndef __IOD_COMMON_H__
#define __IOD_COMMON_H__

#ifdef WIN32

/**
******************************************************
win32
******************************************************
*/
#include <Winsock2.h> 
#include <Windows.h>
#include <conio.h>
#define snprintf _snprintf

#elif __x86_64

/**
******************************************************
unix/linux 32
******************************************************
*/

#else

/**
******************************************************
unix/linux 64
******************************************************
*/

#endif

/**
******************************************************
all platform include headers
******************************************************
*/

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <queue>

#include <time.h>

#endif
