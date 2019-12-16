/*
  @file types.h
  @brief info_t types definitions.
*/
#ifndef TYPES_H
#define TYPES_H

/* date_t is a pointer to a structure. Contains information about date. */
typedef struct _time_t {
	int day;
	int month;
	int year;
} *date_t;

/* Creates a new empty date_t structure. */
date_t date_empty();

/* Gets local time. */
date_t get_local_time();

/* Destroys allocated date @date. */
date_t destroy_date(date_t date);

/* bill_t defines whether the tax is electric, gas, etc. */
typedef char *bill_t;

/* unit_t is the consumption measure unit. */
typedef char *unit_t;

/* curr_t is the payment currency. */
typedef char *curr_t;

#endif
