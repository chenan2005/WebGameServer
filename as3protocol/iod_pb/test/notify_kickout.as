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
	public dynamic final class notify_kickout extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const KICK_REASON:FieldDescriptor_TYPE_SINT32 = new FieldDescriptor_TYPE_SINT32("iod_pb.test.notify_kickout.kick_reason", "kickReason", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		private var kick_reason$field:int;

		private var hasField$0:uint = 0;

		public function clearKickReason():void {
			hasField$0 &= 0xfffffffe;
			kick_reason$field = new int();
		}

		public function get hasKickReason():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set kickReason(value:int):void {
			hasField$0 |= 0x1;
			kick_reason$field = value;
		}

		public function get kickReason():int {
			return kick_reason$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasKickReason) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_SINT32(output, kick_reason$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var kick_reason$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (kick_reason$count != 0) {
						throw new flash.errors.IOError('Bad data format: notify_kickout.kickReason cannot be set twice.');
					}
					++kick_reason$count;
					this.kickReason = com.netease.protobuf.ReadUtils.read_TYPE_SINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
