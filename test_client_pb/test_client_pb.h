#ifndef __TEST_CLIENT_PROTOBUF_H__
#define __TEST_CLIENT_PROTOBUF_H__

#include <set>
#include "iod_server.h"

class test_client_protobuf_session;

class test_client_pb : public iod_server
{
public:
	test_client_pb(void);
	~test_client_pb(void);

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();
	
	virtual void on_winsys_kbhit(int c);

protected:

	std::set< test_client_protobuf_session* > sessions;
};

#endif
