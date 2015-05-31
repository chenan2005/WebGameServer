#ifndef __TEST_SERVER_H__
#define __TEST_SERVER_H__

#include "iod_server.h"

class test_server_session_manager;

class test_server	: public iod_server
{
public:

	test_server(void);

	virtual ~test_server(void);

protected:

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();

	virtual void on_winsys_kbhit(int c);

	virtual void print_help_info();

private:

	test_server_session_manager* session_manager;
};

#endif
