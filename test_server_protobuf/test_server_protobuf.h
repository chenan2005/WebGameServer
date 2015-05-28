#ifndef __TEST_SERVER_PROTOBUF_H__
#define __TEST_SERVER_PROTOBUF_H__

#include "iod_server.h"

class test_server_protobuf_session_manager;

class test_server_protobuf	: public iod_server
{
public:

	test_server_protobuf(void);

	virtual ~test_server_protobuf(void);

protected:

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();

	virtual void on_winsys_kbhit(int c);

private:

	test_server_protobuf_session_manager* session_manager;
};

#endif
