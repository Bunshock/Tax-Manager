/*
 * info.c
 *
 * TAD info implementation 
 */
#include <stdlib.h>
#include <time.h>

#include "info.h"

period_t period_empty() {
	period_t period = NULL;
	period = (period_t) calloc(1, sizeof(struct _period_t));
	return period;
}

info_t info_empty() {
	info_t info = NULL;
	info = (info_t) calloc(1, sizeof(struct _info_t));
	info->period = period_empty();
	info->pay_date = NULL;
	return info;
}

void info_dump(info_t info, FILE *file) {
	if(info != NULL) {
		fprintf(file, INFO_FORMAT, info->cost, info->currency, info->bill, info->paid ? "PAID" : "NOT PAID", info->period->year, info->period->month, 
			        info->consumption, info->unit);
		fprintf(file, "\nPayment date:\n");
		info->pay_date == NULL ? fprintf(file, "NO PAYMENT DATE REGISTERED!\n") : fprintf(file, "%d/%d/%d\n", info->pay_date->day, 
																						info->pay_date->month, info->pay_date->year);
	}
}

bool comes_before(period_t info1, period_t info2) {
	if(info1 == NULL || info2 == NULL)
		return false;

	bool b = false;
	b = info1->year < info2->year ? true : ( info1->year == info2->year ? info1->month < info2->month : false );
	return b;
}

bool eq_period(period_t info1, period_t info2) {
	if(info1 == NULL || info2 == NULL)
		return false;

	bool b = false;
	b = info1->year == info2->year ? info1->month == info2->month : false;
	return b;
}

info_t destroy_info(info_t info) {
	if(info->period != NULL) {
		free(info->period);
		info->period = NULL;
	}
	if(info->pay_date != NULL) {
		free(info->pay_date);
		info->pay_date = NULL;
	}
	free(info);
	info = NULL;
	return NULL;
}

