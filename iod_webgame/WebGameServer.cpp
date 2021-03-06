#include "WebGameServer.h"
#include "PlayerManager.h"
#include "IODNetwork.h"
#include "IODLogSystem.h"
#include "DbHandle.h"
#include "RoomManager.h"

IMPLEMENT_SINGLETON_INSTANCE(WebGameServer);

WebGameServer::WebGameServer(void)
{
}

WebGameServer::~WebGameServer(void)
{
}

bool WebGameServer::initialize_server()
{
	DbHandle::instance()->initialize("192.168.1.240", 3306, "root", "", "IODWebGame");

	sessionManager = new PlayerManager;

	sessionManager->l_info = IODNetwork::start_listener(sessionManager, "0.0.0.0:12345");

	if (!sessionManager->l_info){
		iod_log_error("server initialize failed!");
		return false;
	}

	iod_log_info("server initialized");

	return true;
}

int WebGameServer::update_server()
{
	RoomManager::instance()->updateStrategy();
	sessionManager->check_sessions();

	//static unsigned int last_random_kick_time = IODUtility::get_time_msec();
	//
	//unsigned int current = IODUtility::get_time_msec();
	//if (current > last_random_kick_time + 120000) {
	//	sessionManager->random_kick(rand() % 100);
	//	last_random_kick_time = current;
	//}

	return 0;
}

void WebGameServer::shutdown_server()
{
	if (sessionManager->l_info)
		IODNetwork::shutdown_listener(sessionManager->l_info);

	delete sessionManager;

	iod_log_info("server shutdown");
}

void WebGameServer::on_winsys_kbhit( int c )
{
	if (c == 'p') {
		const iod_netstatistics& stat = sessionManager->netstatistics;
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
			sessionManager->create_session_count,
			sessionManager->destroy_session_count,
			sessionManager->get_session_count(),
			IODUtility::get_time_msec());
	}
	else if (c =='k') {
		sessionManager->random_kick(rand() % 100);
	}
}

void WebGameServer::print_help_info()
{
#ifdef WIN32
	iod_log_info("\n  q: quit server"
		"\n  r: reload server config"
		"\n  p: print running statistics"
		"\n  k: random kick some session"
		"\n  h: print this info");
#endif
}
