#include <stdio.h>

int main(void)
{
    int a = 1023; /* simple integer type */
    char c = 'a'; /* character type */
    char s[] = "Hello"; /* string up to 256 characters */
    /* 'initializing' : truncation from 'const double' to 'float' */
    float f = 3.14159; /* float point type */
    printf ("a = %d\n", a); // decimal output
    printf ("c = %c\n", c); // ASCCII string output
    printf ("s = %s\n", s); // ASCII string output
    printf ("f = %f\n", f); // floating output
    printf ("a = %7d\n", a); // use a field width of 7
    printf ("a = %-7d\n", a); // left justify in a field of 7
    printf ("f = %.3f\n", f); // use 3 decimal places
    return 0;
}