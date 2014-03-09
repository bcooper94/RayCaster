/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * CPE 101 - 3
 * Assignment 5 - Unit Tests
 */

#include <stdio.h>
#include "commandline.h"
#include "checkit.h"

#define MAX_SPHERES 10000
#define MAX_VALS 50

void get_input_tests()
{
   int sCreated1, sCreated2;
   struct sphere spheres1[MAX_SPHERES];
   struct sphere spheres2[MAX_SPHERES];
   int num_args = 2;
   char *filename1 = "spheres.in";
   char *filename2 = "spheres2.in";

   sCreated1 = get_input(num_args, filename1, spheres1);
   sCreated2 = get_input(num_args, filename2, spheres2);
   //get_input(num_args, filename, spheres2);

   checkit_int(sCreated1, 2);
   checkit_double(spheres1[0].center.x, 1.0);
   checkit_double(spheres1[0].center.y, 1.0);
   checkit_double(spheres1[0].center.z, 0.0);
   checkit_double(spheres1[1].center.x, 8.0);
   checkit_double(spheres1[1].center.y, -10.0);
   checkit_double(spheres1[1].center.z, 110.0);
   /* spheres2[2] and spheres2[3]
    * 8.0 9.0 11.0 2.0 1.0 0.0 1.0 0.2 0.4 0.5 0.09
    * 3.0 3.0 100.0 3.0 0.2 0.2 0.6 0.4 0.8 0.0 0.05
    */
   checkit_int(sCreated2, 4);
   checkit_double(spheres2[2].center.x, 8.0);
   checkit_double(spheres2[2].center.y, 9.0);
   checkit_double(spheres2[2].center.z, 11.0);
   checkit_double(spheres2[3].center.x, 3.0);
   checkit_double(spheres2[3].center.y, 3.0);
   checkit_double(spheres2[3].center.z, 100.0);
}

void get_vals_tests()
{
   int index1, index2, index3, index4;
   double vals1[MAX_VALS];
   double vals2[MAX_VALS];
   double vals3[MAX_VALS];
   double vals4[MAX_VALS];
   char * string1[] = {"./a.out", "spheres.in", "-eye",
                       "-45.6", "3.5", "-21.0"};
   char * string2[] = {"./a.out", "spheres.in", "-eye",
                       "2345.6", "-342.1", "908.0"};
   char * string3[] = {"./a.out", "spheres.in", "-eye",
                       "23.0", "14", "-12", "-light",
                       "114.1", "321.0", "14.5",
                       "0.14", "0.956", "1.156"};
   char * string4[] = {"./a.out", "spheres.in", "-eye",
                       "23.0", "14", "-12", "-light",
                       "114.1", "321.0", "14.5",
                       "0.14", "0.956", "1.156", "-view",
                       "-41", "14.3", "11.94", "1512.0",
                       "1495", "1793"};
   int cur_index = 2;
   int max_index = cur_index + 3;
   int args1 = 6;
   int args2 = 13;
   int args3 = 20;

   index1 = get_vals(string1, cur_index, max_index, args1, vals1);
   index2 = get_vals(string2, cur_index, max_index, args1, vals2);
   index3 = get_vals(string3, 6, 12, args2, vals3);
   index4 = get_vals(string4, 13, 19, args3, vals4);

   checkit_int(index1, 5);
   checkit_double(vals1[0], -45.6);
   checkit_double(vals1[1], 3.5);
   checkit_double(vals1[2], -21.0);
   checkit_int(index2, 5);
   checkit_double(vals2[0], 2345.6);
   checkit_double(vals2[1], -342.1);
   checkit_double(vals2[2], 908.0);
   checkit_int(index3, 12);
   checkit_double(vals3[0], 114.1);
   checkit_double(vals3[1], 321.0);
   checkit_double(vals3[2], 14.5);
   checkit_double(vals3[3], 0.14);
   checkit_double(vals3[4], 0.956);
   checkit_double(vals3[5], 1.156);
   checkit_int(index4, 19);
   checkit_double(vals4[0], -41.0);
   checkit_double(vals4[1], 14.3);
   checkit_double(vals4[2], 11.94);
   checkit_double(vals4[3], 1512.0);
   checkit_double(vals4[4], 1495.0);
   checkit_double(vals4[5], 1793.0);
}

int main(int argc, char * argv[])
{
   get_input_tests();
   get_vals_tests();

   return 0;
}
