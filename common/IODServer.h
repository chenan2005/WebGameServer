//服务器框架

#ifndef __IOD_SERVER_H__
#define __IOD_SERVER_H__

#include "IODMicroHelper.h"

#define SERVER_INSTANCE(classname) ((classname*)classname::instance())

class IODServer
{
public:

	enum {
		CTRL_FLAG_QUIT = 1,
		CTRL_FLAG_RELOAD = 2,
	};

	static IODServer* instance() { return _server_instance; }

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

	IODServer(void) : ctrl_flag(0) { _server_instance = this; }

	virtual ~IODServer(void) {}

	/**
	*************************************************************
	initialize service involved
	*************************************************************
	*/

	//初始化运行环境
	virtual bool initialize_running_env();

	//初始化日志系统
	virtual bool initialize_log_system();

	//加载配置
	virtual bool load_config();

	//初始化服务器
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

	//初始化日志系统
	virtual void shutdown_log_system();

	//关闭服务器
	virtual void shutdown_server() = 0;


	/**
	*************************************************************
	protected members
	*************************************************************
	*/

	unsigned int ctrl_flag;

private:

	static IODServer* _server_instance;

	DISALLOW_COPY_AND_ASSIGN(IODServer);
};

#endif
