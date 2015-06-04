//µ¥¼þÄ£°å

#ifndef __IOD_SINGLETON_H__
#define __IOD_SINGLETON_H__

#include "IODMicroHelper.h"

template <typename T> 
class IODSingleton
{
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

	IODSingleton() {}

	virtual ~IODSingleton() {}

private:

	static T* m_instance;

	DISALLOW_COPY_AND_ASSIGN(IODSingleton);

};

template <typename T> T* IODSingleton<T>::m_instance = 0;

#endif
