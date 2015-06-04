#ifndef __IOD_PACKET_H__
#define __IOD_PACKET_H__

#include "IODUtility.h"

#define _MAX_PACKET_LENGTH 32768u

class IODPacket
{
public:

	//�������ݴ�������ö��
	enum
	{
		READ_ERR_LENGTH_OVERFLOW = -1,	//�������
		READ_ERR_MEM_ERROR = -2,		//�ڴ����
		READ_ERR_PARSE_DATA_FAILED = -3,//��ȡ��Ϣʧ��
		READ_ERR_DECRYPT_FAILED = -4,	//����ʧ��
		READ_ERR_VERSION_ERROR = -5,	//��Ϣ�汾����
		READ_ERR_VALIDATE_ERROR = -6,	//����У�����
	};

	inline static IODPacket* create() {
		return new IODPacket;
	}

	inline static void destroy(IODPacket* packet) {
		delete packet;
	}

	inline virtual void set_data(const char* data, int length) {
		reset();
		this->data = (char*)malloc(length);
		memcpy(this->data, data, length);
		this->length = length;
	}

	inline int get_length() const {
		return this->length;
	}

	inline const char* get_data() const { 
		return this->data; 
	}

	virtual int read(struct bufferevent* bufev);

	virtual int write(struct bufferevent *bufev);

protected:

	IODPacket(void) : length(0), data(0) {}

	inline virtual ~IODPacket(void) {
		reset();
	}

	inline virtual void reset() {
		if (data)
			delete data;
		data = 0;
		length = 0;
	}

private:

	int packet_type;

	int length;

	char* data;
};

typedef IODPacket* (*FNC_PACKET_CONSTRUCTOR)();

#endif
