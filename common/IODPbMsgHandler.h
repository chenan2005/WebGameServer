#ifndef __iod_pb_msg_handler_H__
#define __iod_pb_msg_handler_H__

#include "common/IODCommon.pb.h"

//注册消息处理函数声明
#define DEC_PB_MSG_HANDLE(classname) \
protected: \
	static bool has_registered_msg_handle_of_##classname; \
	static void register_msg_handle_of_##classname(); \
	typedef void* (classname::*FNC_PB_MSG_HANDLER)(struct connection_info* from, com::iod::pb::common::BaseMsg*); \
	virtual void* dispatch_pb_msg(struct connection_info* from, com::iod::pb::common::BaseMsg*); \
private: \
	static std::map< int, classname::FNC_PB_MSG_HANDLER > *msg_handler_map_of_##classname;


//注册消息处理函数实现-开始
#define REG_PB_MSG_HANDLE_BEGIN(classname) \
std::map< int, classname::FNC_PB_MSG_HANDLER > * classname::msg_handler_map_of_##classname = 0; \
bool classname::has_registered_msg_handle_of_##classname = false; \
void* classname::dispatch_pb_msg(struct connection_info* from, com::iod::pb::common::BaseMsg* msg) {\
	if (inherit_pb_msg_handle()) __super::dispatch_pb_msg(from, msg); \
	register_msg_handle_of_##classname();\
	std::map< int, classname::FNC_PB_MSG_HANDLER >::iterator it = msg_handler_map_of_##classname->find(msg->message_id()); \
	if (it == msg_handler_map_of_##classname->end()) return 0;\
	return (this->*(it->second))(from, msg);\
}\
void classname::register_msg_handle_of_##classname() { \
	if (has_registered_msg_handle_of_##classname) return;\
	msg_handler_map_of_##classname = new std::map< int, classname::FNC_PB_MSG_HANDLER >; \
	std::map< int, classname::FNC_PB_MSG_HANDLER >& m = *msg_handler_map_of_##classname; \
	bool& to_set_var = classname::has_registered_msg_handle_of_##classname;

//注册消息处理函数
#define ADD_PB_MSG_HANDLE(protocol_name, mapfun) \
	m[id##protocol_name.number()] = &mapfun;

//注册消息处理函数实现-结束
#define REG_PB_MSG_HANDLE_END() \
	to_set_var = true; \
}

//不继承继承父类的消息处理函数
#define NOT_INHERIT_PB_MSG_HANDLE() \
protected:\
	inline bool inherit_pb_msg_handle() { return false; }

//-------------------------------------------------------------------------------

#define SAFE_GET_EXTENSION(msg, protocol_name, varname) \
	if (!msg->HasExtension(id##protocol_name)) \
		return; \
	const protocol_name& varname = msg->GetExtension(id##protocol_name);

//-------------------------------------------------------------------------------

class IODPbMsgHandler
{
public:

	IODPbMsgHandler(void);

	virtual ~IODPbMsgHandler(void);

	inline bool inherit_pb_msg_handle() { return true; }

	inline virtual void* dispatch_pb_msg(struct connection_info*, com::iod::pb::common::BaseMsg*){ return 0; }

};

#endif
