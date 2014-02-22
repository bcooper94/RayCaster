/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * Section: CPE 101 - 3
 * HW4 - Cast Source
 */
 
#include "cast.h"
#include <math.h>

#define INTERSECT_ERROR 0.01

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
   double shortest_distance = length_vector(vector_from_to(eye, intersection_points[0]));

   for (index = 0; index < num_spheres; ++index)
   {
      current_distance = length_vector(vector_from_to(eye, intersection_points[index]));

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
 * Output: final color of a sphere
 */
struct color ambient_color(
   struct sphere s,
   struct color ambience,
   struct light light,
   int light_blocked,
   double light_visibility,
   double spec_intensity)
{
   double r, g, b;

   r = s.color.r * s.finish.ambient * ambience.r;
   g = s.color.g * s.finish.ambient * ambience.g;
   b = s.color.b * s.finish.ambient * ambience.b;

   if (!light_blocked && (light_visibility > 0))
   {
      r += light_visibility * light.color.r * s.finish.diffuse * s.color.r;
      g += light_visibility * light.color.g * s.finish.diffuse * s.color.g;
      b += light_visibility * light.color.b * s.finish.diffuse * s.color.b;
   }
   if (spec_intensity > 0)
   {
      r += light.color.r * s.finish.specular * pow(spec_intensity, 1.0 / s.finish.roughness);
      g += light.color.g * s.finish.specular * pow(spec_intensity, 1.0 / s.finish.roughness);
      b += light.color.b * s.finish.specular * pow(spec_intensity, 1.0 / s.finish.roughness);
   }

   return create_color(r, g, b);
}

/* Normalize and translate an intersection point along the sphere's
 * normal vector by 0.01 to prevent unintended intersections
 */
struct point error_translate(struct point intersection_point,
   struct sphere s)
{
   return translate_point(intersection_point,
                          scale_vector(
                              sphere_normal_at_point(s, intersection_point),
                              INTERSECT_ERROR));
}

// Compute normalized vector from an intersection point to a light
struct vector light_vector(
   struct sphere s,
   struct point intersection_point,
   struct light diffuse)
{
   return normalize_vector(vector_from_to(intersection_point, diffuse.p));
}

/* Determine if a sphere is in the way of the light
 * reflecting off another sphere
 *
 * Inputs: point of intersection on sphere,
 *    normal vector from sphere intersection point,
 *    normalized vector from light source, light structure,
 *    spheres array
 *
 * Output: int representing whether a sphere is blocking
 *    light source or not
 */
int sphere_blocking_light(
   struct point intersected_point,
   struct light light,
   struct vector sphere_normal,
   struct vector light_normal,
   struct sphere spheres[],
   int num_spheres)
{
   struct ray to_lightsource;
   struct sphere light_hit_spheres[num_spheres];
   struct point light_intersect_points[num_spheres];

   to_lightsource = create_ray(intersected_point, light_normal);

   return find_intersection_points(spheres,
                           num_spheres,
                           to_lightsource,
                           light_hit_spheres,
                           light_intersect_points);
}

/* Compute the specular intensity at a point
 * Inputs: Eye point, translated error point,
 *    normal vector from intersect point on sphere,
 *    normal vector to light source, light visibility factor
 *
 * Output: Specular intensity double
 */
double spec_intensity(
   struct point eye,
   struct point error_point,
   struct vector sphere_norm,
   struct vector light_norm,
   double light_visibility)
{
   struct vector reflection;
   double specular;
   struct vector view_direction;

   reflection = normalize_vector(
                  difference_vector(
                     light_norm,
                     scale_vector(
                        sphere_norm,
                        2 * light_visibility)));

   view_direction = normalize_vector(vector_from_to(eye, error_point));

   specular = dot_vector(reflection, view_direction);

   return specular;
}

struct color cast_ray(struct ray r,
   struct sphere spheres[],
   int num_spheres,
   struct color color,
   struct light light,
   struct point eye)
{
   struct sphere hit_spheres[num_spheres];
   struct point intersection_points[num_spheres];
   struct sphere close_sphere;
   struct point sphere_point;
   struct point sphere_error_point;
   int num_spheres_hit;
   double light_visibility, light_blocked, intensity;
   struct vector sphere_normal;
   struct vector light_normal;
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
      sphere_point = sphere_intersection_point(r, close_sphere).p;
      sphere_error_point = error_translate(sphere_point, close_sphere);
      sphere_normal = sphere_normal_at_point(close_sphere, sphere_point);
      light_normal = light_vector(
                           close_sphere,
                           sphere_point,
                           light);
      light_visibility = dot_vector(light_vector(
                           close_sphere,
                           sphere_point,
                           light), sphere_normal);
      light_blocked = sphere_blocking_light(
                           sphere_error_point,
                           light,
                           sphere_normal,
                           light_normal,
                           spheres,
                           num_spheres);
      intensity = spec_intensity(
                     eye,
                     sphere_error_point,
                     sphere_normal,
                     light_normal,
                     light_visibility);

      sphere_color = ambient_color(
                           close_sphere,
                           color,
                           light,
                           light_blocked,
                           light_visibility,
                           intensity);
   }

   return sphere_color;
}
 
void cast_all_rays(double min_x, double max_x,
   double min_y, double max_y,
   int width, int height,
   struct point eye,
   struct sphere spheres[],
   int num_spheres,
   struct color col,
   struct light light)
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
           r = create_ray(eye, v);
           
           color = cast_ray(r, spheres, num_spheres, col, light, eye);

           printf("%d %d %d ", (int) (color_min_max(color.r) * 255),
                               (int) (color_min_max(color.g) * 255),
                               (int) (color_min_max(color.b) * 255));
      }
   }
}
