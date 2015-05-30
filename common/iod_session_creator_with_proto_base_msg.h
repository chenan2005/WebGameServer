#ifndef __IOD_SESSION_CREATOR_WITH_PROTO_BASE_MSG_H__
#define __IOD_SESSION_CREATOR_WITH_PROTO_BASE_MSG_H__

#include "iod_session_creator.h"
#include "iod_session_with_proto_base_msg.h"

//������Ϣ������ӳ���
#define DEC_NON_SESSION_PROTO_MSG_HANDLE_MAP(classname) \
protected: \
	typedef iod_session* (classname::*GProtoHandlerFunc)(struct connection_info*, iod::protobuf::common::base_msg*); \
	static std::map< int, GProtoHandlerFunc > msg_handler_map;



class iod_session_creator_with_proto_base_msg : public iod_session_creator
{
	DEC_NON_SESSION_PROTO_MSG_HANDLE_MAP(iod_session_creator_with_proto_base_msg)

public:
	iod_session_creator_with_proto_base_msg(void);
	virtual ~iod_session_creator_with_proto_base_msg(void);

	iod_session* on_none_session_message(struct connection_info* conn_info, iod::protobuf::common::base_msg* msg);

	virtual iod_session* on_none_session_packet(struct connection_info* conn_info, iod_packet* packet);
};

#endif
