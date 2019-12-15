/*
  @file types.h
  @brief date_t and bill_t types definitions 
*/
#ifndef TYPES_H
#define TYPES_H

#include <time.h>
#include <stdbool.h>

/* date_t is a pointer to a structure. struct tm is a time structure
 * defined in time.h. */
typedef struct tm *date_t;

/* bill_t defines whether the tax is electric, gas, etc. */
typedef char *bill_t;

/* unit_t is the consumption measure unit. */
typedef char *unit_t;

/* Gets local tame */
date_t get_local_time();

#endif