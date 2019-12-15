/*
  @file info.h
  @brief TAD info and related functions implementations 
*/
#ifndef INFO_H
#define INFO_H

#include "types.h"

/* info_t is a pointer to a structure. It contains information about
 * a tax (type, cost, dates, etc) */
typedef struct _info_t *info_t;

/* Create an empty info struct */
info_t info_empty();

/* Prints information @info to file @file. */
void info_dump(info_t info, FILE *file);

#endif