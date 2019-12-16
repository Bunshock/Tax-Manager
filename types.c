/*
 * types.c
 *
 * TAD date_t implementation 
 */
#include <stdlib.h>
#include <time.h>

#include "types.h"

date_t date_empty() {
	date_t date = NULL;
	date = (date_t) calloc(1, sizeof(struct _time_t));
	return date;
}

date_t get_local_time(date_t date) {
	time_t rawtime;
	struct tm *time_info;
	time(&rawtime);
	time_info = localtime(&rawtime);

	date->day = time_info->tm_mday;
	date->month = time_info->tm_mon;
	date->year = time_info->tm_year;

	return date;
}

date_t destroy_date(date_t date) {
	free(date);
	date = NULL;
	return NULL;
}