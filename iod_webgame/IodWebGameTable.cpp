#include "IodWebGameTable.h"
//-----------------------------------------------------------------------------------
IMPLEMENT_TABLE_INIT_BEGIN(STItemIndexData, ItemIndexData)
	IMPLEMENT_FIELD_INFO(STItemIndexData, m_ui64item_uid, IOD_FIELD_TYPE_UINT8, "item_uid", "NULL", IOD_FIELD_KEY_UNIQUE_0)
	IMPLEMENT_FIELD_INFO(STItemIndexData, m_ui32idx, IOD_FIELD_TYPE_UINT4, "idx", "NULL", IOD_FIELD_KEY_UNIQUE_0|IOD_FIELD_KEY_FILTER_0)
	IMPLEMENT_FIELD_INFO_EX(STItemIndexData, m_szdata, IOD_FIELD_TYPE_BLOB, "data", "NULL", IOD_FIELD_KEY_NONE, m_ui16dataLength)
IMPLEMENT_TABLE_INIT_END(STItemIndexData, ItemIndexData)
//-----------------------------------------------------------------------------------
IMPLEMENT_TABLE_INIT_BEGIN(STItemIndexValue, ItemIndexValue)
	IMPLEMENT_FIELD_INFO(STItemIndexValue, m_ui64item_uid, IOD_FIELD_TYPE_UINT8, "item_uid", "NULL", IOD_FIELD_KEY_UNIQUE_0)
	IMPLEMENT_FIELD_INFO(STItemIndexValue, m_ui32idx, IOD_FIELD_TYPE_UINT4, "idx", "NULL", IOD_FIELD_KEY_UNIQUE_0|IOD_FIELD_KEY_FILTER_0)
	IMPLEMENT_FIELD_INFO(STItemIndexValue, m_ui32value, IOD_FIELD_TYPE_UINT4, "value", "NULL", IOD_FIELD_KEY_FILTER_0)
IMPLEMENT_TABLE_INIT_END(STItemIndexValue, ItemIndexValue)
//-----------------------------------------------------------------------------------
IMPLEMENT_TABLE_INIT_BEGIN(STItemInfo, ItemInfo)
	IMPLEMENT_FIELD_INFO(STItemInfo, m_ui64uid, IOD_FIELD_TYPE_UINT8, "uid", "NULL", IOD_FIELD_KEY_UNIQUE_0|IOD_FIELD_KEY_AUTO_INC)
	IMPLEMENT_FIELD_INFO(STItemInfo, m_ui64owner_uid, IOD_FIELD_TYPE_UINT8, "owner_uid", "NULL", IOD_FIELD_KEY_UNIQUE_1)
	IMPLEMENT_FIELD_INFO(STItemInfo, m_ui32class_id, IOD_FIELD_TYPE_UINT4, "class_id", "NULL", IOD_FIELD_KEY_UNIQUE_1|IOD_FIELD_KEY_FILTER_0)
	IMPLEMENT_FIELD_INFO(STItemInfo, m_tmget_time, IOD_FIELD_TYPE_TIME, "get_time", "CURRENT_TIMESTAMP", IOD_FIELD_KEY_NONE)
	IMPLEMENT_FIELD_INFO(STItemInfo, m_ui64flags, IOD_FIELD_TYPE_UINT8, "flags", "0", IOD_FIELD_KEY_NONE)
	IMPLEMENT_FIELD_INFO(STItemInfo, m_ui32amount, IOD_FIELD_TYPE_UINT4, "amount", "0", IOD_FIELD_KEY_NONE)
IMPLEMENT_TABLE_INIT_END(STItemInfo, ItemInfo)
//-----------------------------------------------------------------------------------
IMPLEMENT_TABLE_INIT_BEGIN(STRoleIndexData, RoleIndexData)
	IMPLEMENT_FIELD_INFO(STRoleIndexData, m_ui64owner_uid, IOD_FIELD_TYPE_UINT8, "owner_uid", "NULL", IOD_FIELD_KEY_UNIQUE_0)
	IMPLEMENT_FIELD_INFO(STRoleIndexData, m_ui32idx, IOD_FIELD_TYPE_UINT4, "idx", "NULL", IOD_FIELD_KEY_UNIQUE_0|IOD_FIELD_KEY_FILTER_0)
	IMPLEMENT_FIELD_INFO_EX(STRoleIndexData, m_szdata, IOD_FIELD_TYPE_BLOB, "data", "NULL", IOD_FIELD_KEY_NONE, m_ui16dataLength)
IMPLEMENT_TABLE_INIT_END(STRoleIndexData, RoleIndexData)
//-----------------------------------------------------------------------------------
IMPLEMENT_TABLE_INIT_BEGIN(STRoleIndexValue, RoleIndexValue)
	IMPLEMENT_FIELD_INFO(STRoleIndexValue, m_ui64owner_uid, IOD_FIELD_TYPE_UINT8, "owner_uid", "NULL", IOD_FIELD_KEY_UNIQUE_0)
	IMPLEMENT_FIELD_INFO(STRoleIndexValue, m_ui32idx, IOD_FIELD_TYPE_UINT4, "idx", "NULL", IOD_FIELD_KEY_UNIQUE_0|IOD_FIELD_KEY_FILTER_0)
	IMPLEMENT_FIELD_INFO(STRoleIndexValue, m_ui32value, IOD_FIELD_TYPE_UINT4, "value", "NULL", IOD_FIELD_KEY_FILTER_0)
IMPLEMENT_TABLE_INIT_END(STRoleIndexValue, RoleIndexValue)
//-----------------------------------------------------------------------------------
IMPLEMENT_TABLE_INIT_BEGIN(STRoleInfo, RoleInfo)
	IMPLEMENT_FIELD_INFO(STRoleInfo, m_ui64uid, IOD_FIELD_TYPE_UINT8, "uid", "NULL", IOD_FIELD_KEY_UNIQUE_0|IOD_FIELD_KEY_AUTO_INC)
	IMPLEMENT_FIELD_INFO(STRoleInfo, m_szaccount, IOD_FIELD_TYPE_STRING, "account", "NULL", IOD_FIELD_KEY_UNIQUE_1)
	IMPLEMENT_FIELD_INFO(STRoleInfo, m_szname, IOD_FIELD_TYPE_STRING, "name", "NULL", IOD_FIELD_KEY_UNIQUE_2)
	IMPLEMENT_FIELD_INFO(STRoleInfo, m_tmcreate_time, IOD_FIELD_TYPE_TIME, "create_time", "CURRENT_TIMESTAMP", IOD_FIELD_KEY_NONE)
	IMPLEMENT_FIELD_INFO(STRoleInfo, m_ui64flags, IOD_FIELD_TYPE_UINT8, "flags", "0", IOD_FIELD_KEY_NONE)
IMPLEMENT_TABLE_INIT_END(STRoleInfo, RoleInfo)
//-----------------------------------------------------------------------------------
