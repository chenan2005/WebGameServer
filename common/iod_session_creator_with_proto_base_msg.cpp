#include "iod_session_creator_with_proto_base_msg.h"

IMP_PROTO_MSG_HANDLE_MAP(iod_session_creator_with_proto_base_msg)

iod_session_creator_with_proto_base_msg::iod_session_creator_with_proto_base_msg(void)
{

}

iod_session_creator_with_proto_base_msg::~iod_session_creator_with_proto_base_msg(void)
{
}

iod_session* iod_session_creator_with_proto_base_msg::on_none_session_message( struct connection_info* conn_info, iod::protobuf::common::base_msg* msg )
{
	if (msg_handler_map.find(msg->messge_id()) == msg_handler_map.end())
		return 0;

	return (this->*(msg_handler_map[msg->messge_id()]))(conn_info, msg);
}

iod_session* iod_session_creator_with_proto_base_msg::on_none_session_packet( struct connection_info* conn_info, iod_packet* packet )
{
	iod_session* session = 0;
	iod::protobuf::common::base_msg* msg = new iod::protobuf::common::base_msg;
	if (msg->ParseFromArray(packet->get_data(), packet->get_length()))
		session = on_none_session_message(conn_info, msg);

	delete msg;

	return session;
}

bool iod_session_creator_with_proto_base_msg::send_base_msg_to(struct connection_info* conn_info, iod::protobuf::common::base_msg* msg)
{
	static char none_session_msg_serialize_buff[_MAX_PACKET_LENGTH];

	if (!conn_info || !conn_info->conn_buffev)
		return false;

	iod_packet* packet = create_packet();

	if (!msg->SerializeToArray(none_session_msg_serialize_buff, sizeof(none_session_msg_serialize_buff)))
		return false;

	packet->set_data(none_session_msg_serialize_buff, msg->ByteSize());

	send_to(conn_info, packet);

	destroy_packet(packet);

	return true;
}
