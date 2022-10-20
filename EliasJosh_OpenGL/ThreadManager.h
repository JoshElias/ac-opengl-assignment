
#ifndef _THREAD_MANAGER_H
#define _THREAD_MANAGER_H

class ThreadManager 
{
private:
	ThreadManager();
	int m_NumOfCores;

public:
	static ThreadManager& Instance() { static ThreadManager tm; return tm; }

	int NumOfCores();


};

#endif
