/*
  @file info.h
  @brief TAD info and related functions implementations.
*/
#ifndef INFO_H
#define INFO_H

#include <stdio.h>
#include <stdbool.h>

#include "types.h"

#define INFO_ELEMS 8
#define INFO_FORMAT "%u %s %s %d %u %u %u %s"

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

/* Prints information @info to file @file. */
void info_dump(info_t info, FILE *file);

/* Returns true if @info1 is older than @info2. */
bool comes_before(info_t info1, info_t info2);

/* Returns true if @info1 has equal period to @info2. */
bool eq_period(info_t info1, info_t info2);

/* Frees allocated memory for specified @info structure. */
info_t destroy_info(info_t info);

#endif
