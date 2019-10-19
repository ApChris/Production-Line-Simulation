#ifndef __components_functions__
#define __components_functions__
#include <stdio.h>
#include <time.h>
#include <unistd.h>				// 	getpid(),...
#define NUM_COMPONENTS 9

#define COMPONENT_1_PAINT 2		// 1st Component's time for painting
#define COMPONENT_2_PAINT 4 	// 2nd Component's time for painting
#define COMPONENT_3_PAINT 6 	// 3rd Component's time for painting

#define COMPONENT_1_CHECK 1 	// 1st Component's time for checking
#define COMPONENT_2_CHECK 3 	// 2nd Component's time for checking
#define COMPONENT_3_CHECK 5 	// 3rd Component's time for checking		


// Component's struct
typedef struct
{
	int id;
	int paint_time;
	int check_time;
	int type;
	int painted;
	clock_t tbegin;
	clock_t tfinish;
}Components;


int total_component_1;
int total_component_2;
int total_component_3;

int num_component_1;
int num_component_2;
int num_component_3;

void create_component(Components *c, int type);
void paint_component(Components *c);
void check_component(Components *c);
void initial_component(Components *c,int i);
int find_WhoAmI(const char *string);



#endif

