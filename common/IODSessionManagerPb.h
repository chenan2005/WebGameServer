#ifndef __IOD_SESSION_MANAGER_PB_H__
#define __IOD_SESSION_MANAGER_PB_H__

#include "IODSessionManager.h"
#include "IODSessionPb.h"

class IODSessionManagerPb 
	: public IODSessionManager
{
	DEC_PB_MSG_HANDLE(IODSessionManagerPb)

public:

	IODSessionManagerPb(void);

	virtual ~IODSessionManagerPb(void);

	IODSession* on_none_session_message(struct connection_info* conn_info, BaseMsgPb* msg);

	//·¢ËÍÏûÏ¢
	template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,  bool _is_packed>
	inline bool send_message_to(struct connection_info* conn_info, 
		const ::google::protobuf::internal::ExtensionIdentifier<BaseMsgPb, _proto_TypeTraits, _field_type, _is_packed>& id,	
		typename _proto_TypeTraits::ConstType msg)	
	{
		BaseMsgPb baseMsg;
		baseMsg.set_message_id(id.number());
		baseMsg.MutableExtension(id)->CopyFrom(msg);
		return send_basemsg_to(conn_info, &baseMsg);
	}

	virtual IODSession* on_none_session_packet(struct connection_info* conn_info, IODPacket* packet);

protected:

	bool send_basemsg_to(struct connection_info* conn_info, BaseMsgPb* msg);
};

#endif
