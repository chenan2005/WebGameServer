#include "iod_session_pb.h"

std::map< int, iod_session_pb::FNC_PB_MSG_HANDLER >* iod_session_pb::msg_handler_map;

REG_PROTO_MSG_HANDLE_BEGIN(iod_session_pb, iod_session_pb)
REG_PROTO_MSG_HANDLE_END(iod_session_pb)

iod_session_pb::iod_session_pb( void )
{

}

iod_session_pb::~iod_session_pb( void )
{

}

void iod_session_pb::on_message( iod::protobuf::common::base_msg* msg )
{
	check_register_msg_handle();

	std::map< int, FNC_PB_MSG_HANDLER >::iterator it = msg_handler_map->find(msg->messge_id());
	if (it == msg_handler_map->end())
		return;

	(this->*(it->second))(msg);
}

void iod_session_pb::on_packet( iod_packet* packet )
{
	iod::protobuf::common::base_msg* msg = new iod::protobuf::common::base_msg;
	if (msg->ParseFromArray(packet->get_data(), packet->get_length()))
	{
		on_message(msg);
	}
	delete msg;
}

bool iod_session_pb::send_base_msg( iod::protobuf::common::base_msg* msg )
{
	static char msg_serialize_buff[_MAX_PACKET_LENGTH];

	iod_packet* packet = create_packet();

	if (!msg->SerializeToArray(msg_serialize_buff, sizeof(msg_serialize_buff)))
		return false;

	packet->set_data(msg_serialize_buff, msg->ByteSize());

	send(packet);

	destroy_packet(packet);

	return true;
}
