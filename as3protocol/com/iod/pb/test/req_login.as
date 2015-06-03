package com.iod.pb.test {
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
	public dynamic final class req_login extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const USERID:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("com.iod.pb.test.req_login.userid", "userid", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		private var userid$field:String;

		public function clearUserid():void {
			userid$field = null;
		}

		public function get hasUserid():Boolean {
			return userid$field != null;
		}

		public function set userid(value:String):void {
			userid$field = value;
		}

		public function get userid():String {
			return userid$field;
		}

		/**
		 *  @private
		 */
		public static const AUTHORIZATION:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("com.iod.pb.test.req_login.authorization", "authorization", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

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
			if (hasUserid) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, userid$field);
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
			var userid$count:uint = 0;
			var authorization$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (userid$count != 0) {
						throw new flash.errors.IOError('Bad data format: req_login.userid cannot be set twice.');
					}
					++userid$count;
					this.userid = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 2:
					if (authorization$count != 0) {
						throw new flash.errors.IOError('Bad data format: req_login.authorization cannot be set twice.');
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
