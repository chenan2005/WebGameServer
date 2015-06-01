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
	public dynamic final class res_authentication extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const RESULT:FieldDescriptor_TYPE_SINT32 = new FieldDescriptor_TYPE_SINT32("iod_pb.test.res_authentication.result", "result", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		private var result$field:int;

		private var hasField$0:uint = 0;

		public function clearResult():void {
			hasField$0 &= 0xfffffffe;
			result$field = new int();
		}

		public function get hasResult():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set result(value:int):void {
			hasField$0 |= 0x1;
			result$field = value;
		}

		public function get result():int {
			return result$field;
		}

		/**
		 *  @private
		 */
		public static const AUTHORIZATION:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("iod_pb.test.res_authentication.authorization", "authorization", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		private var authorization$field:String;

		public function clearAuthorization():void {
			authorization$field = null;
		}

		public function get hasAuthorization():Boolean {
			return authorization$field != null;
		}

		public function set authorization(value:String):void {
			authorization$field = value;
		}

		public function get authorization():String {
			return authorization$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasResult) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_SINT32(output, result$field);
			}
			if (hasAuthorization) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, authorization$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var result$count:uint = 0;
			var authorization$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (result$count != 0) {
						throw new flash.errors.IOError('Bad data format: res_authentication.result cannot be set twice.');
					}
					++result$count;
					this.result = com.netease.protobuf.ReadUtils.read_TYPE_SINT32(input);
					break;
				case 2:
					if (authorization$count != 0) {
						throw new flash.errors.IOError('Bad data format: res_authentication.authorization cannot be set twice.');
					}
					++authorization$count;
					this.authorization = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
