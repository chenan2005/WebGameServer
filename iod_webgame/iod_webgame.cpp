#include "iod_webgame.h"
#include "iod_webgame_session_manager.h"
#include "iod_network.h"
#include "iod_logsystem.h"

IMPLEMENT_SINGLETON_INSTANCE(iod_webgame);

iod_webgame::iod_webgame(void)
{
}

iod_webgame::~iod_webgame(void)
{
}

bool iod_webgame::initialize_server()
{
	session_manager = new iod_webgame_session_manager;

	session_manager->l_info = iod_network::start_listener(session_manager, "0.0.0.0:12345");

	if (!session_manager->l_info){
		iod_log_error("server initialize failed!");
		return false;
	}

	iod_log_info("server initialized");

	return true;
}

int iod_webgame::update_server()
{
	session_manager->check_sessions();

	static unsigned int last_random_kick_time = iod_utility::get_time_msec();
	
	unsigned int current = iod_utility::get_time_msec();
	if (current > last_random_kick_time + 120000) {
		session_manager->random_kick(rand() % 100);
		last_random_kick_time = current;
	}

	return 0;
}

void iod_webgame::shutdown_server()
{
	if (session_manager->l_info)
		iod_network::shutdown_listener(session_manager->l_info);

	delete session_manager;

	iod_log_info("server shutdown");
}

void iod_webgame::on_winsys_kbhit( int c )
{
	if (c == 'p') {
		const iod_netstatistics& stat = session_manager->netstatistics;
		iod_log_info("\nrecv byte count: %llu"
			"\nrecv packet count:%u"
			"\nsend byte count:%llu"
			"\nsend packet count:%u"
			"\nincoming connection count:%u"
			"\nincoming connection close count:%u"
			"\ncreate session count:%u"
			"\ndestroy session count:%u"
			"\ncurrent session count:%u"
			"\nrunning time ms:%u", 
			(unsigned long long)stat.recv_byte_count, 
			stat.recv_packet_count, 
			(unsigned long long)stat.send_byte_count,
			stat.send_packet_count,
			stat.incoming_conn_count,
			stat.incoming_conn_close_count,
			session_manager->create_session_count,
			session_manager->destroy_session_count,
			session_manager->get_session_count(),
			iod_utility::get_time_msec());
	}
	else if (c =='k') {
		session_manager->random_kick(rand() % 100);
	}
}

void iod_webgame::print_help_info()
{
#ifdef WIN32
	iod_log_info("\n  q: quit server"
		"\n  r: reload server config"
		"\n  p: print running statistics"
		"\n  k: random kick some session"
		"\n  h: print this info");
#endif
}
