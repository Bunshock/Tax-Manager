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
#define INFO_FORMAT "%u %s %d %s %d %d %u %s"

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
	bool paid;
	bill_t bill;
	period_t period;
	date_t pay_date;
	unsigned int consumption;
	unit_t unit;
} *info_t;

/* Create an empty info structure. */
info_t info_empty();

/* Updates the information of @info with the specified values. */
info_t info_update(info_t info, unsigned int cost, curr_t curr, bool paid, bill_t bill, int month, int year,
						date_t pay_date, unsigned int consumption, unit_t unit);

/* Prints information @info to file @file. */
void info_dump(info_t info, FILE *file);

/* Gets local time. */
date_t get_local_time();

/* Puts time information specified in @date into @info structure. */
info_t set_payment_date(info_t info, date_t date);

/* Creates a date_t structure from the @day, @month and @year values. */
date_t convert_to_tm(int day, int month, int year);

/* Returns true if @info1 is older than @info2. */
bool comes_before(info_t info1, info_t info2);

#endif
