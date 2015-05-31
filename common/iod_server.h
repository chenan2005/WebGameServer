//���������

#ifndef __IOD_SERVER_H__
#define __IOD_SERVER_H__

#define implement_server_instance(classname)  classname __instance_of_##classname

class iod_server
{
public:

	enum {
		CTRL_FLAG_QUIT = 1,
		CTRL_FLAG_RELOAD = 2,
	};

	static iod_server* instance() { return _server_instance; }

	bool initialize();

	int update();

	void shutdown();

	bool check_flag(unsigned int flag);

	void set_flag(unsigned int flag);

	void clear_flag(unsigned int flag);

	virtual void on_winsys_kbhit(int c);

	virtual bool reload_config() { return true; }

	virtual void print_startup_info();

	virtual void print_help_info();

protected:

	iod_server(void) : ctrl_flag(0) { _server_instance = this; }

	virtual ~iod_server(void) {}

	/**
	*************************************************************
	initialize service involved
	*************************************************************
	*/

	//��ʼ�����л���
	virtual bool initialize_running_env();

	//��ʼ����־ϵͳ
	virtual bool initialize_log_system();

	//��������
	virtual bool load_config();

	//��ʼ��������
	virtual bool initialize_server() = 0;

	/**
	*************************************************************
	update involved
	*************************************************************
	*/
	
	virtual int update_server() = 0;
	
	/**
	*************************************************************
	shutdown service involved
	*************************************************************
	*/

	//��ʼ����־ϵͳ
	virtual void shutdown_log_system();

	//�رշ�����
	virtual void shutdown_server() = 0;

	/**
	*************************************************************
	others
	*************************************************************
	*/


	unsigned int ctrl_flag;

private:

	iod_server(const iod_server&) {}

	static iod_server* _server_instance;
};

#endif
