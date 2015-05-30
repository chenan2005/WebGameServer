#include "iod_session_with_proto_base_msg.h"

IMP_PROTO_MSG_HANDLE_MAP(iod_session_with_proto_base_msg)

iod_session_with_proto_base_msg::iod_session_with_proto_base_msg( void )
{

}

iod_session_with_proto_base_msg::~iod_session_with_proto_base_msg( void )
{

}

void iod_session_with_proto_base_msg::on_message( iod::protobuf::common::base_msg* msg )
{
	if (msg_handler_map.find(msg->messge_id()) == msg_handler_map.end())
		return;

	(this->*(msg_handler_map[msg->messge_id()]))(msg);
}

bool iod_session_with_proto_base_msg::send_message( iod::protobuf::common::base_msg* msg )
{
	static char msg_serialize_buff[_MAX_PACKET_LENGTH];

	iod_packet* packet = create_packet();

	if (!msg->SerializeToArray(msg_serialize_buff, sizeof(msg_serialize_buff)))
		return false;

	packet->set_data(msg_serialize_buff, msg->ByteSize());

	send(packet);

	return true;
}

void iod_session_with_proto_base_msg::on_packet( iod_packet* packet )
{
	iod::protobuf::common::base_msg* msg = new iod::protobuf::common::base_msg;
	if (msg->ParseFromArray(packet->get_data(), packet->get_length()))
	{
		on_message(msg);
	}
	delete msg;
}
