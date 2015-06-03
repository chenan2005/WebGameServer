package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.req_logout;
	import com.iod.pb.common.base_msg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const _REQ_LOGOUT:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test._req_logout", "com.iod.pb.test._REQ_LOGOUT", (1006 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.req_logout);

	com.iod.pb.common.base_msg.extensionReadFunctions[(1006 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = _REQ_LOGOUT.read;

}
