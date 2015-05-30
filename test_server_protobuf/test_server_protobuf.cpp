#include "test_server_protobuf.h"
#include "test_server_protobuf_session_manager.h"
#include "iod_network.h"
#include "iod_logsystem.h"

implement_server_instance(test_server_protobuf);

test_server_protobuf::test_server_protobuf(void)
{
}

test_server_protobuf::~test_server_protobuf(void)
{
}

bool test_server_protobuf::initialize_server()
{
	session_manager = new test_server_protobuf_session_manager;

	session_manager->l_info = iod_network::start_listener(session_manager, "0.0.0.0:12345");

	if (!session_manager->l_info){
		iod_log_error("server initialize failed!");
		return false;
	}

	iod_log_info("server initialized");

	return true;
}

int test_server_protobuf::update_server()
{
	session_manager->check_sessions();
	return 0;
}

void test_server_protobuf::shutdown_server()
{
	if (session_manager->l_info)
		iod_network::shutdown_listener(session_manager->l_info);

	delete session_manager;

	iod_log_info("server shutdown");
}

void test_server_protobuf::on_winsys_kbhit( int c )
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
}
