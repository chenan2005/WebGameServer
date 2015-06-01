#ifndef __TEST_SERVER_PROTOBUF_H__
#define __TEST_SERVER_PROTOBUF_H__

#include "iod_server.h"

class test_s_pb_conf_session_manager;

class test_s_pb_conf	: public iod_server
{
public:

	test_s_pb_conf(void);

	virtual ~test_s_pb_conf(void);

protected:

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();

	virtual void on_winsys_kbhit(int c);

	virtual void print_help_info();

private:

	test_s_pb_conf_session_manager* session_manager;
};

#endif
