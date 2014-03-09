/* Name: Brandon Cooper
 * Instructor: Brett Armstrong
 * CPE 101 - 3
 * Assignment 5 - Commandline Header
 */

#include "cast.h"
#ifndef COMMANDLINE_H
#define COMMANDLINE_H

int get_input(int arg_nums, char * filename, struct sphere spheres[]);

int get_vals(char * string[],
   int cur_index,
   int max_index,
   int arg_nums,
   double vals[]);

void add_flags(int arg_nums, char * args[], struct sphere spheres[]);

#endif
