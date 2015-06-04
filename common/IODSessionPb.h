#ifndef __IOD_SESSION_PB_H__
#define __IOD_SESSION_PB_H__

#include "IODSession.h"
#include "common/IODCommon.pb.h"

//ע����Ϣ����������
#define DEC_REG_PROTO_MSG_HANDLE(classname) \
protected: \
	static bool has_registered_msg_handle_of_##classname; \
	static void register_msg_handle(); \
	inline virtual void check_register_msg_handle() { if (!has_registered_msg_handle_of_##classname) classname::register_msg_handle(); }

//ע����Ϣ������ʵ��-��ʼ
#define REG_PROTO_MSG_HANDLE_BEGIN(classname, baseclass) \
bool classname::has_registered_msg_handle_of_##classname = false; \
void classname::register_msg_handle()\
{ \
	if (has_registered_msg_handle_of_##classname) \
		return; \
	if (!baseclass::msg_handler_map) \
		baseclass::msg_handler_map = new std::map< int, FNC_PB_MSG_HANDLER >; \
	std::map< int, FNC_PB_MSG_HANDLER >& m = *baseclass::msg_handler_map;

//ע����Ϣ������
#define ADD_PROTO_MSG_HANDLE(protocol_name, mapfun) \
	m[id##protocol_name.number()] = (FNC_PB_MSG_HANDLER)&mapfun;

//ע����Ϣ������ʵ��-����
#define REG_PROTO_MSG_HANDLE_END(classname) \
	has_registered_msg_handle_of_##classname = true; \
}

//-------------------------------------------------------------------------------

#define SAFE_GET_EXTENSION(msg, protocol_name, varname) \
	if (!msg->HasExtension(id##protocol_name)) \
		return; \
	const protocol_name& varname = msg->GetExtension(id##protocol_name);

//-------------------------------------------------------------------------------

#define SESSION_SEND_MESSAGE(protocol_name, var) send_message(id##protocol_name, var)

//-------------------------------------------------------------------------------

class IODSessionPb : public IODSession
{
	DEC_REG_PROTO_MSG_HANDLE(IODSessionPb)

public:

	IODSessionPb(void);

	virtual ~IODSessionPb(void);

	void on_message(com::iod::pb::common::BaseMsg* msg);

	//������Ϣ
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

	virtual void on_packet(IODPacket* packet);

protected:

	typedef void (IODSessionPb::*FNC_PB_MSG_HANDLER)(com::iod::pb::common::BaseMsg*);

	bool send_basemsg(com::iod::pb::common::BaseMsg* msg);

	static std::map< int, FNC_PB_MSG_HANDLER > *msg_handler_map;

};

#endif
