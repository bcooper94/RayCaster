/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * Section: CPE 101 - 3
 * HW4 - Cast Source
 */
 
#include "cast.h"


// cap the upper and lower values of each color
double color_min_max(double const c)
{
   double color = c;

   if (c > 1.0)
   {
      color = 1.0;
   }
   else if (c < 0.0)
   {
      color = 0.0;
   }

   return color;
}

/* Detect the closest sphere a ray intersects
 *
 * Inputs: ray structure, array of intersected spheres,
 * number of spheres hit, array of intersection points on sphere,
 * eye point structure (source of ray)
 * 
 * Output: sphere structure of first sphere intersected by ray r
*/
struct sphere closest_sphere(struct ray r,
   struct sphere spheres[],
   int num_spheres,
   struct point intersection_points[],
   struct point eye)
{
   int index;
   double current_distance;
   struct sphere nearest_sphere = spheres[0];
   double shortest_distance = length_vector(vector_from_to(
                                 eye, intersection_points[0]));

   for (index = 0; index < num_spheres; ++index)
   {
      current_distance = length_vector(vector_from_to(
                           eye, intersection_points[index]));

      if (current_distance < shortest_distance)
      {
         shortest_distance = current_distance;
         nearest_sphere = spheres[index];
      }
   }

   return nearest_sphere;
}

/* Computes color value for a sphere
 *
 * Inputs: sphere structure, color structure of the room's ambience
 *
 * Outputs: final color of a sphere
*/
struct color ambient_color(struct sphere s, struct color ambience)
{
   struct color newColor;

   newColor = create_color(s.color.r * s.finish.ambient * ambience.r,
                           s.color.g * s.finish.ambient * ambience.g,
                           s.color.b * s.finish.ambient * ambience.b);

   return newColor;
}

struct color cast_ray(struct ray r,
   struct sphere spheres[],
   int num_spheres,
   struct point eye,
   struct color color)
{
   struct sphere hit_spheres[num_spheres];
   struct point intersection_points[num_spheres];
   struct sphere close_sphere;
   int num_spheres_hit;
   struct color sphere_color = create_color(1.0, 1.0, 1.0);
   
   num_spheres_hit = find_intersection_points(
                        spheres,
                        num_spheres,
                        r,
                        hit_spheres,
                        intersection_points);

   if (num_spheres_hit)
   {
      close_sphere = closest_sphere(r,
                        hit_spheres,
                        num_spheres_hit,
                        intersection_points,
                        eye);
      sphere_color = ambient_color(close_sphere, color);
   }

   return sphere_color;
}
 
void cast_all_rays(double min_x, double max_x,
   double min_y, double max_y,
   int width, int height,
   struct point eye,
   struct sphere spheres[],
   int num_spheres,
   struct color col)
{
   struct ray r;
   struct point p;
   struct vector v;
   struct color color;
   double x_index = min_x;
   double y_index = max_y;
   
   printf("P3\n%d %d\n255\n", width, height);
   
   for (y_index = max_y;
     y_index > min_y;
     y_index -= (max_y - min_y) / height)
   {
      for (x_index = min_x;
           x_index < max_x;
           x_index += (max_x - min_x) / width)
      {
           p = create_point(x_index, y_index, 0.0);
           v = vector_from_to(eye, p);
           r = create_ray(p, v);
           
           color = cast_ray(r, spheres, num_spheres, eye, col);

           printf("%d %d %d ", (int) (color_min_max(color.r) * 255),
                               (int) (color_min_max(color.g) * 255),
                               (int) (color_min_max(color.b) * 255));
      }
   }
}
