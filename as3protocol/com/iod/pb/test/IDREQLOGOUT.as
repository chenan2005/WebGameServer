package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.ReqLogout;
	import com.iod.pb.common.BaseMsg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const IDREQLOGOUT:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test.idReqLogout", "com.iod.pb.test.IDREQLOGOUT", (1006 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.ReqLogout);

	com.iod.pb.common.BaseMsg.extensionReadFunctions[(1006 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = IDREQLOGOUT.read;

}
