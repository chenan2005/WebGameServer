#ifndef __TEST_CLIENT_H__
#define __TEST_CLIENT_H__

#include <set>
#include "iod_server.h"

class sample_session;

class test_client : public iod_server
{
public:
	test_client(void);
	~test_client(void);

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();
	
protected:

	std::set< sample_session* > sessions;
};

#endif
