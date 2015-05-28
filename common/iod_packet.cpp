#include "iod_packet.h"
#include "iod_common.h"

int iod_packet::read(struct bufferevent* bufev)
{
	struct evbuffer* buf = bufferevent_get_input(bufev);
	size_t buffer_len = evbuffer_get_length(buf);
	ev_uint16_t data_length = 0;
	ev_uint16_t packet_length = 0;

	//获得包长度
	if (buffer_len < sizeof(data_length))
		return 0;
	evbuffer_copyout(buf, &data_length, sizeof(data_length));
	data_length = ntohs(data_length);
	packet_length = data_length + sizeof(data_length);

	if (packet_length > _MAX_PACKET_LENGTH)
		return READ_ERR_LENGTH_OVERFLOW;
	if (buffer_len < packet_length)
		return 0; 

	//获得数据
	this->data = (char*)malloc(data_length);
	if (this->data == 0)
		return READ_ERR_MEM_ERROR;
	evbuffer_drain(buf, sizeof(data_length));
	evbuffer_remove(buf, this->data, data_length);
	this->length = data_length;

	return packet_length;
}

int iod_packet::write(struct bufferevent *bufev)
{
	ev_uint16_t data_length = htons((ev_uint16_t)this->length);
	if (bufferevent_write(bufev, &data_length, sizeof(ev_uint16_t)) == -1)
		return -1;
	return bufferevent_write(bufev, this->data, this->length);
}
