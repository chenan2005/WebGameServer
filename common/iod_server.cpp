#include "iod_server.h"
#include "iod_network.h"
#include "iod_logsystem.h"

iod_server* iod_server::_server_instance = 0;

bool iod_server::initialize()
{
	if (!initialize_running_env())
		return false;

	if (!initialize_log_system())
		return false;

	if (!load_config())
		return false;

	if (!iod_network::initialize())
		return false;

	return initialize_server();
}

int iod_server::update()
{
	iod_network::update();

	return update_server();
}

void iod_server::shutdown()
{
	shutdown_server();
	iod_network::shutdown();
	shutdown_log_system();
	return;
}

bool iod_server::check_flag(unsigned int flag)
{
	return (ctrl_flag & flag) != 0;
}

void iod_server::set_flag(unsigned int flag)
{
	ctrl_flag |= flag;
}

void iod_server::on_winsys_kbhit(int c)
{
	return;
}

bool iod_server::initialize_running_env()
{
	return true;
}

bool iod_server::initialize_log_system()
{
	return true;
}

bool iod_server::load_config()
{
	return reload_config();
}

void iod_server::shutdown_log_system()
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

	iod_server* server_instance = iod_server::instance();

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
	iod_utility::get_time_msec();

	while (true)
	{
		server_instance->update();

#ifdef WIN32
		if (_kbhit())
		{
			int c = _getch();
			if (c == 'q')
				server_instance->set_flag(iod_server::CTRL_FLAG_QUIT);
			else if (c == 'r')
				server_instance->set_flag(iod_server::CTRL_FLAG_RELOAD);
			else
				server_instance->on_winsys_kbhit(c);
		}
#endif

		if (server_instance->check_flag(iod_server::CTRL_FLAG_RELOAD))
			server_instance->reload_config();
		else if (server_instance->check_flag(iod_server::CTRL_FLAG_QUIT))
			break;
	}

	iod_server::instance()->shutdown();

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