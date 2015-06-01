package iod_pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import iod_pb.test.req_authentication;
	import iod_pb.common.base_msg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const _REQ_AUTHENTICATION:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("iod_pb.test._req_authentication", "iod_pb.test._REQ_AUTHENTICATION", (1000 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, iod_pb.test.req_authentication);

	iod_pb.common.base_msg.extensionReadFunctions[(1000 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = _REQ_AUTHENTICATION.read;

}
