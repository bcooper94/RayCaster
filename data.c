/* Name: Brandon Cooper
 * Section: CPE 101 - 3
 * Instructor: Brett Armstrong
 * Assignemnt 1 - Data.c*/

#include "data.h"

struct point create_point(double x, double y, double z)
{
   struct point mypoint;
   mypoint.x = x;
   mypoint.y = y;
   mypoint.z = z;

   return mypoint;
}

struct vector create_vector(double x, double y, double z)
{
   struct vector myvector;
   myvector.x = x;
   myvector.y = y;
   myvector.z = z;

   return myvector;
}

struct ray create_ray(struct point p, struct vector dir)
{
   struct ray myray;
   myray.p = p;
   myray.dir = dir;

   return myray;
}

struct color create_color(double r, double g, double b)
{
   struct color myColor;
   myColor.r = r;
   myColor.g = g;
   myColor.b = b;
   
   return myColor;
}

struct finish create_finish(double ambient, double diffuse)
{
   struct finish myFinish;
   myFinish.ambient = ambient;
   myFinish.diff = diffuse;

   return myFinish;
}

struct light create_light(struct point p, struct color col)
{
   struct light myLight;
   myLight.p = p;
   myLight.color = color;

   return myLight;
}

struct sphere create_sphere(struct point center, double radius, struct color color, struct finish finish)
{
   struct sphere mysphere;
   mysphere.center = center;
   mysphere.radius = radius;
   mysphere.color = color;
   mysphere.finish = finish;

   return mysphere;
}
