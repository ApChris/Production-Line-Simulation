#include "components_functions.h"


// Initialize a component considering from type 
void create_component(Components *c, int type)
{

	if(type == 1)	// If Component type is 1
	{
		printf("Component type 1 has been CREATED with id:%d!\n",num_component_1);
		c -> id = num_component_1;
		c -> paint_time = 0;
		c -> check_time = 0;
		c -> painted = 0;
		c -> type = type;
		c -> tbegin = clock();
		c -> tfinish = (double)0;
		num_component_1++;
	}
	else if(type == 2)	// If Component type is 2
	{
		printf("Component type 2 has been CREATED with id:%d!\n",num_component_2);
		c -> id = num_component_2;
		c -> paint_time = 0;
		c -> check_time = 0;
		c -> painted = 0;
		c -> type = type;
		c -> tbegin = clock();
		c -> tfinish = (double)0;
		num_component_2++;
	}
	else if(type == 3)	// If Component type is 3
	{
		printf("Component type 3 has been CREATED with id:%d!\n",num_component_3);
		c -> id = num_component_3;
		c -> paint_time = 0;
		c -> check_time = 0;
		c -> painted = 0;
		c -> type = type;
		c -> tbegin = clock();
		c -> tfinish = (double)0;
		num_component_3++;
	}
	else	
	{
		printf("That component does not exist\n");
	}
	
	
}


// Paint a component considering from type 
void paint_component(Components *c)
{
	
	if(c->type == 1)		// If Component type is 1
	{
		printf("Component type 1 has been PAINTED with id:%d!\n",c->id);		
		c -> painted = 1;
		c -> paint_time = COMPONENT_1_PAINT;
	}
	else if(c->type == 2)	// If Component type is 2
	{
		printf("Component type 2 has been PAINTED with id:%d!\n",c->id);
		c -> painted = 1;
		c -> paint_time = COMPONENT_2_PAINT;
	}
	else if(c->type == 3)	// If Component type is 3
	{
		printf("Component type 3 has been PAINTED with id:%d!\n",c->id);
		c -> painted = 1;
		c -> paint_time = COMPONENT_3_PAINT;
	}
	else
	{
		printf("That component does not exist\n");
	}

}

// Check a component considering from type 
void check_component(Components *c)
{
	
	if(c->type == 1)		// If Component type is 1
	{
		printf("Component type 1 has been CHECKED with id:%d!\n",c->id);				
		c -> check_time = COMPONENT_1_CHECK;
	}
	else if(c->type == 2)	// If Component type is 2
	{
		printf("Component type 2 has been CHECKED with id:%d!\n",c->id);
		c -> check_time = COMPONENT_2_CHECK;
	}
	else if(c->type == 3)	// If Component type is 3
	{
		printf("Component type 3 has been CHECKED with id:%d!\n",c->id);
		c -> check_time = COMPONENT_3_CHECK;
	}
	else
	{
		printf("That component does not exist\n");
	}

}

// Initialize a component , I need that for shmaddr_3,because its different size from others SMs
void initial_component(Components *c,int i)
{	
	c[i].id = 0;
	c[i].paint_time = 0;
	c[i].check_time = 0;
	c[i].painted = 0;
	c[i].type = 0;
	c[i].tbegin = 0;
	c[i].tfinish = 0;	
}


// A function that prints the pid and ppid of current proces
int find_WhoAmI(const char *string)
{
	printf("I am %s and my pid is:%lu . My parent's pid is:%lu\n",string,(long)getpid(),(long)getppid());
	return 10;
}

