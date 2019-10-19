#include "sharedMemory.h"

int shared_Memory_Get(key_t key, int size)
{
	int shmid;
	
	if ((shmid = shmget(key, size, 0666)) == -1)
		return -1;

	return shmid;
}

int shared_Memory_Create(key_t key, int size)
{
	int shmid;

	if ((shmid = shmget(key, size, IPC_CREAT | 0666)) == -1)
		return -1;

	return shmid;
}

void* shared_Memory_Attach(int shmid)
{
	return shmat(shmid, 0, 0);
}

int shared_Memory_Detach(const void* shmaddr)
{
	if( shmdt(shmaddr) == -1 )
		return errno;

	return 0;
}

int shared_Memory_Delete(int shmid)
{
	if( shmctl(shmid, IPC_RMID, 0) == -1 )
		return errno;

	return 0;
}
