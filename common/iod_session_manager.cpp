#include "iod_session_manager.h"

iod_session_manager::iod_session_manager(void)
{
	memset(&netstatistics, 0, sizeof(netstatistics));
}

iod_session_manager::~iod_session_manager(void)
{
}

bool iod_session_manager::send_to(connection_info* conn_info, iod_packet* packet)
{
	if (!conn_info || !conn_info->conn_buffev)
		return false;

	int send_bytes = packet->write(conn_info->conn_buffev);

	if (send_bytes <= 0)
		return false;

	netstatistics.send_byte_count += send_bytes;
	netstatistics.send_packet_count++;

	return true;
}
