#ifndef __IOD_SESSION_PB_H__
#define __IOD_SESSION_PB_H__

#include "IODSession.h"
#include "IODMicroHelperPb.h"
#include "common/IODCommon.pb.h"

#define SESSION_SEND_MESSAGE(protocol_name, var) send_message(id##protocol_name, var)

class IODSessionPb 
	: public IODSession
{
	DEC_PB_MSG_HANDLE(IODSessionPb)

public:

	IODSessionPb(void);

	virtual ~IODSessionPb(void);

	//发送消息
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

	//发送消息
	template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,  bool _is_packed>
	inline bool send_message(
		const ::google::protobuf::internal::ExtensionIdentifier<com::iod::pb::common::BaseMsg, _proto_TypeTraits, _field_type, _is_packed>& id,	
		typename _proto_TypeTraits::ConstType msg)	
	{
		com::iod::pb::common::BaseMsg BaseMsg;
		BaseMsg.set_message_id(id.number());
		BaseMsg.MutableExtension(id)->CopyFrom(msg);
		return send_basemsg(&BaseMsg);
	}

protected:

	void on_message(com::iod::pb::common::BaseMsg* msg);

	bool send_basemsg(com::iod::pb::common::BaseMsg* msg);

	bool send_basemsg_to(struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg);

	virtual void on_packet(IODPacket* packet);
};

#endif
