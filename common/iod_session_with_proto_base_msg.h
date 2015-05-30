#ifndef __IOD_SESSION_WITH_PROTO_BASE_MSG_H__
#define __IOD_SESSION_WITH_PROTO_BASE_MSG_H__

#include "iod_session.h"
#include "common/iod_common.pb.h"

//������Ϣ������ӳ���
#define DEC_PROTO_MSG_HANDLE_MAP(classname) \
protected: \
	typedef void (classname::*GProtoHandlerFunc)(iod::protobuf::common::base_msg*); \
	static std::map< int, GProtoHandlerFunc > msg_handler_map;

#define IMP_PROTO_MSG_HANDLE_MAP(classname) \
	std::map< int, classname::GProtoHandlerFunc > classname::msg_handler_map;

//ע����Ϣ����������
#define DEC_REG_PROTO_MSG_HANDLE(classname) \
private: \
class _register_of_##classname { \
public:\
	_register_of_##classname(); \
	~_register_of_##classname() {} \
}; \
	static _register_of_##classname _instance_of_regist_##classname;

//ע����Ϣ������ʵ��-��ʼ
#define REG_PROTO_MSG_HANDLE_BEGIN(classname, baseclass) \
	classname::_register_of_##classname::_register_of_##classname(){ \
	std::map< int, GProtoHandlerFunc >& m = baseclass::msg_handler_map; \

//ע����Ϣ������
#define ADD_PROTO_MSG_HANDLE(mapid, mapfun) \
	m[mapid] = (GProtoHandlerFunc)&mapfun;

//ע����Ϣ������ʵ��-����
#define REG_PROTO_MSG_HANDLE_END(classname) \
} \
	classname::_register_of_##classname classname::_instance_of_regist_##classname;

//-------------------------------------------------------------------------------

class iod_session_with_proto_base_msg : public iod_session
{
	DEC_PROTO_MSG_HANDLE_MAP(iod_session_with_proto_base_msg)

public:

	typedef void (iod_session_with_proto_base_msg::*FNC_PROTO_MSG_HANDLER)(iod::protobuf::common::base_msg*);

	iod_session_with_proto_base_msg(void);
	virtual ~iod_session_with_proto_base_msg(void);

	virtual void on_message(iod::protobuf::common::base_msg* msg) = 0;

	bool send_message(iod::protobuf::common::base_msg* msg);

	virtual void on_packet(iod_packet* packet);

};

#endif
