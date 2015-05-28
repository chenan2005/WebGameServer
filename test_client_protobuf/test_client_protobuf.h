#ifndef __TEST_CLIENT_PROTOBUF_H__
#define __TEST_CLIENT_PROTOBUF_H__

#include <set>
#include "iod_server.h"

class test_client_protobuf_session;

class test_client_protobuf : public iod_server
{
public:
	test_client_protobuf(void);
	~test_client_protobuf(void);

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();
	
protected:

	std::set< test_client_protobuf_session* > sessions;
};

#endif
