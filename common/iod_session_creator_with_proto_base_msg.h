#ifndef __IOD_SESSION_CREATOR_WITH_PROTO_BASE_MSG_H__
#define __IOD_SESSION_CREATOR_WITH_PROTO_BASE_MSG_H__

#include "iod_session_creator.h"
#include "iod_session_with_proto_base_msg.h"

//������Ϣ��������ӳ���
#define DEC_NON_SESSION_PROTO_MSG_HANDLE_MAP(classname) \
protected: \
	typedef iod_session* (classname::*GProtoHandlerFunc)(struct connection_info*, iod::protobuf::common::base_msg*); \
	static std::map< int, GProtoHandlerFunc > msg_handler_map;

//-------------------------------------------------------------------------------

#define SAFE_GET_NONE_SESSION_EXTENSION(msg, extname, varname) \
	if (!msg->HasExtension(_##extname)) \
		return 0; \
	const extname& varname = msg->GetExtension(_##extname);

//-------------------------------------------------------------------------------

class iod_session_creator_with_proto_base_msg : public iod_session_creator
{
	DEC_NON_SESSION_PROTO_MSG_HANDLE_MAP(iod_session_creator_with_proto_base_msg)

public:
	iod_session_creator_with_proto_base_msg(void);
	virtual ~iod_session_creator_with_proto_base_msg(void);

	iod_session* on_none_session_message(struct connection_info* conn_info, iod::protobuf::common::base_msg* msg);

	//������Ϣ
	template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,  bool _is_packed>
	inline bool send_message_to(struct connection_info* conn_info, 
		const ::google::protobuf::internal::ExtensionIdentifier<iod::protobuf::common::base_msg, _proto_TypeTraits, _field_type, _is_packed>& id,	
		typename _proto_TypeTraits::ConstType msg)	
	{
		iod::protobuf::common::base_msg base_msg;
		base_msg.set_messge_id(id.number());
		base_msg.MutableExtension(id)->CopyFrom(msg);
		return send_base_msg_to(conn_info, &base_msg);
	}

	virtual iod_session* on_none_session_packet(struct connection_info* conn_info, iod_packet* packet);

protected:

	bool send_base_msg_to(struct connection_info* conn_info, iod::protobuf::common::base_msg* msg);
};

#endif