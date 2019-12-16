/*
 * tax.c
 *
 * TAD tax implementation 
 */
#include <assert.h>
#include <stdlib.h>

#include "tax.h"

tax_t tax_empty() {
	tax_t tax = NULL;
	tax = (tax_t) calloc(1, sizeof(struct _tax_t));
	tax->data = NULL;
	tax->next = NULL;
	return tax;
}

tax_list_t tax_list_empty() {
	tax_list_t tax_list = NULL;
	tax_list = (tax_list_t) calloc(1, sizeof(struct _tax_list_t));
	tax_list->list = NULL;
	tax_list->length = 0u;
	return tax_list;
}

tax_t do_tax_add(tax_t head, info_t data) {
	tax_t res = head;
	tax_t new_node = tax_empty();
	new_node->data = data;

	if(head == NULL)
		return new_node;

	if(comes_before(head->data->period, data->period)) {
		res = new_node;
		new_node->next = head;
	}
	else {
		tax_t next_tax;
		while(comes_before(data->period, head->data->period) && head != NULL) {
			next_tax = head->next;
			if(next_tax == NULL || comes_before(next_tax->data->period, data->period)) {
				head->next = new_node;
				new_node->next = next_tax;
			}
			head = next_tax;
		}
	}
	return res;
}

tax_list_t tax_add(tax_list_t tax_list, info_t data) {
	if(tax_exists(tax_list, data->period)) {
		printf("Tax with specified period already exists.\n");
		return tax_list;
	}
	tax_list->list = do_tax_add(tax_list->list, data);
	tax_list->length++;
	assert(tax_list != NULL);
	return tax_list;
}

tax_t do_tax_remove(tax_t head, period_t period) {
	tax_t res = head;

	if(head == NULL)
		return NULL;

	bool is_equal = eq_period(head->data->period, period);
	if(is_equal) {
		res = head->next;
		destroy_tax(head);
	}
	else {
		tax_t prev_tax = NULL;
		while(head != NULL && !eq_period(head->data->period, period)) {
			prev_tax = head;
			head = head->next;
		}
		if(head != NULL) {
			prev_tax->next = head->next;
			destroy_tax(head);
		}
	}
	return res;
}

tax_list_t tax_remove(tax_list_t tax_list, period_t period) {
	assert(tax_list != NULL);
	if(!tax_exists(tax_list, period)) {
		printf("The specified tax does not exist.\n");
		return tax_list;
	}
	tax_list->list = do_tax_remove(tax_list->list, period);
	tax_list->length--;
	return tax_list;
}

bool tax_exists(tax_list_t tax_list, period_t period) {
	if(tax_list == NULL)
		return false;

	bool exists = false;
	tax_t head = tax_list->list;
	while(head != NULL && !exists) {
		exists = eq_period(head->data->period, period);
		head = head->next;
	}
	return exists;
}

tax_list_t set_payment_date(tax_list_t tax_list, period_t period, date_t date) {
	if(tax_list == NULL)
		return NULL;

	if(!tax_exists(tax_list, period))
		return tax_list;

	tax_t tax = tax_list->list;
	while(!eq_period(tax->data->period, period))
		tax = tax->next;

	if(tax->data->pay_date != NULL)
		free(tax->data->pay_date);

	date_t dest_date = date_empty();
	dest_date->day = date->day;
	dest_date->month = date->month;
	dest_date->year = date->year;
	tax->data->pay_date = dest_date;
	return tax_list;
}

bool tax_is_paid(tax_list_t tax_list, period_t period) {
	if(tax_list == NULL || !tax_exists(tax_list, period))
		return false;

	tax_t tax = tax_list->list;
	while(!eq_period(tax->data->period, period))
		tax = tax->next;

	return tax->data->paid;
}

void tax_dump(tax_list_t tax_list, FILE *file) {
	if(tax_list != NULL) {
		unsigned int len = tax_list->length;
		tax_t tax = tax_list->list;
		while(len > 0){
			fprintf(file, "%d/%d:\n", tax->data->period->month, tax->data->period->year);
			info_dump(tax->data, file);
			fprintf(file, "\n");
			tax = tax->next;
			len--;
		}
	}
}

tax_t destroy_tax(tax_t tax) {
	if(tax == NULL)
		return NULL;
	if(tax->next != NULL)
		destroy_tax(tax->next);
	destroy_info(tax->data);
	free(tax);
	tax = NULL;
	return tax;
}

tax_list_t destroy_tax_list(tax_list_t tax_list) {
	if(tax_list == NULL)
		return NULL;
	if(tax_list->length > 0u)
		tax_list->list = destroy_tax(tax_list->list);
	free(tax_list);
	tax_list = NULL;
	return tax_list;
}
