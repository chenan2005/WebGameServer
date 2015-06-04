#include "IODSessionManager.h"

IODSessionManager::IODSessionManager(void)
{
	memset(&netstatistics, 0, sizeof(netstatistics));
}

IODSessionManager::~IODSessionManager(void)
{
}

bool IODSessionManager::send_to(connection_info* conn_info, IODPacket* packet)
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
