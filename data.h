/* Name: Brandon Cooper
 * Section: CPE 101 - 3
 * Instructor: Brett Armstrong
 * Assignemnt 1 - Data header*/

#ifndef DATA_H
#define DATA_H
#include <stdio.h>
#include <math.h>

struct point
{
   double x, y, z;
};

struct vector
{
   double x, y, z;
};

struct ray
{
   struct point p;
   struct vector dir;
};

struct color
{
   double r, g, b;
};

struct finish
{
   double ambient;
};

struct sphere
{
   struct point center;
   double radius;
   struct color color;
   struct finish finish;
};


struct point create_point(double x, double y, double z);

struct vector create_vector(double x, double y, double z);

struct ray create_ray(struct point p, struct vector dir);

struct color create_color(double r, double g, double b);

struct finish create_finish(double ambient);

struct sphere create_sphere(
   struct point center,
   double radius,
   struct color color,
   struct finish finish);

#endif
