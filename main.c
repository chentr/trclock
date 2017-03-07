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
#define DAY_PER_WEEK 7
struct Week_alarm{
	int week_day[DAY_PER_WEEK];//set 1 if this day want to be alarmed
	int hour;
	int min;
	int second;
};
enum ALARM_TYPE{
	AL_DISABLE,
	AL_ONETIME,
	AL_REPEAT,
	AL_WEEK,
};
struct Alarm{
	int type;
	time_t next_point;//next alarm point
	time_t repeat_time;//repeat per repeat_time. time_t == long int,means seconds.
	struct Week_alarm week_time;//alarm in a time of a week's specific days.
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
	int i;
	time_t now = time (NULL);;   
	struct tm *local=localtime(&now);
	for(i=0;i<MAX_CLOCK_NUM;i++)
	{
		//if need alarm clock 
		if(alarm[i].type > AL_DISABLE && (difftime(alarm[i].next_point,now ) < 5  &&  difftime(alarm[i].next_point,now ) > -5) )
		{
			//show alert betweent -5 to 5 second
			//3{
				//if it is one time clock
					//disable it
				//else if it is a repeat clock
					//set alarm to next point
			//3}
		
		}
	
	}
		//if a clock is out of time
			//3
}
