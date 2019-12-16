/*
  @file info.h
  @brief TAD info and related functions implementations.
*/
#ifndef INFO_H
#define INFO_H

#include <stdio.h>
#include <stdbool.h>

#include "types.h"

#define INFO_ELEMS 9   /* 7 elements and a struct containing year and period */
#define INFO_FORMAT "%u %s %d %s %u %u %u %s"

/* info_t is a pointer to a structure. It contains information about
 * a tax (type, cost, dates, etc) */
typedef struct _info_t {
	unsigned int cost;
	curr_t currency;
	bill_t bill;
	bool paid;
	unsigned int year;
	unsigned int month;
	unsigned int consumption;
	unit_t unit;
} *info_t;

/* Create an empty info structure. */
info_t info_empty();

/* Updates the information of @info with the specified values. */
info_t info_put(info_t info, info_t source);

/* Prints information @info to file @file. */
void info_dump(unsigned int info, FILE *file);

/* Returns true if @info1 is older than @info2. */
bool comes_before(unsigned int info1, unsigned int info2);

/* Returns true if @info1 has equal period to @info2. */
bool eq_period(unsigned int info1, unsigned int info2);

/* Frees allocated memory for specified @info structure. */
info_t destroy_info(info_t info);

#endif
