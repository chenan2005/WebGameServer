//µ¥¼þÄ£°å

#ifndef __IOD_SINGLETON_H__
#define __IOD_SINGLETON_H__

#include "iod_micro_helper.h"

template <typename T> 
class iod_singleton
{
	DISALLOW_COPY_AND_ASSIGN(iod_singleton);

public:

	static T* instance()
	{
		if (m_instance == NULL) 
			m_instance = new T;
		return m_instance;
	}

	static void destroy()
	{
		delete m_instance;
		m_instance = 0;
	}

protected:

	iod_singleton() {}

	virtual ~iod_singleton() {}

private:

	static T* m_instance;
};

template <typename T> T* iod_singleton<T>::m_instance = 0;

#endif
