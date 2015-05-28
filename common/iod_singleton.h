//µ¥¼þÄ£°å

#ifndef __IOD_SINGLETON_H__
#define __IOD_SINGLETON_H__

template <typename T> 
class iod_singleton
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

	iod_singleton() {}

	virtual ~iod_singleton() {}

private:

	iod_singleton(const iod_singleton&) 	{}

	static T* m_instance;
};

template <typename T> T* iod_singleton<T>::m_instance = 0;

#endif
