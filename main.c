/* 	
	File Name 	: main .c 
	Author 		: Christoforos Apostolopoulos
	Project 	: Number -> 1 , Operating Systems 2018-2019
*/

#include <stdio.h> 		// 	Standard I/O
#include <stdlib.h>		//	rand(),...
#include <time.h>		// 	sleep(),...
#include <wait.h>		//	wait(),...
#include <unistd.h>		// 	fork(),...
#include <errno.h>		// 	errno...
#include <string.h>		// 	memcpy...
#include <sys/ipc.h>	//	ipc structs	
#include <sys/sem.h>	//	semaphores structs&func/s
#include <sys/shm.h>	//	shared memory structs&func/s
#include <sys/types.h>	//	var type def/s

#include "semaphores.h"				// Semaphores functions
#include "sharedMemory.h"			// Shared memory functions
#include "components_functions.h"	// Components & helpful functions


#define PROCESSES 4


int total_component_1 = 1000 + (NUM_COMPONENTS/3);
int total_component_2 = 2000 + (NUM_COMPONENTS/3);
int total_component_3 = 3000 + (NUM_COMPONENTS/3);

int num_component_1 = 1000;
int num_component_2 = 2000;
int num_component_3 = 3000;


int main(int argc,char *argv[])
{
	// Initialiaze variables that I'm going to use

	Components *shmaddr,*shmaddr_2,*shmaddr_3; 	// For Shared Memory addresses
	Components *total_comps[NUM_COMPONENTS]; 	// For fitting state

	int semid;									// For semaphores
	int ret;									// For the returns of functions
	int shmid,shmid_2,shmid_3; 					// For Shared Memory ids
	int offset = 0;								// For shmaddr_3
	int final_id = 1;							// Number of final total objects
	int childrens_pid[PROCESSES]; 				// Array of children pid
	int parent_pid;								// Hold parent's pid
	int total_paint_time = 0; 					// That's a variable that I'm going to hold the avg time from painter (a)

	double avg_final_time = 0;					// That's a variable that I'm going to hold the avg time of fitting for every object

	pid_t pid;									// For fork
	

	// SEMAPHORES


	// Create NUMBER_OF_SEMAPHORES semaphores
	printf("Creating %d semaphores with key %d\n", NUMBER_OF_SEMAPHORES, SEMAPHORE_KEY);
	semid = semaphore_Create(SEMAPHORE_KEY, NUMBER_OF_SEMAPHORES);
	printf("Got semid: %d\n", semid);


	// SET 1st semaphore's value to 0  (reading)
	printf("Setting semaphore %d to %d\n", SEMNUM, 0);
	ret = semaphore_Set_Value(semid, SEMNUM, 0);
	printf("Function was executed perfecty if number is 0: %d\n", ret);


	// SET 2nd semaphore's value to 1 (writing)
	printf("Setting semaphore %d to %d\n", SEMNUM+1, 1);
	ret = semaphore_Set_Value(semid, SEMNUM+1, 1);
	printf("Function was executed perfecty if number is 0: %d\n", ret);


	// SET 3rd semaphore's value to 0 (reading)
	printf("Setting semaphore %d to %d\n", SEMNUM+2, 0);
	ret = semaphore_Set_Value(semid, SEMNUM+2, 0);
	printf("Function was executed perfecty if number is 0: %d\n", ret);


	// SET 4th semaphore's value to 1 (writing)
	printf("Setting semaphore %d to %d\n", SEMNUM+3, 1);
	ret = semaphore_Set_Value(semid, SEMNUM+3, 1);
	printf("Function was executed perfecty if number is 0: %d\n", ret);


	// SET 5th semaphore's value to 0 (reading)
	printf("Setting semaphore %d to %d\n", SEMNUM+4, 0);
	ret = semaphore_Set_Value(semid, SEMNUM+4, 0);
	printf("Function was executed perfecty if number is 0: %d\n", ret);



	// SET 6th semaphore's value to 1 (writing) 
	printf("Setting semaphore %d to %d\n", SEMNUM+5, 1);
	ret = semaphore_Set_Value(semid, SEMNUM+5, 1);
	printf("Function was executed perfecty if number is 0: %d\n", ret);


	// SHARED MEMORY

	
	// CREATE a 1ST shared memory 
	printf("Creating shared memory with key '%d' of size %ld bytes.\n", SHM_KEY_1, sizeof(Components *));
	shmid = shared_Memory_Create(SHM_KEY_1, sizeof(Components *));
	printf("Got shmid: %d\n\n", shmid);

	// ATTACH
	printf("Attaching shared memory to address: %p\n", shmaddr);
	shmaddr = (Components *) shared_Memory_Attach(shmid);
	printf("Which now points to: %p\n\n", shmaddr);


	
	// CREATE a 2ND shared memory 
	printf("Creating shared memory with key '%d' of size %ld bytes.\n", SHM_KEY_2, sizeof(Components *));
	shmid_2 = shared_Memory_Create(SHM_KEY_2, sizeof(Components *));
	printf("Got shmid_2: %d\n\n", shmid_2);

	// ATTACH
	printf("Attaching shared memory to address: %p\n", shmaddr_2);
	shmaddr_2 = (Components *) shared_Memory_Attach(shmid_2);
	printf("Which now points to: %p\n\n", shmaddr_2);

	

	
	// CREATE a 3RD shared memory with key == 7 and size == 8
	printf("Creating shared memory with key '%d' of size %ld bytes.\n", SHM_KEY_3, NUM_COMPONENTS*sizeof(Components *));
	shmid_3 = shared_Memory_Create(SHM_KEY_3, NUM_COMPONENTS*sizeof(Components *));
	printf("Got shmid_3: %d\n\n", shmid_3);

	// ATTACH
	printf("Attaching shared memory to address: %p\n", shmaddr_3);
	shmaddr_3 = (Components *) shared_Memory_Attach(shmid_3);
	printf("Which now points to: %p\n\n", shmaddr_3);



	
	find_WhoAmI("parent");				// Print Parent process

	
	parent_pid = getpid();				// Get parent pid (we nned that for wait , dettach/deallocates)
	
		
	
	for(int i = 0; i < PROCESSES; i++)	// For each PROCESS (== 8)
	{
		
		pid = fork();					// Create a process
		
		if(pid == -1)					// Case -1:	-- ERROR
		{
			
			perror("File name:main.c---->Fork has been failed\n");
			exit(1);
				
		}
		else if(pid == 0)				// Child case:Print & Get current process's pid
		{
					
			find_WhoAmI("child");
			childrens_pid[i] = getpid();
			break;
		}
	}
	
	
	if(getpid() == parent_pid)			// If current pid is Parent
	{
		
		for(int i=0;i<PROCESSES;i++)	// wait all children
		{
			wait(NULL);
		}
		
   		// Delete semaphores
		printf("Deleting semaphores... \n");	
		ret = semaphore_Delete(semid);
		
		// Detach 1st
		printf("Detatching shared memory from address: %p\n", shmaddr);
		ret = shared_Memory_Detach(shmaddr);
		
		// Detach 2nd 
		printf("Detatching shared memory from address: %p\n", shmaddr_2);
		ret = shared_Memory_Detach(shmaddr_2);
		
		// Detach 3rd
		printf("Detatching shared memory from address: %p\n", shmaddr_3);
		ret = shared_Memory_Detach(shmaddr_3);
		

		// Delete 1st shared memory
		printf("Deleting shared memory... \n");
		ret = shared_Memory_Delete(shmid);
		

		// Delete 2nd shared memory
		printf("Deleting shared memory... \n");
		ret = shared_Memory_Delete(shmid_2);
		

		// Delete 3rd shared memory
		printf("Deleting shared memory... \n");
		ret = shared_Memory_Delete(shmid_3);
				
		
	}
	else 													// if current pid is child
	{
		sleep(1);
		srand(time(NULL));					
			
		
		if(getpid() == childrens_pid[0]) 					// Component's constructor
		{
						
	   		int i = 0;										// Initialize i
	 
			while(i < NUM_COMPONENTS)						// for each component
			{
				int compType;
				
				ret = semaphore_Locking(semid, SEMNUM+1);	// Locking semaphore : 1 (writing semaphore)
								
				while(1)									// I call a rand() from 1 to 3 and I check if I can create 
				{
					compType = rand()%3 +1;
					if(compType == 1 && (num_component_1 < total_component_1))		// Component type 1
					{
						create_component(shmaddr,1);
						break;						
					}
					else if(compType == 2 && (num_component_2 < total_component_2)) // Component type 2
					{
						create_component(shmaddr,2);
						break;						
					}
					else if(compType == 3 && (num_component_3 < total_component_3)) // Component type 3
					{
						create_component(shmaddr,3);			
						break;
					}
					else if((num_component_1 + 1 < total_component_1) && (num_component_2 + 1 < total_component_2) && (num_component_3 + 1 < total_component_3))
					{
						break;
					}
					
				}
			
				ret = semaphore_Unlocking(semid, SEMNUM);	 // Unlocking semaphore: 0 (reading semaphore)
				
										
				sleep(0.1);
				i++;
			}
			sleep(5);
			exit(5);
		}
				
	else if(getpid() == childrens_pid[1]) 					// Painter 
	{
		sleep(1.4);											// To let child 1 create a component
		
					
	  	int i = 0;
	  	
	   
		while(i < NUM_COMPONENTS)							// For each component
		{
			
			
			ret = semaphore_Locking(semid, SEMNUM);			// Locking semaphore : 0 (reading semaphore)
			
			paint_component(shmaddr);						// Paint component
		
			ret = semaphore_Locking(semid, SEMNUM+3);		// Locking semaphore : 3 (writing semaphore)
			
			shmaddr_2 -> id = shmaddr->id;					// Copy shmaddr to shmaddr_2
			shmaddr_2 -> type = shmaddr->type;	
			shmaddr_2 -> paint_time = shmaddr-> paint_time;
			shmaddr_2 -> check_time = shmaddr-> check_time;
			shmaddr_2 -> painted = shmaddr-> painted;
			shmaddr_2 -> tbegin = shmaddr -> tbegin;
			shmaddr_2 -> tfinish = shmaddr -> tfinish;

			total_paint_time += shmaddr_2 -> paint_time; 	// Increase paint_time for (a)
			
			ret = semaphore_Unlocking(semid, SEMNUM+2);		// Unlocking semaphore: 2 (reading semaphore)
				
			sleep(0.1);
			
			ret = semaphore_Unlocking(semid, SEMNUM+1);	 	// Unlocking semaphore: 1 (writing semaphore)	
			
			i++;
			sleep(1);
						
		}
		
		total_paint_time /= NUM_COMPONENTS;					// Print painting AVG time 
		printf("AVG painting time: %d ms\n",total_paint_time);

		sleep(5);	
		exit(10);
	}
	else if(getpid() == childrens_pid[2])					// Checker
	{
		sleep(2);
					
	  	int i = 0;
	  	
		while(i < NUM_COMPONENTS)							// For each component
		{
						
			ret = semaphore_Locking(semid, SEMNUM+2);		// Locking semaphore : 2 (reading semaphore)
						
			check_component(shmaddr_2);						// Check Component
			
			ret = semaphore_Locking(semid, SEMNUM+5);		// Locking semaphore : 5 (writing semaphore)
			
			shmaddr_3[offset].id = shmaddr_2 -> id;			// Copy shmaddr_2 to shmaddr_3[offset]
			shmaddr_3[offset].type = shmaddr_2 -> type;
			shmaddr_3[offset].paint_time = shmaddr_2 -> paint_time;
			shmaddr_3[offset].check_time = shmaddr_2 -> check_time;
			shmaddr_3[offset].painted = shmaddr_2 -> painted;
			shmaddr_3[offset].tbegin = shmaddr_2 -> tbegin;
			shmaddr_3[offset].tfinish = shmaddr_2 -> tfinish;

			offset++;										// Increase offset
			
			ret = semaphore_Unlocking(semid, SEMNUM+4);		// Unlocking semaphore: 4 (reading semaphore)
					
			ret = semaphore_Unlocking(semid, SEMNUM+3);		// Unlocking semaphore: 3 (writing semaphore)
			i++;
			sleep(1);
			
				
		}
		sleep(1);
		exit(10);
	}
	else if(getpid() == childrens_pid[3])					// Fitter
	{
		sleep(4);
	
		int i = 0;

	  	double current_min_time = 0;  						// For (b)
	  	double current_time = 0;							// For (b)

		while(i < NUM_COMPONENTS)
		{
			
			ret = semaphore_Locking(semid, SEMNUM+4);
			
			offset++;
			int t1 = 0,t2 = 0,t3 = 0;
			int pos1 = 0, pos2 = 0, pos3 = 0;

			for(int j = 0; j < offset; j++)						// I put components in shmaddr_3 which is sizeof NUM_COMPONENTS*(Components* = 8) and now I'm checking if I have 3 different components to create a final object
			{
				
				if( (shmaddr_3[j].type == 1) && (t1 == 0))		// If current component is type 1 and its the 1st one of the shmaddr_3 then:
				{
					t1++;
					pos1 = j;					
				}
				else if( (shmaddr_3[j].type == 2) && (t2 == 0))	// If current component is type 2 and its the 1st one of the shmaddr_3 then:
				{				
					t2++;
					pos2 = j;					
				}
				else if( (shmaddr_3[j].type == 3) && (t3 == 0))	// If current component is type 3 and its the 1st one of the shmaddr_3 then:
				{
					t3++;
					pos3 = j;
				}
				if( (t1 == 1) && (t2 == 1) && (t3 == 1))		// If statement is true: We found the oldest 3 components with different types(1, 2, 3).
				{
					printf("\nA final component has been created with ID:%d\n\n",final_id);

					if( (shmaddr_3[pos1].tbegin < shmaddr_3[pos2].tbegin) && (shmaddr_3[pos1].tbegin < shmaddr_3[pos3].tbegin))			// Component type 1 is the oldest comp ftom other 2 
					{
						current_min_time = shmaddr_3[pos1].tbegin;
					}
					else if( (shmaddr_3[pos2].tbegin < shmaddr_3[pos1].tbegin) && (shmaddr_3[pos2].tbegin < shmaddr_3[pos3].tbegin))	// Component type 2 is the oldest comp ftom other 2 
					{
						current_min_time = shmaddr_3[pos2].tbegin;
					}
					else if( (shmaddr_3[pos3].tbegin < shmaddr_3[pos1].tbegin) && (shmaddr_3[pos3].tbegin < shmaddr_3[pos1].tbegin))	// Component type 3 is the oldest comp ftom other 2 
					{
						current_min_time = shmaddr_3[pos3].tbegin;
					}
					current_time = clock();								// Get current time
						
					avg_final_time += current_time - current_min_time;	// Its not the final
					
					initial_component(shmaddr_3,pos1);					// Remove these components from shmaddr_3 
					initial_component(shmaddr_3,pos2);
					initial_component(shmaddr_3,pos3);
					pos1 = 0, pos2 = 0, pos3 = 0;						// Initialize flags and positions
					t1 = 0,t2 = 0,t3 = 0;

					final_id++;											// Increase final object id by 1
					
				}

			}
			
			sleep(0.1);	
					
			ret = semaphore_Unlocking(semid, SEMNUM+5);					// Unlocking semaphore: 5 (writing semaphore)
			i++;
			sleep(2);
		}

		avg_final_time /= (NUM_COMPONENTS/3); 
		printf("avg time %lf ms\n",avg_final_time);
		sleep(1);
		exit(10);
	}
}

return 0;
}






