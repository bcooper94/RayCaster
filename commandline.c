/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * CPE 101 - 3
 * Assignment 5 - Commandline Source
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commandline.h"
#define MAX_SPHERES 10000
#define LINE_MAX 200
#define MAX_STR_SIZE 50
#define MAX_VALS 20

// Pull spheres array from input file
int get_input(int arg_nums, char * filename, struct sphere spheres[])
{
   char cur_line[LINE_MAX];  
   double pX, pY, pZ, radius, r, g, b,
          ambient, diffuse, spec, rough;
   int spheres_created = 0;
   int still_scanning = 1;
   FILE* input = fopen(filename, "r");

   if (!input)
   {
      perror(filename);
      exit(1);
   }
   else
   {
      while (fgets(cur_line, LINE_MAX, input)
            && spheres_created < MAX_SPHERES
            && still_scanning)
      {
         if (sscanf(cur_line, "%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",
               &pX, &pY, &pZ, &radius, &r, &g, &b,
               &ambient, &diffuse, &spec, &rough))
         {
            spheres[spheres_created] = create_sphere(
                  create_point(pX, pY, pZ),
                  radius,
                  create_color(r, g, b),
                  create_finish(ambient, diffuse, spec, rough));
            ++spheres_created;
         }
         else
         {
            still_scanning = 0;
         }
      }
   }

   fclose(input);

   return spheres_created;
}

// Take flags into account and cast all rays
void add_flags(int arg_nums, char * cmd_line[], struct sphere spheres[])
{
   int i, num_spheres;
   char str[MAX_STR_SIZE];
   struct point eye;
   struct color ambient;
   struct light light;
   double val_storage[MAX_VALS];

   // Set default values
   double eyeX = 0.0, eyeY = 0.0, eyeZ = -14.0;
   double minX = -10.0, maxX = 10.0, minY = -7.5, maxY = 7.5;
   int width = 1024, height = 768;
   double lightX = -100.0, lightY = 100.0, lightZ = -100.0,
          lightR = 1.5, lightG = 1.5, lightB = 1.5;
   double ambR = 1.0, ambG = 1.0, ambB = 1.0;

   // Too few arguments
   if (arg_nums < 2)
   {
      printf("usage: a.out <filename> [-eye x y z]\n"
            "[-view min_x max_x min_y max_y width height]\n"
            "[-light x y z r g b] [-ambient r g b]\n");
   }
   else
   {
      // Grab input for spheres array
      num_spheres = get_input(arg_nums, cmd_line[1], spheres);

      // If possible flags
      if (arg_nums > 2)
      {
         i = 2;
         // Scan for possible flags
         while (i < arg_nums && sscanf(cmd_line[i], "%s", str))
         {
            // Check for -eye flag
            if (strncmp(str, "-eye", 4) == 0)
            {
               i = get_vals(cmd_line, i, i + 3, arg_nums, val_storage);
               eyeX = val_storage[0];
               eyeY = val_storage[1];
               eyeZ = val_storage[2];
            }
            // Check for -view flag
            else if (strncmp(str, "-view", 5) == 0)
            {
               i = get_vals(cmd_line, i, i + 6, arg_nums, val_storage);
               minX = val_storage[0];
               maxX = val_storage[1];
               minY = val_storage[2];
               maxY = val_storage[3];
               width = val_storage[4];
               height = val_storage[5];
            }
            // Check for -light flag
            else if (strncmp(str, "-light", 6) == 0)
            {
               i = get_vals(cmd_line, i, i + 6, arg_nums, val_storage);               
               lightX = val_storage[0];
               lightY = val_storage[1];
               lightZ = val_storage[2];
               lightR = val_storage[3];
               lightG = val_storage[4];
               lightB = val_storage[5];
            }
            // Check for -ambient flag
            else if (strncmp(str, "-ambient", 8) == 0)
            {
               i = get_vals(cmd_line, i, i + 3, arg_nums, val_storage);
               ambR = val_storage[0];
               ambG = val_storage[1];
               ambB = val_storage[2];
            }
            // Incorrect entries
            else
            {
               printf("usage: a.out <filename> [-eye x y z]\n"
                     "[-view min_x max_x min_y max_y width height]\n"
                     "[-light x y z r g b] [-ambient r g b]\n");
               exit(1);
            }

            ++i;
         }
      }

      eye = create_point(eyeX, eyeY, eyeZ);
      light = create_light(create_point(lightX, lightY, lightZ),
                           create_color(lightR, lightG, lightB));
      ambient = create_color(ambR, ambG, ambB);

      cast_all_rays(minX, maxX,
         minY, maxY,
         width, height,
         eye,
         spheres,
         num_spheres,
         ambient,
         light);
   }
}

// Grab values following each flag
int get_vals(char * string[],
   int cur_index,
   int max_index,
   int arg_nums,
   double vals[])
{
   int j = 0;
   int i = cur_index;
   
   if (max_index >= arg_nums)
   {
      printf("usage: a.out <filename> [-eye x y z]\n"
                     "[-view min_x max_x min_y max_y width height]\n"
                     "[-light x y z r g b] [-ambient r g b]\n");
      exit(1);
   }
   while (i < max_index
         && sscanf(string[i + 1], "%lf", &vals[j]))
   {
      ++i;
      ++j;
   }

   return i;
}
