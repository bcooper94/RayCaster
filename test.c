/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * Section: CPE 101 - 3
 * HW4 - Test Cases
 */
 
#include "checkit.h"
#include "cast.h"
#include <math.h>


#define AMBIENCE_1 0.3
#define AMBIENCE_2 0.5
#define AMBIENCE_3 1.0
#define DIFFUSE_1 0.5
#define DIFFUSE_2 0.2
#define INTERSECT_ERROR 0.01
#define ROUGH 0.05
#define SPEC 0.5

void cast_ray_test_cases(void)
{
   struct ray ray1, ray2, ray3, ray4, ray5, ray6, ray7;
   struct sphere spheres[4], spheres2[3];
   struct color cast_rays1, cast_rays2, cast_rays3,
            cast_rays4, cast_rays5, cast_rays6,
            cast_rays7, cast_rays8;
   struct light light1, light2;
   struct color ambient_color = create_color(1.0, 1.0, 1.0);
   int num_spheres1 = 4;
   int num_spheres2 = 3;

   light1 = create_light(create_point(-100.0, 100.0, -100.0),
               create_color(0.5, 1.0, 1.5));
   light2 = create_light(create_point(-50.0, 500.0, -100.0),
               create_color(0.2, 1.1, 0.6));
   
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
                  create_finish(AMBIENCE_1, DIFFUSE_1, SPEC, ROUGH));
   spheres[1] = create_sphere(create_point(-3.0, 4.0, 7.0),
                  1.5,
                  create_color(0.0, 0.7, 0.0),
                  create_finish(AMBIENCE_2, DIFFUSE_2, SPEC, ROUGH));
   spheres[2] = create_sphere(create_point(1.0, 2.0, 3.0),
                  2.0,
                  create_color(0.0, 0.5, 0.0),
                  create_finish(AMBIENCE_3, DIFFUSE_1, SPEC, ROUGH));
   spheres[3] = create_sphere(create_point(-25.0, 0.0, 0.0),
                  3.0,
                  create_color(0.0, 0.0, 0.35),
                  create_finish(AMBIENCE_3, DIFFUSE_2, SPEC, ROUGH));
   spheres2[0] = create_sphere(create_point(0.0, 0.0, 0.0),
                  4.0,
                  create_color(0.55, 0.0, 0.0),
                  create_finish(AMBIENCE_1, DIFFUSE_1, SPEC, ROUGH));
   spheres2[1] = create_sphere(create_point(4.0, 0.0, 0.0),
                  2.0,
                  create_color(0.0, 0.6, 0.0),
                  create_finish(AMBIENCE_2, DIFFUSE_2, SPEC, ROUGH));
   spheres2[2] = create_sphere(create_point(-3.0, 0.0, 0.0),
                  4.0,
                  create_color(0.0, 0.25, 0.0),
                  create_finish(AMBIENCE_3, DIFFUSE_1, SPEC, ROUGH));
   
   
   cast_rays1 = cast_ray(ray1, spheres, num_spheres1, ambient_color, light1, ray1.p);
   cast_rays2 = cast_ray(ray2, spheres, num_spheres1, ambient_color, light1, ray2.p);
   cast_rays3 = cast_ray(ray3, spheres, num_spheres1, ambient_color, light2, ray3.p);
   cast_rays4 = cast_ray(ray4, spheres, num_spheres1, ambient_color, light2, ray4.p);
   cast_rays5 = cast_ray(ray3, spheres2, num_spheres2, ambient_color, light1, ray3.p);
   cast_rays6 = cast_ray(ray5, spheres2, num_spheres2, ambient_color, light1, ray5.p);
   cast_rays7 = cast_ray(ray6, spheres2, num_spheres2, ambient_color, light2, ray6.p);
   cast_rays8 = cast_ray(ray7, spheres2, num_spheres2, ambient_color, light2, ray7.p);

   checkit_double(cast_rays1.r, 0.326123);
   checkit_double(cast_rays1.g, 0.0);
   checkit_double(cast_rays1.b, 0.0);
   checkit_double(cast_rays2.r, 1.0);
   checkit_double(cast_rays2.g, 1.0);
   checkit_double(cast_rays2.b, 1.0);
   checkit_double(cast_rays3.r, 0.319329);
   checkit_double(cast_rays3.g, 0.33506);
   checkit_double(cast_rays3.b, 0.18276);
   checkit_double(cast_rays4.r, 1.0);
   checkit_double(cast_rays4.g, 1.0);
   checkit_double(cast_rays4.b, 1.0);
   checkit_double(cast_rays5.r, 0.242228);
   checkit_double(cast_rays5.g, 0.0);
   checkit_double(cast_rays5.b, 0.0);
   checkit_double(cast_rays6.r, 0.0);
   checkit_double(cast_rays6.g, 0.6 * AMBIENCE_2);
   checkit_double(cast_rays6.b, 0.0);
   checkit_double(cast_rays7.r, 0.0);
   checkit_double(cast_rays7.g, 0.261554);
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

void closest_sphere_test_cases(void)
{
   struct ray ray0, ray1, ray2, ray3;
   struct sphere sphere0, sphere1, sphere2, sphere3;
   int num_spheres = 4;
   struct sphere spheres[4];

   struct sphere hit_spheres0[num_spheres];
   struct point intersection_points0[num_spheres];

   struct sphere hit_spheres1[num_spheres];
   struct point intersection_points1[num_spheres];

   struct sphere hit_spheres2[num_spheres];
   struct point intersection_points2[num_spheres];

   struct sphere hit_spheres3[num_spheres];
   struct point intersection_points3[num_spheres];
   
   ray0 = create_ray(create_point(0.0, -5.0, 0.0), create_vector(0.0, 1.2, 0.0));
   ray1 = create_ray(create_point(8.0, 1.0, 0.0), create_vector(0.0, -1.0, 0.0));
   ray2 = create_ray(create_point(0.0, 7.0, 0.0), create_vector(0.0, -1.0, 0.0));
   ray3 = create_ray(create_point(-9.0, -1.0, 0.0), create_vector(2.0, 0.0, 0.0));

   spheres[0] = create_sphere(create_point(0.0, 0.0, 0.0),
                  2.0,
                  create_color(0.35, 0.0, 0.0),
                  create_finish(AMBIENCE_1, DIFFUSE_1, SPEC, ROUGH));
   spheres[1] = create_sphere(create_point(4.0, 5.0, 0.0),
                  2.0,
                  create_color(0.0, 0.2, 0.0),
                  create_finish(AMBIENCE_2, DIFFUSE_2, SPEC, ROUGH));
   spheres[2] = create_sphere(create_point(0.0, 4.0, 0.0),
                  1.0,
                  create_color(0.0, 0.1, 0.0),
                  create_finish(AMBIENCE_3, DIFFUSE_1, SPEC, ROUGH));
   spheres[3] = create_sphere(create_point(-4.0, -1.0, 0.0),
                  2.0,
                  create_color(0.0, 0.0, 0.5),
                  create_finish(AMBIENCE_3, DIFFUSE_2, SPEC, ROUGH));

   find_intersection_points(spheres, num_spheres, ray0, hit_spheres0, intersection_points0);
   find_intersection_points(spheres, num_spheres, ray1, hit_spheres1, intersection_points1);
   find_intersection_points(spheres, num_spheres, ray2, hit_spheres2, intersection_points2);
   find_intersection_points(spheres, num_spheres, ray3, hit_spheres3, intersection_points3);

   sphere0 = closest_sphere(ray0,
               hit_spheres0,
               num_spheres,
               intersection_points0,
               ray0.p);
   sphere1 = closest_sphere(ray1,
               hit_spheres1,
               num_spheres,
               intersection_points1,
               ray1.p);
   sphere2 = closest_sphere(ray2,
               hit_spheres2,
               num_spheres,
               intersection_points2,
               ray2.p);
   sphere3 = closest_sphere(ray3,
               hit_spheres3,
               num_spheres,
               intersection_points3,
               ray3.p);

   checkit_double(sphere0.center.x, 0.0);
   checkit_double(sphere0.center.y, 0.0);
   checkit_double(sphere0.center.z, 0.0);
   checkit_double(sphere1.center.x, 0.0);
   checkit_double(sphere1.center.y, 4.0);
   checkit_double(sphere1.center.z, 0.0);
   checkit_double(sphere2.center.x, 0.0);
   checkit_double(sphere2.center.y, 4.0);
   checkit_double(sphere2.center.z, 0.0);
   checkit_double(sphere3.center.x, -4.0);
   checkit_double(sphere3.center.y, -1.0);
   checkit_double(sphere3.center.z, 0.0);
}

void ambient_color_test_cases(void)
{
   struct color col1, col2, col3;
   struct sphere s1, s2, s3;
   struct color ambience1, ambience2;
   struct color newCol1, newCol2, newCol3, newCol4, newCol5, newCol6;
   struct light light1, light2;
   int lightBlocked, lightNotBlocked;
   double lightVisibility1, lightVisibility2, lightVisibility3;

   lightBlocked = 0;
   lightNotBlocked = 1;

   lightVisibility1 = 0.65;
   lightVisibility2 = 0.42;
   lightVisibility3 = 0.1;


   col1 = create_color(0.0, 1.0, 0.0);
   col2 = create_color(1.0, 0.0, 1.0);
   col3 = create_color(0.5, 0.6, 0.0);

   light1 = create_light(create_point(-100.0, 100.0, -100.0), col1);
   light2 = create_light(create_point(-100.0, 100.0, -100.0), col2);

   s1 = create_sphere(create_point(0.0, 0.0, 0.0),
                     2.0,
                     col1,
                     create_finish(1.0, DIFFUSE_1, SPEC, ROUGH));
   s2 = create_sphere(create_point(1.0, 2.0, 3.0),
                     1.0,
                     col2,
                     create_finish(0.5, DIFFUSE_2, SPEC, ROUGH));
   s3 = create_sphere(create_point(2.0, 4.0, 0.0),
                     2.5,
                     col3,
                     create_finish(1.0, DIFFUSE_1, SPEC, ROUGH));

   ambience1 = create_color(1.0, 1.0, 1.0);
   ambience2 = create_color(0.5, 0.5, 0.2);

   newCol1 = ambient_color(s1, ambience1, light1, lightNotBlocked, lightVisibility1, 0.2);
   newCol2 = ambient_color(s2, ambience1, light1, lightBlocked, lightVisibility2, 0.4);
   newCol3 = ambient_color(s3, ambience1, light1, lightNotBlocked, lightVisibility3, 0.5);
   newCol4 = ambient_color(s1, ambience2, light2, lightBlocked, lightVisibility1, 1.0);
   newCol5 = ambient_color(s2, ambience2, light2, lightNotBlocked, lightVisibility2, -3.0);
   newCol6 = ambient_color(s3, ambience2, light2, lightBlocked, lightVisibility3, -1.0);

   checkit_double(newCol1.r, 0.0);
   checkit_double(newCol1.g, s1.color.g * ambience1.g * s1.finish.ambient);
   checkit_double(newCol1.b, 0.0);
   checkit_double(newCol2.r, s2.color.r * ambience1.r * s2.finish.ambient
      + s2.finish.diffuse * s2.color.r * light1.color.r * lightVisibility2);
   checkit_double(newCol2.g, 0.0);
   checkit_double(newCol2.b, s2.color.b * ambience1.b * s2.finish.ambient
      + s2.finish.diffuse * s2.color.b * light1.color.b * lightVisibility2);
   checkit_double(newCol3.r, s3.color.r * ambience1.r * s3.finish.ambient);
   checkit_double(newCol3.g, s3.color.g * ambience1.g * s3.finish.ambient);
   checkit_double(newCol3.b, 0.0);
   checkit_double(newCol4.r, 0.5);
   checkit_double(newCol4.g, s1.color.g * ambience2.g * s1.finish.ambient
      + s3.finish.diffuse * s3.color.g * light2.color.g * lightVisibility1);
   checkit_double(newCol4.b, 0.5);
   checkit_double(newCol5.r, s2.color.r * ambience2.r * s2.finish.ambient);
   checkit_double(newCol5.g, 0.0);
   checkit_double(newCol5.b, s2.color.b * ambience2.b * s2.finish.ambient);
   checkit_double(newCol6.r, s3.color.r * ambience2.r * s3.finish.ambient
      + s3.finish.diffuse * s3.color.r * light2.color.r * lightVisibility3);
   checkit_double(newCol6.g, s3.color.g * ambience2.g * s3.finish.ambient
      + s3.finish.diffuse * s3.color.g * light2.color.g * lightVisibility3);
   checkit_double(newCol6.b, 0.0);
}

void error_translate_test_cases(void)
{
   struct point intersection1, intersection2;
   struct sphere s1, s2;
   struct point translated1, translated2;

   intersection1 = create_point(2.0, 0.0, 0.0);
   intersection2 = create_point(0.0, -3.0, 0.0);

   s1 = create_sphere(
         create_point(0.0, 0.0, 0.0), 2.0,
         create_color(1.0, 0.5, 0.25),
         create_finish(0.2, DIFFUSE_1, SPEC, ROUGH));
   s2 = create_sphere(
         create_point(0.0, 1.0, 0.0), 4.0,
         create_color(0.0, 0.2, 0.21),
         create_finish(0.3, DIFFUSE_2, SPEC, ROUGH));

   translated1 = error_translate(intersection1, s1);
   translated2 = error_translate(intersection2, s2);

   checkit_double(translated1.x, 2.01);
   checkit_double(translated1.y, 0.0);
   checkit_double(translated1.z, 0.0);
   checkit_double(translated2.x, 0.0);
   checkit_double(translated2.y, -3.01);
   checkit_double(translated2.z, 0.0);
}

void light_vector_tests(void)
{
   struct sphere s1, s2;
   struct point p1, p2;
   struct light diffuse;
   struct vector light_v1, light_v2;

   s1 = create_sphere(create_point(0.0, 0.0, 0.0), 2.0,
         create_color(0.1, 0.5, 0.9),
         create_finish(AMBIENCE_1, DIFFUSE_1, SPEC, ROUGH));
   s2 = create_sphere(create_point(0.0, 0.0, 0.0), 4.0,
         create_color(0.15, 0.54, 0.29),
         create_finish(AMBIENCE_2, DIFFUSE_2, SPEC, ROUGH));

   p1 = create_point(-2.0, 0.0, 0.0);
   p2 = create_point(0.0, 4.0, 0.0);

   diffuse = create_light(create_point(0.0, 150.0, 0.0),
                         create_color(1.5, 1.2, 0.9));

   light_v1 = light_vector(s1, p1, diffuse);
   light_v2 = light_vector(s2, p2, diffuse);

   checkit_double(light_v1.x, normalize_vector(vector_from_to(p1, diffuse.p)).x);
   checkit_double(light_v1.y, normalize_vector(vector_from_to(p1, diffuse.p)).y);
   checkit_double(light_v1.z, normalize_vector(vector_from_to(p1, diffuse.p)).z);
   checkit_double(light_v2.x, normalize_vector(vector_from_to(p2, diffuse.p)).x);
   checkit_double(light_v2.y, normalize_vector(vector_from_to(p2, diffuse.p)).y);
   checkit_double(light_v2.z, normalize_vector(vector_from_to(p2, diffuse.p)).z);
}

void sphere_blocking_light_tests(void)
{
   struct point intersected_p1, intersected_p2;
   struct light light;
   struct vector light_norm;
   struct sphere spheres[2];
   int s_blocking1, s_blocking2;
   int num_spheres = 2;

   light = create_light(create_point(0.0, 200.0, 0.0),
                        create_color(1.0, 0.5, 0.5));

   spheres[0] = create_sphere(create_point(0.0, 0.0, 0.0), 2.0,
                  create_color(0.1, 0.5, 0.9),
                  create_finish(AMBIENCE_1, DIFFUSE_1, SPEC, ROUGH));
   spheres[1] = create_sphere(create_point(0.0, -10.0, 0.0), 1.0,
                  create_color(0.1, 0.5, 0.9),
                  create_finish(AMBIENCE_1, DIFFUSE_1, SPEC, ROUGH));

   intersected_p1 = create_point(0.0, -9.0, 0.0);
   intersected_p2 = create_point(0.0, 2.0, 0.0);

   light_norm = create_vector(0.0, 1.0, 0.0);

   s_blocking1 = sphere_blocking_light(intersected_p1, light, light_norm, spheres, num_spheres);
   s_blocking2 = sphere_blocking_light(intersected_p2, light, light_norm, spheres, num_spheres);

   checkit_int(s_blocking1, 1);
   checkit_int(s_blocking2, 0);
}

void spec_intensity_tests(void)
{
   struct point eye;
   struct point error_point;
   struct vector sphere_norm;
   struct vector light_norm1, light_norm2;
   double light_visibility;
   struct vector reflect1, reflect2;
   double spec1, spec2;
   struct vector v;

   eye = create_point(-15.0, 0.0, 0.0);
   error_point = create_point(-1.01, 0.0, 0.0);

   sphere_norm = create_vector(-1.0, 0.0, 0.0);

   light_norm1 = create_vector(1.0, 0.0, 0.0);
   light_norm2 = create_vector(0.0, 1.0, 0.0);

   light_visibility = 0.5;

   reflect1 = normalize_vector(
                  difference_vector(
                     light_norm1,
                     scale_vector(
                        sphere_norm,
                        2 * light_visibility)));
   reflect2 = normalize_vector(
                  difference_vector(
                     light_norm2,
                     scale_vector(
                        sphere_norm,
                        2 * light_visibility)));
   v = normalize_vector(vector_from_to(eye, error_point));

   spec1 = spec_intensity(eye, error_point, sphere_norm, light_norm1, light_visibility);
   spec2 = spec_intensity(eye, error_point, sphere_norm, light_norm2, light_visibility);

   checkit_double(spec1, dot_vector(reflect1, v));
   checkit_double(spec2, dot_vector(reflect2, v));
}
 
int main(int argc, char **argv)
{
   cast_ray_test_cases();
   color_min_max_test_cases();
   closest_sphere_test_cases();
   ambient_color_test_cases();
   error_translate_test_cases();
   light_vector_tests();
   sphere_blocking_light_tests();
   spec_intensity_tests();
 
   return 0;
}
