/*
	1.must can run in Linux and Win.use cross-platform library ,such as gtk+,apr.  
	2.write GUI for it.
	clock about specific time, clock from current time
*/

// get user's input 
	//check if set  clock ,or modify clock , delete clock

// check all clocks's next point
	//if need alarm clock 
		//show alert betweent -5 to 5 second
		//3{
			//if it is one time clock
				//disable it
			//else if it is a repeat clock
				//set alarm to next point
		//3}
	//if a clock is out of time
		//3
#include <stdio.h>		
#include <stdlib.h>		
#include <string.h>		
#include <time.h>		
#define MAX_TIME_STRLEN 64
#define MAX_CLOCK_NUM 10
struct Alarm{
	time_t next_point;//next alarm point
} alarm[MAX_CLOCK_NUM];
void show_time()
{
	time_t now = time (NULL);;   
	char time_str[MAX_TIME_STRLEN];
	struct tm *local=localtime(&now);
	//difftime
	printf("current time is :%s\n",ctime(&now));
	printf("Local hour is: %d\n",local->tm_hour);
	return;
}

int main()
{
	show_time();
	return 0;
}

void check_thread()
{
	// check all clocks's next point
		//if need alarm clock 
			//show alert betweent -5 to 5 second
			//3{
				//if it is one time clock
					//disable it
				//else if it is a repeat clock
					//set alarm to next point
			//3}
		//if a clock is out of time
			//3
}
