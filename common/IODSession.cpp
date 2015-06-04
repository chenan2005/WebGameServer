#include "IODSession.h"
#include "IODLogSystem.h"
#include "IODNetwork.h"

IODSession::IODSession() : conn_info(0), net_state(SNS_NONE)
{
	last_net_state_time = IODUtility::get_time_msec();
}

IODSession::~IODSession(void)
{
	close(IODNetwork::CONNECTION_CLOSE_BY_LOCAL);
}

bool IODSession::connect(const char* target_addr)
{
	if (!IODNetwork::start_connection(this, target_addr)) 
		return false;
	set_net_state(SNS_CONNECTING);
	return true;
}

void IODSession::close(int reason)
{
	if (conn_info)
		IODNetwork::destroy_connection(conn_info, reason);
}

bool IODSession::send( IODPacket* packet )
{
	if (net_state != SNS_CONNECTED)
		return false;

	int send_bytes = packet->write(conn_info->conn_buffev);

	if (send_bytes <= 0)
		return false;

	IODSessionManager* session_creator = conn_info->session_creator;
	if (session_creator) {
		session_creator->netstatistics.send_byte_count += send_bytes;
		session_creator->netstatistics.send_packet_count++;
	}

	return true;
}

bool IODSession::send_to(connection_info* conn_info, IODPacket* packet)
{
	if (!conn_info || !conn_info->conn_buffev)
		return false;

	int send_bytes = packet->write(conn_info->conn_buffev);

	if (send_bytes <= 0)
		return false;

	return true;
}

void IODSession::flush()
{
	IODNetwork::flush_connection(conn_info);
}

void IODSession::on_connected()
{
	//iod_log_info("connect success");
}

void IODSession::on_closed(int reason)
{
	//iod_log_info("connection close: %d", reason);
}

void IODSession::set_net_state(session_net_state net_state)
{
	this->net_state = net_state;
	this->last_net_state_time = IODUtility::get_time_msec();
}
