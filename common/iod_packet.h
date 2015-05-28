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
