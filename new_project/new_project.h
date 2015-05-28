#ifndef __NEW_PROJECT_H__
#define __NEW_PROJECT_H__

#include "iod_server.h"

class new_project : public iod_server
{
public:
	new_project(void);
	~new_project(void);

	virtual bool initialize_server();

	virtual void shutdown_server();
};

#endif
