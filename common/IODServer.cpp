#include "IODServer.h"
#include "IODNetwork.h"
#include "IODLogSystem.h"

IODServer* IODServer::_server_instance = 0;

bool IODServer::initialize()
{
	if (!initialize_running_env())
		return false;

	if (!initialize_log_system())
		return false;

	if (!load_config())
		return false;

	if (!IODNetwork::initialize())
		return false;

	return initialize_server();
}

int IODServer::update()
{
	IODNetwork::update();

	return update_server();
}

void IODServer::shutdown()
{
	shutdown_server();
	IODNetwork::shutdown();
	shutdown_log_system();
	return;
}

bool IODServer::check_flag(unsigned int flag)
{
	return (ctrl_flag & flag) != 0;
}

void IODServer::set_flag(unsigned int flag)
{
	ctrl_flag |= flag;
}

void IODServer::clear_flag(unsigned int flag)
{
	ctrl_flag &= ~flag;
}

void IODServer::on_winsys_kbhit(int c)
{
	return;
}

void IODServer::print_startup_info()
{
	iod_log_info("start server successfully");
	print_help_info();
}

void IODServer::print_help_info()
{
#ifdef WIN32
	iod_log_info("\n  q: quit server"
		"\n  r: reload server config"
		"\n  h: print this info");
#endif
}

bool IODServer::initialize_running_env()
{
	return true;
}

bool IODServer::initialize_log_system()
{
	return true;
}

bool IODServer::load_config()
{
	return reload_config();
}

void IODServer::shutdown_log_system()
{
}

//------------------------------------------------------------

inline void winsys_wait_key() {
#ifdef WIN32
	printf("\npress any key to continue...");
	_getch();
#endif
}

int main(int argc, char *argv[])
{
//#ifdef WIN32
//#ifdef _DEBUG
//	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
//#endif //_DEBUG
//#endif //WIN32

	IODServer* server_instance = IODServer::instance();

	if (!server_instance) {
		printf("\nmissing server instance!\n");
		winsys_wait_key();
		return -1;
	}


	if (!server_instance->initialize()) {
		winsys_wait_key();
		return -1;
	}

	//初始化时间
	IODUtility::get_time_msec();

	server_instance->print_startup_info();

	while (true)
	{
		server_instance->update();

#ifdef WIN32
		if (_kbhit())
		{
			int c = _getch();
			if (c == 'q')
				server_instance->set_flag(IODServer::CTRL_FLAG_QUIT);
			else if (c == 'r')
				server_instance->set_flag(IODServer::CTRL_FLAG_RELOAD);
			else if (c == 'h')
				server_instance->print_help_info();
			else
				server_instance->on_winsys_kbhit(c);
		}
#endif

		if (server_instance->check_flag(IODServer::CTRL_FLAG_RELOAD)) {
			server_instance->reload_config();
			server_instance->clear_flag(IODServer::CTRL_FLAG_RELOAD);
		}
		
		if (server_instance->check_flag(IODServer::CTRL_FLAG_QUIT)) {
			break;
		}
	}

	IODServer::instance()->shutdown();

#ifdef WIN32
	winsys_wait_key();
#endif

//#ifdef WIN32
//#ifdef _DEBUG
//	_CrtDumpMemoryLeaks();
//#endif
//#endif

	return 0;
}