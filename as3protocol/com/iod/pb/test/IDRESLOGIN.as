package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.ResLogin;
	import com.iod.pb.common.BaseMsg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const IDRESLOGIN:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test.idResLogin", "com.iod.pb.test.IDRESLOGIN", (1003 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.ResLogin);

	com.iod.pb.common.BaseMsg.extensionReadFunctions[(1003 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = IDRESLOGIN.read;

}
