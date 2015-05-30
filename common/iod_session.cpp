#include "iod_session.h"
#include "iod_logsystem.h"
#include "iod_network.h"

iod_session::iod_session() : conn_info(0), net_state(SNS_NONE)
{
	last_net_state_time = iod_utility::get_time_msec();
}

iod_session::~iod_session(void)
{
	close(iod_network::CONNECTION_CLOSE_BY_LOCAL);
}

bool iod_session::connect(const char* target_addr)
{
	if (!iod_network::start_connection(this, target_addr)) 
		return false;
	set_net_state(SNS_CONNECTING);
	return true;
}

void iod_session::close(int reason)
{
	if (conn_info)
		iod_network::destroy_connection(conn_info, reason);
}

bool iod_session::send( iod_packet* packet )
{
	if (net_state != SNS_CONNECTED)
		return false;

	int send_bytes = packet->write(conn_info->conn_buffev);

	if (send_bytes <= 0)
		return false;

	iod_session_manager* session_creator = conn_info->session_creator;
	if (session_creator) {
		session_creator->netstatistics.send_byte_count += send_bytes;
		session_creator->netstatistics.send_packet_count++;
	}

	return true;
}

void iod_session::flush()
{
	iod_network::flush_connection(conn_info);
}

void iod_session::on_connected()
{
	//iod_log_info("connect success");
}

void iod_session::on_closed(int reason)
{
	//iod_log_info("connection close: %d", reason);
}

void iod_session::set_net_state(session_net_state net_state)
{
	this->net_state = net_state;
	this->last_net_state_time = iod_utility::get_time_msec();
}
