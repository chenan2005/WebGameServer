package iod_pb.common {
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
	public dynamic final class base_msg extends com.netease.protobuf.Message {
		[ArrayElementType("Function")]
		public static const extensionReadFunctions:Array = [];

		/**
		 *  @private
		 */
		public static const FROM:FieldDescriptor_TYPE_SINT32 = new FieldDescriptor_TYPE_SINT32("iod_pb.common.base_msg.from", "from", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		private var from$field:int;

		private var hasField$0:uint = 0;

		public function clearFrom():void {
			hasField$0 &= 0xfffffffe;
			from$field = new int();
		}

		public function get hasFrom():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set from(value:int):void {
			hasField$0 |= 0x1;
			from$field = value;
		}

		public function get from():int {
			return from$field;
		}

		/**
		 *  @private
		 */
		public static const TO:FieldDescriptor_TYPE_SINT32 = new FieldDescriptor_TYPE_SINT32("iod_pb.common.base_msg.to", "__to", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		private var to$field:int;

		public function clearTo():void {
			hasField$0 &= 0xfffffffd;
			to$field = new int();
		}

		public function get hasTo():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set __to(value:int):void {
			hasField$0 |= 0x2;
			to$field = value;
		}

		public function get __to():int {
			return to$field;
		}

		/**
		 *  @private
		 */
		public static const FLAGS:FieldDescriptor_TYPE_SINT32 = new FieldDescriptor_TYPE_SINT32("iod_pb.common.base_msg.flags", "flags", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		private var flags$field:int;

		public function clearFlags():void {
			hasField$0 &= 0xfffffffb;
			flags$field = new int();
		}

		public function get hasFlags():Boolean {
			return (hasField$0 & 0x4) != 0;
		}

		public function set flags(value:int):void {
			hasField$0 |= 0x4;
			flags$field = value;
		}

		public function get flags():int {
			return flags$field;
		}

		/**
		 *  @private
		 */
		public static const MESSGE_ID:FieldDescriptor_TYPE_SINT32 = new FieldDescriptor_TYPE_SINT32("iod_pb.common.base_msg.messge_id", "messgeId", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var messgeId:int;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasFrom) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_SINT32(output, from$field);
			}
			if (hasTo) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_SINT32(output, to$field);
			}
			if (hasFlags) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_SINT32(output, flags$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_SINT32(output, this.messgeId);
			for (var fieldKey:* in this) {
				super.writeExtensionOrUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var from$count:uint = 0;
			var to$count:uint = 0;
			var flags$count:uint = 0;
			var messge_id$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (from$count != 0) {
						throw new flash.errors.IOError('Bad data format: base_msg.from cannot be set twice.');
					}
					++from$count;
					this.from = com.netease.protobuf.ReadUtils.read_TYPE_SINT32(input);
					break;
				case 2:
					if (to$count != 0) {
						throw new flash.errors.IOError('Bad data format: base_msg.__to cannot be set twice.');
					}
					++to$count;
					this.__to = com.netease.protobuf.ReadUtils.read_TYPE_SINT32(input);
					break;
				case 3:
					if (flags$count != 0) {
						throw new flash.errors.IOError('Bad data format: base_msg.flags cannot be set twice.');
					}
					++flags$count;
					this.flags = com.netease.protobuf.ReadUtils.read_TYPE_SINT32(input);
					break;
				case 4:
					if (messge_id$count != 0) {
						throw new flash.errors.IOError('Bad data format: base_msg.messgeId cannot be set twice.');
					}
					++messge_id$count;
					this.messgeId = com.netease.protobuf.ReadUtils.read_TYPE_SINT32(input);
					break;
				default:
					super.readExtensionOrUnknown(extensionReadFunctions, input, tag);
					break;
				}
			}
		}

	}
}
