package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.TestMsg6;
	import com.iod.pb.common.BaseMsg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const IDTESTMSG6:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test.idTestMsg6", "com.iod.pb.test.IDTESTMSG6", (5006 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.TestMsg6);

	com.iod.pb.common.BaseMsg.extensionReadFunctions[(5006 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = IDTESTMSG6.read;

}
