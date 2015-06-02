package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.ResTestInfo;
	import com.iod.pb.common.BaseMsg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const IDRESTESTINFO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test.idResTestInfo", "com.iod.pb.test.IDRESTESTINFO", (1005 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.ResTestInfo);

	com.iod.pb.common.BaseMsg.extensionReadFunctions[(1005 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = IDRESTESTINFO.read;

}
