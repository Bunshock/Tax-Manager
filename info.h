/*
  @file info.h
  @brief TAD info and related functions implementations.
*/
#ifndef INFO_H
#define INFO_H

#include <stdio.h>
#include <stdbool.h>

#include "types.h"

#define INFO_ELEMS 11
#define INFO_FORMAT "%u %s %s %s %d/%d %u %s"

/* period_t contains information of year and period of consumption. */
typedef struct _period_t {
	int month;
	int year;
} *period_t;

/* info_t is a pointer to a structure. It contains information about
 * a tax (type, cost, dates, etc) */
typedef struct _info_t {
	unsigned int cost;
	curr_t currency;
	bill_t bill;
	bool paid;
	period_t period;
	date_t pay_date;
	unsigned int consumption;
	unit_t unit;
} *info_t;

/* Create an empty period structure. */
period_t period_empty();

/* Create an empty info structure. */
info_t info_empty();

/* Prints information @info to file @file. */
void info_dump(info_t info, FILE *file);

/* Creates a date_t structure from the @day, @month and @year values. */
date_t convert_to_date(int day, int month, int year);

/* Returns true if @info1 is older than @info2. */
bool comes_before(period_t info1, period_t info2);

/* Returns true if @info1 has equal period to @info2. */
bool eq_period(period_t info1, period_t info2);

/* Frees allocated memory for specified @info structure. */
info_t destroy_info(info_t info);

#endif
