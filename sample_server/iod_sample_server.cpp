#include "iod_sample_server.h"
#include "sample_session_manager.h"
#include "iod_network.h"
#include "iod_logsystem.h"

implement_server_instance(iod_sample_server);

iod_sample_server::iod_sample_server(void)
{
}

iod_sample_server::~iod_sample_server(void)
{
}

bool iod_sample_server::initialize_server()
{
	session_manager = new sample_session_manager;

	iod_network::start_listener(session_manager, "0.0.0.0:12345");

	iod_log_info("server initialized");

	return true;
}

void iod_sample_server::shutdown_server()
{
	delete session_manager;

	iod_log_info("server shutdown");
}
