#pragma once

#include "iod_server.h"

class sample_session_manager;

class iod_sample_server	: public iod_server
{
public:

	iod_sample_server(void);

	virtual ~iod_sample_server(void);

protected:

	virtual bool initialize_server();

	virtual int update_server();

	virtual void shutdown_server();

	virtual void on_winsys_kbhit(int c);

private:

	sample_session_manager* session_manager;
};
