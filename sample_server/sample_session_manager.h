#pragma once
#include "iod_session_creator.h"

class sample_session_manager :
	public iod_session_creator
{
public:
	sample_session_manager(void);
	virtual ~sample_session_manager(void);
};
