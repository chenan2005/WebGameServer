#ifndef __IOD_PACKET_H__
#define __IOD_PACKET_H__

#include <queue>

#define _MAX_PACKET_LENGTH 32768u

class iod_packet;

typedef std::queue< iod_packet* > packet_sequence;

typedef iod_packet* (*FNC_PACKET_CONSTRUCTOR)();

class iod_packet
{
public:

	//解析数据错误类型枚举
	enum 
	{
		READ_ERR_LENGTH_OVERFLOW = -1,	//长度溢出
		READ_ERR_MEM_ERROR = -2,		//内存错误
		READ_ERR_PARSE_DATA_FAILED = -3,//读取消息失败
		READ_ERR_DECRYPT_FAILED = -4,	//解密失败
		READ_ERR_VERSION_ERROR = -5,	//消息版本错误
		READ_ERR_VALIDATE_ERROR = -6,	//数据校验错误
	};

	static iod_packet* create() { return new iod_packet; }

	virtual ~iod_packet(void) { if (data) delete data; }

	virtual int read(struct bufferevent* bufev);

	virtual int write(struct bufferevent *bufev);

	int get_length() const { return this->length; }

	const char* get_data() const { return this->data; }

protected:

	iod_packet(void) : length(0), data(0) {}


private:

	int packet_type;

	int length;

	char* data;
};

#endif
