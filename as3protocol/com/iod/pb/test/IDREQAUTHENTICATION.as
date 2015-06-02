package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.ReqAuthentication;
	import com.iod.pb.common.BaseMsg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const IDREQAUTHENTICATION:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test.idReqAuthentication", "com.iod.pb.test.IDREQAUTHENTICATION", (1000 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.ReqAuthentication);

	com.iod.pb.common.BaseMsg.extensionReadFunctions[(1000 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = IDREQAUTHENTICATION.read;

}
