package com.iod.pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import com.iod.pb.test.req_authentication;
	import com.iod.pb.common.base_msg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const _REQ_AUTHENTICATION:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("com.iod.pb.test._req_authentication", "com.iod.pb.test._REQ_AUTHENTICATION", (1000 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, com.iod.pb.test.req_authentication);

	com.iod.pb.common.base_msg.extensionReadFunctions[(1000 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = _REQ_AUTHENTICATION.read;

}
