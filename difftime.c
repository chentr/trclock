#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
   time_t first, second;

   first = time(NULL);  /* Gets system
      time */
   sleep(3);
   second = time(NULL); /* Gets system time
      again */

   printf("The difference(2nd,1st) is: %f  seconds\n",difftime(second,first));
   printf("The difference(1st,2nd) is: %f  seconds\n",difftime(first,second));

   return 0;
}
