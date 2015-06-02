#include "iod_session_manager_pb.h"

std::map< int, iod_session_manager_pb::FNC_PB_MSG_HANDLER >* iod_session_manager_pb::msg_handler_map;

REG_PROTO_MSG_HANDLE_BEGIN(iod_session_manager_pb, iod_session_manager_pb)
REG_PROTO_MSG_HANDLE_END(iod_session_manager_pb)

iod_session_manager_pb::iod_session_manager_pb(void)
{

}

iod_session_manager_pb::~iod_session_manager_pb(void)
{
}

iod_session* iod_session_manager_pb::on_none_session_message( struct connection_info* conn_info, iod_pb::common::base_msg* msg )
{
	check_register_msg_handle();

	std::map< int, FNC_PB_MSG_HANDLER >::iterator it = msg_handler_map->find(msg->messge_id());
	if (it == msg_handler_map->end())
		return 0;

	return (this->*(it->second))(conn_info, msg);
}

iod_session* iod_session_manager_pb::on_none_session_packet( struct connection_info* conn_info, iod_packet* packet )
{
	iod_session* session = 0;
	iod_pb::common::base_msg* msg = new iod_pb::common::base_msg;
	if (msg->ParseFromArray(packet->get_data(), packet->get_length()))
		session = on_none_session_message(conn_info, msg);

	delete msg;

	return session;
}

bool iod_session_manager_pb::send_base_msg_to(struct connection_info* conn_info, iod_pb::common::base_msg* msg)
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
