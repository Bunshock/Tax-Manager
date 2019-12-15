/*
 * info.c
 *
 * TAD info implementation 
 */
#include <assert.h>
#include <stdbool.h>

#include "info.h"

struct _info_t {
	unsigned int cost;
	bool paid;
	bill_t bill;
	unsigned int period;
	unsigned int year;
	date_t pay_date;
	unsigned int consumption;
	unit_t unit;
}

info_t info_empty() {
	info_t info = NULL;
	info = (info_t) calloc(1, sizeof(struct _info_t));
	info->cost = 0u;
	info->paid = false;
	info->type = NULL;
	info->pay_date = NULL;
	info->consumption = 0u;
	info->unit = NULL;
}
