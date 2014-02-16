/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * Section: CPE 101 - 3
 * HW4 - Test Cases
 */
 
 #include "checkit.h"
 #include "cast.h"

#define AMBIENCE_1 0.3
#define AMBIENCE_2 0.5
#define AMBIENCE_3 1.0

 void cast_ray_test_cases(void)
 {
   struct ray ray1, ray2, ray3, ray4, ray5, ray6, ray7;
   struct sphere spheres[4], spheres2[3];
   struct color cast_rays1, cast_rays2, cast_rays3,
            cast_rays4, cast_rays5, cast_rays6,
            cast_rays7, cast_rays8;
   struct color ambient_color = create_color(1.0, 1.0, 1.0);
   int num_spheres1 = 4;
   int num_spheres2 = 3;
   
   ray1 = create_ray(create_point(-10.0, 3.0, 0.0), create_vector(1.0, 0.0, 0.0));
   ray2 = create_ray(create_point(10.0, 13.0, 25.0), create_vector(1.0, -1.0, 41.0));
   ray3 = create_ray(create_point(0.0, 5.0, 0.0), create_vector(0.0, -2.5, 0.0));
   ray4 = create_ray(create_point(0.0, 10.0, 0.0), create_vector(0.0, 1.0, 0.0));
   ray5 = create_ray(create_point(9.0, 0.0, 0.0), create_vector(-1.5, 0.0, 0.0));
   ray6 = create_ray(create_point(-9.0, 0.0, 0.0), create_vector(2.0, 0.0, 0.0));
   ray7 = create_ray(create_point(-3.0, -7.0, 0.0), create_vector(0.0, 1.0, 0.0));
   
   spheres[0] = create_sphere(create_point(0.0, 0.0, 0.0),
                  4.0,
                  create_color(0.65, 0.0, 0.0),
                  create_finish(AMBIENCE_1));
   spheres[1] = create_sphere(create_point(-3.0, 4.0, 7.0),
                  1.5,
                  create_color(0.0, 0.7, 0.0),
                  create_finish(AMBIENCE_2));
   spheres[2] = create_sphere(create_point(1.0, 2.0, 3.0),
                  2.0,
                  create_color(0.0, 0.5, 0.0),
                  create_finish(AMBIENCE_3));
   spheres[3] = create_sphere(create_point(-25.0, 0.0, 0.0),
                  3.0,
                  create_color(0.0, 0.0, 0.35),
                  create_finish(AMBIENCE_3));
   spheres2[0] = create_sphere(create_point(0.0, 0.0, 0.0),
                  4.0,
                  create_color(0.55, 0.0, 0.0),
                  create_finish(AMBIENCE_1));
   spheres2[1] = create_sphere(create_point(4.0, 0.0, 0.0),
                  2.0,
                  create_color(0.0, 0.6, 0.0),
                  create_finish(AMBIENCE_2));
   spheres2[2] = create_sphere(create_point(-3.0, 0.0, 0.0),
                  4.0,
                  create_color(0.0, 0.25, 0.0),
                  create_finish(AMBIENCE_3));
   
   
   cast_rays1 = cast_ray(ray1, spheres, num_spheres1, ray1.p, ambient_color);
   cast_rays2 = cast_ray(ray2, spheres, num_spheres1, ray2.p, ambient_color);
   cast_rays3 = cast_ray(ray3, spheres, num_spheres1, ray3.p, ambient_color);
   cast_rays4 = cast_ray(ray4, spheres, num_spheres1, ray4.p, ambient_color);
   cast_rays5 = cast_ray(ray3, spheres2, num_spheres2, ray3.p, ambient_color);
   cast_rays6 = cast_ray(ray5, spheres2, num_spheres2, ray5.p, ambient_color);
   cast_rays7 = cast_ray(ray6, spheres2, num_spheres2, ray6.p, ambient_color);
   cast_rays8 = cast_ray(ray7, spheres2, num_spheres2, ray7.p, ambient_color);
   
   checkit_double(cast_rays1.r, 0.65 * AMBIENCE_1);
   checkit_double(cast_rays1.g, 0.0);
   checkit_double(cast_rays1.b, 0.0);
   checkit_double(cast_rays2.r, 1.0);
   checkit_double(cast_rays2.g, 1.0);
   checkit_double(cast_rays2.b, 1.0);
   checkit_double(cast_rays3.r, 0.65 * AMBIENCE_1);
   checkit_double(cast_rays3.g, 0.0);
   checkit_double(cast_rays3.b, 0.0);
   checkit_double(cast_rays4.r, 1.0);
   checkit_double(cast_rays4.g, 1.0);
   checkit_double(cast_rays4.b, 1.0);
   checkit_double(cast_rays5.r, 0.55 * AMBIENCE_1);
   checkit_double(cast_rays5.g, 0.0);
   checkit_double(cast_rays5.b, 0.0);
   checkit_double(cast_rays6.r, 0.0);
   checkit_double(cast_rays6.g, 0.6 * AMBIENCE_2);
   checkit_double(cast_rays6.b, 0.0);
   checkit_double(cast_rays7.r, 0.0);
   checkit_double(cast_rays7.g, 0.25 * AMBIENCE_3);
   checkit_double(cast_rays7.b, 0.0);
   checkit_double(cast_rays8.r, 0.0);
   checkit_double(cast_rays8.g, 0.25 * AMBIENCE_3);
   checkit_double(cast_rays8.b, 0.0);
 }

void color_min_max_test_cases(void)
{
   checkit_double(color_min_max(1.5), 1.0);
   checkit_double(color_min_max(0.55), 0.55);
   checkit_double(color_min_max(-0.1), 0.0);
}
 
 int main(int argc, char **argv)
 {
   cast_ray_test_cases();
   color_min_max_test_cases();
 
   return 0;
 }
