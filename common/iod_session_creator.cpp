#include "iod_session_creator.h"

iod_session_creator::iod_session_creator(void)
{
}

iod_session_creator::~iod_session_creator(void)
{
}

iod_session* iod_session_creator::on_none_session_packet(connection_info* conn_info, iod_packet* packet)
{
	return 0;
}
