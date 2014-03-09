/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * CPE 101 - 3
 * Assignment 5 - Ray_caster Main
 */

#include <stdio.h>
#include "commandline.h"

#define MAX_SPHERES 10000

int main(int argc, char * argv[])
{
   struct sphere spheres[MAX_SPHERES];

   add_flags(argc, argv, spheres);

   return 0;
}
