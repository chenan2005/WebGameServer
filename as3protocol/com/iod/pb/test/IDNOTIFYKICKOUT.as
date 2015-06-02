package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.NotifyKickout;
	import com.iod.pb.common.BaseMsg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const IDNOTIFYKICKOUT:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test.idNotifyKickout", "com.iod.pb.test.IDNOTIFYKICKOUT", (1009 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.NotifyKickout);

	com.iod.pb.common.BaseMsg.extensionReadFunctions[(1009 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = IDNOTIFYKICKOUT.read;

}
