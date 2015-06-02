package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.ResTestResponseTime;
	import com.iod.pb.common.BaseMsg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const IDRESTESTRESPONSETIME:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test.idResTestResponseTime", "com.iod.pb.test.IDRESTESTRESPONSETIME", (1008 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.ResTestResponseTime);

	com.iod.pb.common.BaseMsg.extensionReadFunctions[(1008 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = IDRESTESTRESPONSETIME.read;

}
