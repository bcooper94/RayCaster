/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * Section: CPE 101 - 3
 * HW4 - Cast Header
 */
 
 #ifndef CAST_H
 #define CAST_H
 #include "collisions.h"
 
double color_min_max(double color);

struct sphere closest_sphere(struct ray r,
   struct sphere spheres[],
   int num_spheres,
   struct point intersection_points[],
   struct point eye);

struct color ambient_color(
   struct sphere s,
   struct color ambience,
   struct light light,
   int light_not_blocked,
   double light_visibility,
   double spec_intensity);

struct point error_translate(struct point intersection_point,
   struct sphere s);

struct vector light_vector(
   struct sphere s,
   struct point intersection_point,
   struct light diffuse);

int sphere_blocking_light(
   struct point intersected_point,
   struct light light,
   struct vector light_normal,
   struct sphere spheres[],
   int num_spheres);

double spec_intensity(
   struct point eye,
   struct point error_point,
   struct vector sphere_norm,
   struct vector light_norm,
   double light_visibility);

struct color cast_ray(struct ray r,
   struct sphere spheres[],
   int num_spheres,
   struct color color,
   struct light light,
   struct point eye);

void cast_all_rays(double min_x, double max_x,
   double min_y, double max_y,
   int width, int height,
   struct point eye,
   struct sphere spheres[],
   int num_spheres,
   struct color color,
   struct light light);
 
#endif
