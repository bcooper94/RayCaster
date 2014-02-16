/* Name: Brandon Cooper
 * Section: CPE 101 - 3
 * Instructor: Brett Armstrong
 * Assignment 2 - Vector Math Source
*/

#include "vector_math.h"

struct vector scale_vector(struct vector v, double scalar)
{
   return create_vector(v.x * scalar, v.y * scalar, v.z * scalar);
}

double dot_vector(struct vector v1, struct vector v2)
{
   return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double length_vector(struct vector v)
{
   return sqrt(dot_vector(v, v));
}

struct vector normalize_vector(struct vector v)
{
   return scale_vector(v, 1.0 / length_vector(v));
}

struct vector difference_point(struct point p1, struct point p2)
{
   return create_vector(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

struct vector difference_vector(struct vector v1, struct vector v2)
{
   return create_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

struct point translate_point(struct point p, struct vector v)
{
   return create_point(p.x + v.x, p.y + v.y, p.z + v.z);
}

struct vector vector_from_to(struct point from, struct point to)
{
   return difference_point(from, to);
}
