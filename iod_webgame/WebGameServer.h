#ifndef __TEST_SERVER_PROTOBUF_H__
#define __TEST_SERVER_PROTOBUF_H__

#include "IODServer.h"

class PlayerManager;

class WebGameServer	: public IODServer
{
public:

	WebGameServer(void);

	virtual ~WebGameServer(void);

protected:

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();

	virtual void on_winsys_kbhit(int c);

	virtual void print_help_info();

private:

	PlayerManager* session_manager;
};

#endif
