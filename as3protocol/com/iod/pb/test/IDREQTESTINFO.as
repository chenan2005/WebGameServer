package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.ReqTestInfo;
	import com.iod.pb.common.BaseMsg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const IDREQTESTINFO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test.idReqTestInfo", "com.iod.pb.test.IDREQTESTINFO", (1004 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.ReqTestInfo);

	com.iod.pb.common.BaseMsg.extensionReadFunctions[(1004 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = IDREQTESTINFO.read;

}
