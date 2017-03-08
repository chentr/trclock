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
#include <stdbool.h>
#include <apr-1.0/apr_time.h>
#define MAX_TIME_STRLEN 64
#define MAX_CLOCK_NUM 10
#define DAY_PER_WEEK 7
struct Week_alarm{
	bool wday[DAY_PER_WEEK];//set 1 if this day want to be alarmed
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
/*
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
*/

/*get current week day*/
int get_wday()
{
	time_t now = time (NULL);;   
	struct tm *local=localtime(&now);
	return local->tm_wday;/*0-6*/
}

int main()
{
	return 0;
}

//set to next alarm point or disable it*/
int reset_clock(struct Alarm alarm)
{
	int curr_wday;
	int j;
	//if it is one time clock
	if(AL_ONETIME == alarm.type)
	{
		//disable it
		alarm.type = AL_DISABLE;
	}
	//else if it is a repeat clock
	else if(AL_REPEAT == alarm.type)
	{
		//set alarm to next point
		alarm.next_point += alarm.repeat_time;
	}
	//else if it is a clock by week
	else if(AL_WEEK == alarm.type)
	{
		/*set alarm to next point*/
		//get current day of week
		curr_wday = get_wday();
		//find next alarm day of week
		for(j=curr_wday+1;j < DAY_PER_WEEK*2-1;j++)
		{
			if(true == alarm.week_time.wday[j/DAY_PER_WEEK])
			{
				//set next alarm
				alarm.next_point += (j-curr_wday)*24*3600;
			}
		}
	}
	else
	{
		printf("alarm type error!\n");
		return -1;
	}
	return 0;
}

void check_thread()
{
	// check all clocks's next point
	int i;
	time_t now = time (NULL);;   
	struct tm *local=localtime(&now);
	double diff;
	for(i=0;i<MAX_CLOCK_NUM;i++)
	{
		if(alarm[i].type > AL_DISABLE )
		{
			diff = difftime(now,alarm[i].next_point);
			//if need alarm clock 
			if(diff > -5 && diff < 5) 
			{
				//show alert betweent -5 to 5 second
				printf("alert!\n");
				reset_clock(alarm[i]);
			}
			//if a clock is out of date
			else if(diff > 5 )
			{
				reset_clock(alarm[i]);
			}
		}
	}
	apr_sleep(1000000);
}
