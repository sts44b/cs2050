/*Multi function program to error check, square and cube*/

#include <stdio.h>

int check_number(float y );
float square(float y);
float cube(float y);

int main()
{
   float x;

   printf("Enter a number: ");
   scanf("%f", &x);

   while (check_number (x) == 0)
   {
      printf("Invalid. Enter a number from -100 to 100: ");
      scanf("%f", &x);
   }

   printf("\nThe number entered is %.2f", x);
   printf("\nSquare of %.2f is %.2f", x, square(x));
   printf("\nCube of %.2f is %.2f", x, cube(x));

return 0;
}   

int check_number(float y)
{
   if (y >= -100 && y <= 100)
      return 1;
   else
      return 0;
}

float square (float y)
{
   return y * y;
}
   printf("Enter a number: ");
   printf("Enter a number: ");
   printf("Enter a number: ");

float cube (float y)
{
   return y * y * y;
}











