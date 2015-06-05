#ifndef __iod_pb_msg_handler_H__
#define __iod_pb_msg_handler_H__

#include "common/IODCommon.pb.h"

//-------------------------------------------------------------------------------
//ע����Ϣ����������
#define DEC_PB_MSG_HANDLE(classname) \
public:\
	virtual void* dispatch_base_msg(struct connection_info* from, com::iod::pb::common::BaseMsg*); \
private: \
	typedef void* (classname::*FNC_PB_MSG_HANDLER)(struct connection_info* from, com::iod::pb::common::BaseMsg*); \
	static void register_msg_handle_of_##classname(); \
	static bool has_registered_msg_handle_of_##classname; \
	static std::map< int, classname::FNC_PB_MSG_HANDLER > *msg_handler_map_of_##classname;

//-------------------------------------------------------------------------------
//ע����Ϣ������ʵ��-��ʼ
#define REG_PB_MSG_HANDLE_BEGIN(classname) \
bool classname::has_registered_msg_handle_of_##classname = false; \
std::map< int, classname::FNC_PB_MSG_HANDLER > * classname::msg_handler_map_of_##classname = 0; \
void* classname::dispatch_base_msg(struct connection_info* from, com::iod::pb::common::BaseMsg* msg) {\
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

//-------------------------------------------------------------------------------
//ע����Ϣ������ʵ�֣��̳и������Ϣ�����߼���-��ʼ
#define REG_PB_MSG_HANDLE_INHERIT_BEGIN(classname) \
bool classname::has_registered_msg_handle_of_##classname = false; \
std::map< int, classname::FNC_PB_MSG_HANDLER > * classname::msg_handler_map_of_##classname = 0; \
void* classname::dispatch_base_msg(struct connection_info* from, com::iod::pb::common::BaseMsg* msg) {\
	__super::dispatch_base_msg(from, msg); \
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

//-------------------------------------------------------------------------------
//ע����Ϣ������
#define ADD_PB_MSG_HANDLE(protocol_name, mapfun) \
	m[id##protocol_name.number()] = &mapfun;

//-------------------------------------------------------------------------------
//ע����Ϣ������ʵ��-����
#define REG_PB_MSG_HANDLE_END() \
	to_set_var = true; \
}

//-------------------------------------------------------------------------------
//ע����Ϣ������ʵ�֣��̳и������Ϣ�����߼���-����
#define REG_PB_MSG_HANDLE_INHERIT_END() \
	to_set_var = true; \
}

//-------------------------------------------------------------------------------
//������������ȡ��Ϣ��Extension���ñ���
#define SAFE_GET_EXTENSION(msg, protocol_name, varname) \
	if (!msg->HasExtension(id##protocol_name)) \
		return 0; \
	const protocol_name& varname = msg->GetExtension(id##protocol_name);

//-------------------------------------------------------------------------------
//�ַ���Ϣ
#define DISPATCH_BASE_MSG(from, msg) dispatch_base_msg(from, msg)

//�ַ���Ϣ
#define DISPATCH_MSG(handler, from, protocolname, msg) {\
	BaseMsgPb baseMsg; \
	baseMsg.set_message_id(id##protocolname.number()); \
	baseMsg.MutableExtension(id##protocolname)->CopyFrom(msg); \
	(handler)->dispatch_base_msg(from, &baseMsg);\
}

//-------------------------------------------------------------------------------
//������Ϣ
#define SEND_MESSAGE_TO(conn_info, protocol_name, var) send_message_to(conn_info, id##protocol_name, var)

typedef com::iod::pb::common::BaseMsg BaseMsgPb;

#endif
