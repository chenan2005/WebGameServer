#ifndef __TEST_SERVER_PROTOBUF_H__
#define __TEST_SERVER_PROTOBUF_H__

#include "IODServer.h"

class test_server_pb_session_manager;

class test_server_pb	: public IODServer
{
public:

	test_server_pb(void);

	virtual ~test_server_pb(void);

protected:

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();

	virtual void on_winsys_kbhit(int c);

	virtual void print_help_info();

private:

	test_server_pb_session_manager* session_manager;
};

#endif
