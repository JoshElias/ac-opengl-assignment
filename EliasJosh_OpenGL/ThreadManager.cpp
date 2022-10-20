#include "Common.h"

ThreadManager::ThreadManager()
{
	m_NumOfCores = NumOfCores();
}

int ThreadManager::NumOfCores()
{

	int numOfCores = 1;

	#ifdef _WIN64 || _WIN32
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	numOfCores = sysinfo.dwNumberOfProcessors;
	
#elif __APPLE__

#elif __linux

#elif __unix

#elif __posix

#endif

	return numOfCores;
	
}
