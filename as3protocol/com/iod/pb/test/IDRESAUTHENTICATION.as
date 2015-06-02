package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.ResAuthentication;
	import com.iod.pb.common.BaseMsg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const IDRESAUTHENTICATION:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test.idResAuthentication", "com.iod.pb.test.IDRESAUTHENTICATION", (1001 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.ResAuthentication);

	com.iod.pb.common.BaseMsg.extensionReadFunctions[(1001 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = IDRESAUTHENTICATION.read;

}
