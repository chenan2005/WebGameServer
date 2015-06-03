#ifndef __TEST_SERVER_PROTOBUF_H__
#define __TEST_SERVER_PROTOBUF_H__

#include "iod_server.h"

class iod_webgame_session_manager;

class iod_webgame	: public iod_server
{
public:

	iod_webgame(void);

	virtual ~iod_webgame(void);

protected:

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();

	virtual void on_winsys_kbhit(int c);

	virtual void print_help_info();

private:

	iod_webgame_session_manager* session_manager;
};

#endif
