#ifndef __IOD_SESSION_PB_H__
#define __IOD_SESSION_PB_H__

#include "iod_session.h"
#include "common/iod_common.pb.h"

//注册消息处理函数声明
#define DEC_REG_PROTO_MSG_HANDLE(classname) \
protected: \
	static bool has_registered_msg_handle_of_##classname; \
	static void register_msg_handle(); \
	inline virtual void check_register_msg_handle() { if (!has_registered_msg_handle_of_##classname) classname::register_msg_handle(); }

//注册消息处理函数实现-开始
#define REG_PROTO_MSG_HANDLE_BEGIN(classname, baseclass) \
bool classname::has_registered_msg_handle_of_##classname = false; \
void classname::register_msg_handle()\
{ \
	if (has_registered_msg_handle_of_##classname) \
		return; \
	if (!baseclass::msg_handler_map) \
		baseclass::msg_handler_map = new std::map< int, FNC_PB_MSG_HANDLER >; \
	std::map< int, FNC_PB_MSG_HANDLER >& m = *baseclass::msg_handler_map;

//注册消息处理函数
#define ADD_PROTO_MSG_HANDLE(mapid, mapfun) \
	m[mapid.number()] = (FNC_PB_MSG_HANDLER)&mapfun;

//注册消息处理函数实现-结束
#define REG_PROTO_MSG_HANDLE_END(classname) \
	has_registered_msg_handle_of_##classname = true; \
}

//-------------------------------------------------------------------------------

#define SAFE_GET_EXTENSION(msg, extname, varname) \
	if (!msg->HasExtension(_##extname)) \
		return; \
	const extname& varname = msg->GetExtension(_##extname);

//-------------------------------------------------------------------------------

class iod_session_pb : public iod_session
{
	DEC_REG_PROTO_MSG_HANDLE(iod_session_pb)

public:

	iod_session_pb(void);

	virtual ~iod_session_pb(void);

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

	typedef void (iod_session_pb::*FNC_PB_MSG_HANDLER)(iod::protobuf::common::base_msg*);

	bool send_base_msg(iod::protobuf::common::base_msg* msg);

	static std::map< int, FNC_PB_MSG_HANDLER > *msg_handler_map;

};

#endif
