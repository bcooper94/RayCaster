/* Name: Brandon Cooper
 * Section: CPE 101 - 3
 * Instructor: Brett Armstrong
 * Assignment 3 - Collisions Source
 */

#include "collisions.h"

struct maybe_point sphere_intersection_point(struct ray r, struct sphere s)
{
   struct maybe_point myMaybe_Point;
   struct vector vector_to_intersection;
   struct point maybe_intersect_point;
   double time_1, time_2;
   double a, b, c;

   a = dot_vector(r.dir, r.dir);
   b = 2 * dot_vector(difference_point(r.p, s.center), r.dir);
   c = dot_vector(difference_point(r.p, s.center),
                  difference_point(r.p, s.center)) - s.radius * s.radius;

   time_1 = (-b + sqrt(pow(b, 2) - 4.0 * a * c)) / (2.0 * a);
   time_2 = (-b - sqrt(pow(b, 2) - 4.0 * a * c)) / (2.0 * a);

   myMaybe_Point.isPoint = 1;

   if (time_1 > 0 && time_2 > 0)
   {
      if (time_1 < time_2)
      {
         vector_to_intersection = scale_vector(r.dir, time_1);
         maybe_intersect_point = translate_point(r.p, vector_to_intersection);
      }
      else  // time_2 < time_1
      {
         vector_to_intersection = scale_vector(r.dir, time_2);
         maybe_intersect_point = translate_point(r.p, vector_to_intersection);
      }
   }
   else if ((time_1 > 0) && (time_2 < 0))
   {
      vector_to_intersection = scale_vector(r.dir, time_1);
      maybe_intersect_point = translate_point(r.p, vector_to_intersection);
   }
   else if ((time_1 < 0) && (time_2 > 0))
   {
      vector_to_intersection = scale_vector(r.dir, time_2);
      maybe_intersect_point = translate_point(r.p, vector_to_intersection);
   }
   else if (time_1 > 0)
   {
      vector_to_intersection = scale_vector(r.dir, time_1);
      maybe_intersect_point = translate_point(r.p, vector_to_intersection);
   }
   else if (time_2 > 0)
   {
      vector_to_intersection = scale_vector(r.dir, time_2);
      maybe_intersect_point = translate_point(r.p, vector_to_intersection);
   }
   else // No intersection
   {
      myMaybe_Point.isPoint = 0;
      maybe_intersect_point = r.p;
   }

   myMaybe_Point.p = maybe_intersect_point;

   return myMaybe_Point;
}

int find_intersection_points(
   struct sphere spheres[],
   int num_spheres,
   struct ray r,
   struct sphere hit_spheres[],
   struct point intersection_points[])
{
   struct maybe_point maybe_hit_sphere;
   int num_spheres_hit = 0;
   int index;

   for (index = 0; index < num_spheres; ++index)
   {
      maybe_hit_sphere = sphere_intersection_point(r, spheres[index]);
      if (maybe_hit_sphere.isPoint)
      {
         hit_spheres[num_spheres_hit] = spheres[index];
         intersection_points[num_spheres_hit] = maybe_hit_sphere.p;
         num_spheres_hit += 1;
      }
   }

   return num_spheres_hit;
}

struct vector sphere_normal_at_point(struct sphere s, struct point p)
{
   return normalize_vector(vector_from_to(s.center, p));
}
