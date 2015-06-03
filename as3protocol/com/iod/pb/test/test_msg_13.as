package com.iod.pb.test {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import flash.utils.ByteArray;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class test_msg_13 extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const TEST_DATA:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("com.iod.pb.test.test_msg_13.test_data", "testData", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		private var test_data$field:flash.utils.ByteArray;

		public function clearTestData():void {
			test_data$field = null;
		}

		public function get hasTestData():Boolean {
			return test_data$field != null;
		}

		public function set testData(value:flash.utils.ByteArray):void {
			test_data$field = value;
		}

		public function get testData():flash.utils.ByteArray {
			return test_data$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasTestData) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, test_data$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var test_data$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (test_data$count != 0) {
						throw new flash.errors.IOError('Bad data format: test_msg_13.testData cannot be set twice.');
					}
					++test_data$count;
					this.testData = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
