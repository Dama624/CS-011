#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void)
{
  int n;
  int i;
  char name[100];
  srand(time(0));
  printf("Enter your first name: ");
  scanf("%99s", name);
  n = rand() % (10) + 1;
  for (i = 0; i < n; i++)
    {
      /* I wanted to try to put the printed string
       * into a variable before the for loop, but
       * doing
       * "char greet[]=("%d: hello, %s!\n", n, name)"
       * wasn't valid; I'm a little uncomfortable with
       * the fact that this loop checks if n is even
       * or odd in every loop of the for loop. I
       * would've liked to check before the loop, put
       * the appropriate greeting into a string, then
       * simply print the string n times.
       */
      if (n % 2 == 0)
	{
	 printf("%d: hello, %s!\n", n, name);
	}
      else
	{
	printf("%d: hi there, %s!\n", n, name);
	}
    }
  return 0;
}
