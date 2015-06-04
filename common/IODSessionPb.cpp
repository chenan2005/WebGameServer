#include "IODSessionPb.h"

std::map< int, IODSessionPb::FNC_PB_MSG_HANDLER >* IODSessionPb::msg_handler_map;

REG_PROTO_MSG_HANDLE_BEGIN(IODSessionPb, IODSessionPb)
REG_PROTO_MSG_HANDLE_END(IODSessionPb)

IODSessionPb::IODSessionPb( void )
{

}

IODSessionPb::~IODSessionPb( void )
{

}

void IODSessionPb::on_message( com::iod::pb::common::BaseMsg* msg )
{
	check_register_msg_handle();

	std::map< int, FNC_PB_MSG_HANDLER >::iterator it = msg_handler_map->find(msg->message_id());
	if (it == msg_handler_map->end())
		return;

	(this->*(it->second))(msg);
}

void IODSessionPb::on_packet( IODPacket* packet )
{
	com::iod::pb::common::BaseMsg* msg = new com::iod::pb::common::BaseMsg;
	if (msg->ParseFromArray(packet->get_data(), packet->get_length()))
	{
		on_message(msg);
	}
	delete msg;
}

bool IODSessionPb::send_basemsg( com::iod::pb::common::BaseMsg* msg )
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
