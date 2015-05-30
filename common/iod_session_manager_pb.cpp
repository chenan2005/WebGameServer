#include "iod_session_manager_pb.h"

IMP_PROTO_MSG_HANDLE_MAP(iod_session_manager_pb)

iod_session_manager_pb::iod_session_manager_pb(void)
{

}

iod_session_manager_pb::~iod_session_manager_pb(void)
{
}

iod_session* iod_session_manager_pb::on_none_session_message( struct connection_info* conn_info, iod::protobuf::common::base_msg* msg )
{
	if (msg_handler_map.find(msg->messge_id()) == msg_handler_map.end())
		return 0;

	return (this->*(msg_handler_map[msg->messge_id()]))(conn_info, msg);
}

iod_session* iod_session_manager_pb::on_none_session_packet( struct connection_info* conn_info, iod_packet* packet )
{
	iod_session* session = 0;
	iod::protobuf::common::base_msg* msg = new iod::protobuf::common::base_msg;
	if (msg->ParseFromArray(packet->get_data(), packet->get_length()))
		session = on_none_session_message(conn_info, msg);

	delete msg;

	return session;
}

bool iod_session_manager_pb::send_base_msg_to(struct connection_info* conn_info, iod::protobuf::common::base_msg* msg)
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
