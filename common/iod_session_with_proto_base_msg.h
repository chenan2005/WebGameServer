#ifndef __IOD_SESSION_WITH_PROTO_BASE_MSG_H__
#define __IOD_SESSION_WITH_PROTO_BASE_MSG_H__

#include "iod_session.h"
#include "common/iod_common.pb.h"

//声明消息处理函数映射表
#define DEC_PROTO_MSG_HANDLE_MAP(classname) \
protected: \
	typedef void (classname::*GProtoHandlerFunc)(iod::protobuf::common::base_msg*); \
	static std::map< int, GProtoHandlerFunc > msg_handler_map;

#define IMP_PROTO_MSG_HANDLE_MAP(classname) \
	std::map< int, classname::GProtoHandlerFunc > classname::msg_handler_map;

//注册消息处理函数声明
#define DEC_REG_PROTO_MSG_HANDLE(classname) \
private: \
class _register_of_##classname { \
public:\
	_register_of_##classname(); \
	~_register_of_##classname() {} \
}; \
	static _register_of_##classname _instance_of_regist_##classname;

//注册消息处理函数实现-开始
#define REG_PROTO_MSG_HANDLE_BEGIN(classname, baseclass) \
	classname::_register_of_##classname::_register_of_##classname(){ \
	std::map< int, GProtoHandlerFunc >& m = baseclass::msg_handler_map; \

//注册消息处理函数
#define ADD_PROTO_MSG_HANDLE(mapid, mapfun) \
	m[mapid.number()] = (GProtoHandlerFunc)&mapfun;

//注册消息处理函数实现-结束
#define REG_PROTO_MSG_HANDLE_END(classname) \
} \
	classname::_register_of_##classname classname::_instance_of_regist_##classname;

//-------------------------------------------------------------------------------

#define SAFE_GET_EXTENSION(msg, extname, varname) \
	if (!msg->HasExtension(_##extname)) \
		return; \
	const extname& varname = msg->GetExtension(_##extname);

//-------------------------------------------------------------------------------

class iod_session_with_proto_base_msg : public iod_session
{
	DEC_PROTO_MSG_HANDLE_MAP(iod_session_with_proto_base_msg)

public:

	typedef void (iod_session_with_proto_base_msg::*FNC_PROTO_MSG_HANDLER)(iod::protobuf::common::base_msg*);

	iod_session_with_proto_base_msg(void);
	virtual ~iod_session_with_proto_base_msg(void);

	void on_message(iod::protobuf::common::base_msg* msg);

	//发送消息
	template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,  bool _is_packed>
	inline bool send_message(
		const ::google::protobuf::internal::ExtensionIdentifier<iod::protobuf::common::base_msg, _proto_TypeTraits, _field_type, _is_packed>& id,	
		typename _proto_TypeTraits::ConstType msg)	
	{
		iod::protobuf::common::base_msg base_msg;
		base_msg.set_messge_id(id.number());
		base_msg.MutableExtension(id)->CopyFrom(msg);
		return send_base_msg(&base_msg);
	}

	virtual void on_packet(iod_packet* packet);

protected:

	bool send_base_msg(iod::protobuf::common::base_msg* msg);

};

#endif
