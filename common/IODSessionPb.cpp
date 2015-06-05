#include "IODSessionPb.h"

REG_PB_MSG_HANDLE_BEGIN(IODSessionPb)
REG_PB_MSG_HANDLE_END()

IODSessionPb::IODSessionPb( void )
{

}

IODSessionPb::~IODSessionPb( void )
{

}

void IODSessionPb::on_message( BaseMsgPb* msg )
{
	DISPATCH_BASE_MSG(this->get_connection_info(), msg);
}

bool IODSessionPb::send_basemsg( BaseMsgPb* msg )
{
	static char msg_serialize_buff[_MAX_PACKET_LENGTH];

	IODPacket* packet = create_packet();

	if (!msg->SerializeToArray(msg_serialize_buff, sizeof(msg_serialize_buff)))
		return false;

	packet->set_data(msg_serialize_buff, msg->ByteSize());

	send(packet);

	destroy_packet(packet);

	return true;
}

bool IODSessionPb::send_basemsg_to(struct connection_info* conn_info, BaseMsgPb* msg)
{
	static char none_session_msg_serialize_buff[_MAX_PACKET_LENGTH];

	if (!conn_info || !conn_info->conn_buffev)
		return false;

	IODPacket* packet = create_packet();

	if (!msg->SerializeToArray(none_session_msg_serialize_buff, sizeof(none_session_msg_serialize_buff)))
		return false;

	packet->set_data(none_session_msg_serialize_buff, msg->ByteSize());

	send_to(conn_info, packet);

	destroy_packet(packet);

	return true;
}

void IODSessionPb::on_packet( IODPacket* packet )
{
	BaseMsgPb* msg = new BaseMsgPb;
	if (msg->ParseFromArray(packet->get_data(), packet->get_length()))
	{
		on_message(msg);
	}
	delete msg;
}
