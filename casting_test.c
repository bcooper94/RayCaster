/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * Section: CPE 101 - 3
 * HW4 - Casting Test Cases
 */
 
#include "cast.h"
 
#define MIN_X -10
#define MAX_X 10
#define MIN_Y -7.5
#define MAX_Y 7.5
#define WIDTH 1024
#define HEIGHT 768
#define NUM_SPHERES 2
#define BLUE_AMBIENCE 0.2
#define RED_AMBIENCE 0.4
#define WHITE_AMBIENCE create_color(1.0, 1.0, 1.0)
 
void cast_all_rays_test_case(void)
{
   struct point eye;
   struct sphere spheres[NUM_SPHERES];
   
   eye = create_point(0.0, 0.0, -14.0);
   spheres[0] = create_sphere(create_point(1.0, 1.0, 0.0), 2.0,
               create_color(0.0, 0.0, 1.0),
               create_finish(BLUE_AMBIENCE));
   spheres[1] = create_sphere(create_point(0.5, 1.5, -3.0), 0.5,
               create_color(1.0, 0.0, 0.0),
               create_finish(RED_AMBIENCE));
   
   cast_all_rays(MIN_X, MAX_X,
      MIN_Y, MAX_Y,
      WIDTH, HEIGHT,
      eye,
      spheres,
      NUM_SPHERES,
      WHITE_AMBIENCE);
}
 
int main(int argc, char **argv)
{
   cast_all_rays_test_case();
 
   return 0;
}
