package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.res_login;
	import com.iod.pb.common.base_msg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const _RES_LOGIN:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test._res_login", "com.iod.pb.test._RES_LOGIN", (1003 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.res_login);

	com.iod.pb.common.base_msg.extensionReadFunctions[(1003 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = _RES_LOGIN.read;

}
