#ifndef __semaphores__
#define __semaphores__
#include <stdio.h>
#include <errno.h>		// 	errno...
#include <sys/sem.h>	//	semaphores structs&func/s

#define SEMAPHORE_KEY 16984	//
#define NUMBER_OF_SEMAPHORES 10
#define SEMNUM 0
#define READING_SEMAPHORE 0
#define WRITING_SEMAPHORE 1


union semun
{
  int val;               
  struct semid_ds *buf;  
  ushort  *array;                        
  struct seminfo *__buf;  
};


int semaphore_Create(key_t key, int num_of_sem);


int semaphore_Get(key_t key, int number_of_sem);


int semaphore_Delete(int semid);

int semaphore_Set_Value(int semid, int semaphore_number, int value);



int semaphore_Locking(int semid, int semaphore_number);


int semaphore_Unlocking(int semid, int semaphore_number);

#endif