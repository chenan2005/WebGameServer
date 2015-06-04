#include "IODSessionManagerPb.h"

std::map< int, IODSessionManagerPb::FNC_PB_MSG_HANDLER >* IODSessionManagerPb::msg_handler_map;

REG_PROTO_MSG_HANDLE_BEGIN(IODSessionManagerPb, IODSessionManagerPb)
REG_PROTO_MSG_HANDLE_END(IODSessionManagerPb)

IODSessionManagerPb::IODSessionManagerPb(void)
{

}

IODSessionManagerPb::~IODSessionManagerPb(void)
{
}

IODSession* IODSessionManagerPb::on_none_session_message( struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg )
{
	check_register_msg_handle();

	std::map< int, FNC_PB_MSG_HANDLER >::iterator it = msg_handler_map->find(msg->message_id());
	if (it == msg_handler_map->end())
		return 0;

	return (this->*(it->second))(conn_info, msg);
}

IODSession* IODSessionManagerPb::on_none_session_packet( struct connection_info* conn_info, IODPacket* packet )
{
	IODSession* session = 0;
	com::iod::pb::common::BaseMsg* msg = new com::iod::pb::common::BaseMsg;
	if (msg->ParseFromArray(packet->get_data(), packet->get_length()))
		session = on_none_session_message(conn_info, msg);

	delete msg;

	return session;
}

bool IODSessionManagerPb::send_basemsg_to(struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg)
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
