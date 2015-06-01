package iod_pb.test {
	import com.netease.protobuf.*;
	import com.netease.protobuf.fieldDescriptors.*;
	import iod_pb.test.req_logout;
	import iod_pb.common.base_msg;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(constant_metadata)
	/**
	 *  @private
	 */
	public const _REQ_LOGOUT:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("iod_pb.test._req_logout", "iod_pb.test._REQ_LOGOUT", (1006 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, iod_pb.test.req_logout);

	iod_pb.common.base_msg.extensionReadFunctions[(1006 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED] = _REQ_LOGOUT.read;

}
