#include <stdio.h>
#include <assert.h>

/* calculate_Easter_date: Takes integer input "year" and outputs an integer
 * value. The output's value represents the day; the sign represents the
 * month. If the sign is negative, the month is March; otherwise it is April.
 * 
 * year: integer input that represents the year for which the day of Easter
 * is calculated. The allowable years are from 1582 to 39999.
 */
int calculate_Easter_date (int year);
int calculate_Easter_date (int year)
{
  int golden, century, skipleap, correct, marchsun, epact, marchmoon;
  int result;
  if (year < 1582 || year > 39999)
    {
      return 0;
    }
  golden = (year % 19) + 1; /* golden: integer that calculates the "golden
                             * year" in the 19-year Metonic cycle. */
  century = (year / 100) + 1; /* century: integer that calculates the
                               * "century"th century. */
  skipleap = (3 * century / 4) - 12; /* skipleap: integer that calculates
                                      * the skipped leap years. */
  correct = ((8 * century + 5) / 25) - 5; /* correct: int that calculates
                                           * the correction factor for the
                                           * moon's orbit. */
  marchsun = (5 * year / 4) - skipleap - 10; /* marchsun:
                                              * March ((-marchsun) mod 7
                                              * +7) is a Sunday. */
  epact = (11 * golden + 20 + correct - skipleap) % 30;
  /* epact: specifies when a full moon occurs. */
  if ((epact == 25 && golden > 11) || epact == 24)
  {
    epact++;
  }
  marchmoon = 44 - epact; /* marchmoon: March "marchmoon" is the
                           * "calendar full moon". */
  if (marchmoon < 21) /* The following calculations are done to determine what
                       * day is the Sunday after a full moon. */
    {
      marchmoon += 30;
    }
  marchmoon = marchmoon + 7 - ((marchsun + marchmoon) % 7);
  result = marchmoon;
  if (marchmoon > 31)
    {
      result -= 31;
      return result;
    }
  else
    {
      result = -result;
      return result;
    }
}

int main(void)
{
  int zeller;
  int year; /* year: The year read from the input file. */
  int check; /* check: Checks if the End of File is reached. */
  int result; /* result: result of passing "year" through
               * calculate_Easter_date. */
  int month; /* month = 3 if March, = 4 if April. Required for Zeller's
              * Congruence. */
  while (1)
  {
    check = scanf("%d", &year);
    if (check == EOF) /* Check if program reached the end of the input
                      * file. */
    {
      break;
    }
    result = calculate_Easter_date(year);
    if (result == 0) /* Check if input year is within 1582-39999. */
    {
      fprintf(stderr, "%d is not a valid input year! (Input between 1582 and \
39999)\n", year);
    }
    else /* Outputs into an output file a line in the format:
          * "year - month day". */
    {
      if (result < 0) /* If calculate_Easter_date outputs a negative value,
                       * the month is March; otherwise the month is April. */
      {
        result = -result;
        month = 3;
        printf("%d - March %d\n", year, result);
      }
      else
      {
        month = 4;
        printf("%d - April %d\n", year, result);
      }
                  /* Extra credit! Using Zeller's Congruence to test whether
                   * the day lands on a Sunday. */
      zeller = (result + ((13 * (month + 1)) / 5) + (year % 100) \
                + ((year % 100)/4) + ((year / 100) / 4) \
                - ((year / 100) * 2)) % 7;
      assert(zeller = 1);
    }
  }
}
