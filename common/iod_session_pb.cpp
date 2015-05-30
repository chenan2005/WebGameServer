#include "iod_session_pb.h"

IMP_PROTO_MSG_HANDLE_MAP(iod_session_pb)

iod_session_pb::iod_session_pb( void )
{

}

iod_session_pb::~iod_session_pb( void )
{

}

void iod_session_pb::on_message( iod::protobuf::common::base_msg* msg )
{
	if (msg_handler_map.find(msg->messge_id()) == msg_handler_map.end())
		return;

	(this->*(msg_handler_map[msg->messge_id()]))(msg);
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
