#ifndef __sharedMemory__
#define __sharedMemory__
#include <stdio.h>
#include <errno.h>		// 	errno...
#include <sys/shm.h>	//	shared memory structs&func/s
#define SHM_KEY_1 7629
#define SHM_KEY_2 1459
#define SHM_KEY_3 568962


int shared_Memory_Get(key_t key, int size);

int shared_Memory_Create(key_t key, int size);
int shared_Memory_Delete(int shmid);

void * shared_Memory_Attach(int shmid);
int shared_Memory_Detach(const void* shmaddr);

#endif