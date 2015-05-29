#include "test_helper.h"
#include "iod_packet.h"

test_helper::test_helper(void)
{
}

test_helper::~test_helper(void)
{
}

bool test_helper::check_cmd( iod_packet* packet, const char* cmd )
{
	int cmd_length = (int)strlen(cmd);
	return (packet->get_length() >= cmd_length && memcmp(packet->get_data(), cmd, cmd_length) == 0);
}
