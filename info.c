/*
 * info.c
 *
 * TAD info implementation 
 */
#include <assert.h>
#include <stdlib.h>

#include "info.h"


info_t info_empty() {
	info_t info = NULL;
	info = (info_t) calloc(1, sizeof(struct _info_t));
	return info;
}

void info_dump(info_t info, FILE *file) {
	if(info != NULL) {
		fprintf(file, INFO_FORMAT, info->cost, info->currency, info->bill, info->paid, info->year, 
			        info->month, info->consumption, info->unit);
		fprintf(file, "\n");
	}
}

bool comes_before(info_t info1, info_t info2) {
	if(info1 == NULL || info2 == NULL)
		return false;

	bool b = false;
	b = info1->year < info2->year ? true : ( info1->year == info2->year ? info1->month < info2->month : false );
	return b;
}

bool eq_period(info_t info1, info_t info2) {
	if(info1 == NULL || info2 == NULL)
		return false;

	bool b = false;
	b = info1->year == info2->year ? info1->month == info2->month : false;
	return b;
}

info_t destroy_info(info_t info) {
	free(info);
	info = NULL;
	return NULL;
}

