package iod_pb.test {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class res_test_response_time extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const REQ_TIMESTAMP:FieldDescriptor_TYPE_SINT64 = new FieldDescriptor_TYPE_SINT64("iod_pb.test.res_test_response_time.req_timestamp", "reqTimestamp", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var reqTimestamp:Int64;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_SINT64(output, this.reqTimestamp);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var req_timestamp$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (req_timestamp$count != 0) {
						throw new flash.errors.IOError('Bad data format: res_test_response_time.reqTimestamp cannot be set twice.');
					}
					++req_timestamp$count;
					this.reqTimestamp = com.netease.protobuf.ReadUtils.read_TYPE_SINT64(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
