/*
	1.must can run in Linux and Win.use cross-platform library ,such as gtk+,apr.  
	2.write GUI for it.
	clock about specific time, clock from current time
*/
#include <stdio.h>		
#include <stdlib.h>		
#include <string.h>		
#include <time.h>		
#include <stdbool.h>
#include <apr-1.0/apr_time.h>
#define MAX_TIME_STRLEN 64
#define MAX_CLOCK_NUM 10
#define DAY_PER_WEEK 7
#define MAX_PERLINE 128
struct Week_alarm{
	bool wday[DAY_PER_WEEK];//set 1 if this day want to be alarmed
	int hour;
	int min;
	int sec;
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

/*get current week day*/
int get_wday()
{
	time_t now = time (NULL);;   
	struct tm *local=localtime(&now);
	return local->tm_wday;/*0-6*/
}

void print_alarm()
{
    printf("--------------------------current alarms---------------------------\n");
    int i,j;
    struct tm *p;
    for(i=0;i<MAX_CLOCK_NUM;i++)
    {
        if(AL_ONETIME == alarm[i].type)
        {
            printf("id=%d,type:onetime alarm \n",i);
            printf("next alarm time:\t%s\n",ctime(&alarm[i].next_point));
            printf("\n");
        }
        else if(AL_REPEAT == alarm[i].type)
        {
            printf("id=%d,type:repeat per duration\n",i);
            printf("next alarm time:\t%s\n",ctime(&alarm[i].next_point));
            p=gmtime(&alarm[i].next_point);
            printf("repeat period:\t%d day;%d:%d:%d\n",p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
            printf("\n");
        }
        else if(AL_WEEK == alarm[i].type)
        {
            printf("id=%d,type:in time of weekday\n",i);
            printf("next alarm time:\t%s\n",ctime(&alarm[i].next_point));
            printf("in these day of a week:\t");
            for(j=0;j<DAY_PER_WEEK;j++)
            {
                if(true == alarm[i].week_time.wday[j])
                {
                    printf("%d\t",j+1);
                }
            }
            printf("\n");
            printf("alarm time:%d:%d:%d\t",alarm[i].week_time.hour,alarm[i].week_time.min,alarm[i].week_time.sec);
            printf("\n");
        }
    }
    printf("--------------------------current alarms end-----------------------\n");

}

void print_help()
{
    printf("--------------------------command list---------------------------\n");
    printf("<clock_id> <type> <time>\n");
    printf("<clock_id> = 0-9\n");
    printf("type: 0 disable , 1 one time, 2 repeat per time, 3 time by week.\n");
    printf("type=0(disable): <time> not need\n");
    printf("type=1(one time): <time> = <yyyy,mm,dd,hh,mm,ss>.\n");
    printf("type=2(repeat per time): <time> <yyyy,mm,dd,hh,mm,ss,d,hh,mm,ss>,at most 9 days.\n");
    printf("type=3(time by week): <time> <hhmmss,[1234567]>.\n");
    printf("--------------------------command list end-----------------------\n");
    printf("[user input]:");
    return ;
}

void handle_cmd()
{
    char cmd[MAX_PERLINE];
    int clock_id;
    int type;
    char time_cmd[MAX_PERLINE];
    struct tm time;
    fgets(cmd,MAX_PERLINE-1,stdin);
    scanf("%d %d %s\n", &clock_id, &type, time_cmd);
    if(clock_id<0 || clock_id>9 || type < AL_DISABLE ||type > AL_WEEK)
    {
        printf("cmd error,wrong clock_id or type\n");
        return ;
    }
    alarm[clock_id].type = type;
    if(AL_ONETIME == type)
    {
        sscanf(time_cmd,"%d,%d,%d,%d,%d,%d",&(time.tm_year),&(time.tm_mon),&(time.tm_mday),&(time.tm_hour),&(time.tm_min),&(time.tm_sec));
    }
	else if(AL_REPEAT == type)
    {
    
    }
	else if(AL_WEEK == type)
    {

    }
	

}

int user_inter()
{
    while(1)
    {
        print_alarm();
        print_help();
        handle_cmd();
    }
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

int main()
{
    user_inter();
	return 0;
}
