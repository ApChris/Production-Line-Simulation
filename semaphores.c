#include "semaphores.h"

int semaphore_Create(key_t key, int number_of_sem)
{
  int semid;

  if( (semid = semget(key, number_of_sem, 0666 | IPC_CREAT)) == -1)
    return -1;

  return semid;
}

             
int semaphore_Delete(int semid)
{
  union semun arg;

  return semctl(semid, 0, IPC_RMID, arg);
}

                      
int semaphore_Set_Value(int semid, int semaphore_number, int value)
{
  union semun arg;
  arg.val = value;

  return semctl(semid, semaphore_number, SETVAL, arg);
}


                   
int semaphore_Locking(int semid, int semaphore_number)
{
  struct sembuf sops;
  sops.sem_num = semaphore_number;
  sops.sem_op = 1;
  sops.sem_flg = SEM_UNDO;
  return semop(semid, &sops, 1);
}



int semaphore_Unlocking(int semid, int semaphore_number)
{
  struct sembuf sops;
  sops.sem_num = semaphore_number;
  sops.sem_op = -1;
  sops.sem_flg = SEM_UNDO;
  return semop(semid, &sops, 1);
}

int semaphore_Get(key_t key, int number_of_sem)
{
  int semid;

  if( (semid = semget(key, number_of_sem, 0666)) == -1 )
    return -1;

  return semid;
}