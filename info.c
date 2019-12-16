/*
 * info.c
 *
 * TAD info implementation 
 */
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "info.h"

period_t period_empty() {
	period_t period = NULL;
	period = (period_t) calloc(1, sizeof(struct _period_t));
	period->year = 0;
	period->month = 0;
	return period;
}

info_t info_empty() {
	info_t info = NULL;
	info = (info_t) calloc(1, sizeof(struct _info_t));
	info->cost = 0u;
	info->currency = NULL;
	info->paid = false;
	info->bill = NULL;
	info->period = period_empty();
	info->pay_date = NULL;
	info->consumption = 0u;
	info->unit = NULL;
	return info;
}

void info_dump(info_t info, FILE *file) {
	if(info != NULL) {
		fprintf(file, INFO_FORMAT, info->cost, info->currency, info->paid, info->bill, 
			info->period->month, info->period->year, info->consumption, info->unit);
		fprintf(file, "\n");
	}
}

info_t info_update(info_t info, 
				   unsigned int cost, 
				   curr_t curr, 
				   bool paid, 
				   bill_t bill,
				   period_t period,
				   date_t pay_date, 
				   unsigned int consumption, 
				   unit_t unit) {
	if(info != NULL) {
		info->cost = cost;
		info->currency = curr;
		info->paid = paid;
		info->bill = bill;
		info->period->year = year;
		info->period->month = month;
		info->pay_date = pay_date;
		info->consumption = consumption;
		info->unit = unit;
	}
	return info;
}

date_t get_local_time() {
	date_t date = NULL;
	time_t rawtime;
	time(&rawtime);
	date = localtime(&rawtime);
	return date;
}

info_t set_payment_date(info_t info, date_t date) {
	if(info != NULL)
		info->pay_date = date;
	return info;
}

date_t convert_to_tm(int day, int month, int year) {
	date_t time = NULL;
	time->tm_mday = day;
	time->tm_mon = month;
	time->tm_year = year - 1900;
	return time;
}

bool comes_before(info_t info1, info_t info2) {
	bool b = false;

	if(info1 == NULL || info2 == NULL)
		return false;

	b = info1->period->year < info2->period->year ? true : ( info1->period->year == info2->period->year ? 
															info1->period->month < info2->period->month : false );
	return b;
}

