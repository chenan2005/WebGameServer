#ifndef __IOD_SESSION_MANAGER_PB_H__
#define __IOD_SESSION_MANAGER_PB_H__

#include "IODSessionManager.h"
#include "IODSessionPb.h"

//-------------------------------------------------------------------------------

#define SAFE_GET_NONE_SESSION_EXTENSION(msg, protocol_name, varname) \
	if (!msg->HasExtension(id##protocol_name)) \
		return 0; \
	const protocol_name& varname = msg->GetExtension(id##protocol_name);

//-------------------------------------------------------------------------------

#define SEND_MESSAGE_TO(conn_info, protocol_name, var) send_message_to(conn_info, id##protocol_name, var)

//-------------------------------------------------------------------------------

class IODSessionManagerPb : public IODSessionManager
{
	DEC_REG_PROTO_MSG_HANDLE(IODSessionManagerPb)

public:

	IODSessionManagerPb(void);

	virtual ~IODSessionManagerPb(void);

	IODSession* on_none_session_message(struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg);

	//·¢ËÍÏûÏ¢
	template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,  bool _is_packed>
	inline bool send_message_to(struct connection_info* conn_info, 
		const ::google::protobuf::internal::ExtensionIdentifier<com::iod::pb::common::BaseMsg, _proto_TypeTraits, _field_type, _is_packed>& id,	
		typename _proto_TypeTraits::ConstType msg)	
	{
		com::iod::pb::common::BaseMsg BaseMsg;
		BaseMsg.set_message_id(id.number());
		BaseMsg.MutableExtension(id)->CopyFrom(msg);
		return send_basemsg_to(conn_info, &BaseMsg);
	}

	virtual IODSession* on_none_session_packet(struct connection_info* conn_info, IODPacket* packet);

protected:

	typedef IODSession* (IODSessionManagerPb::*FNC_PB_MSG_HANDLER)(struct connection_info*, com::iod::pb::common::BaseMsg*);

	bool send_basemsg_to(struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg);

	static std::map< int, FNC_PB_MSG_HANDLER > *msg_handler_map;
};

#endif
