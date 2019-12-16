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
	printf("allocated new tax\n");
	tax->data = 0u;
	tax->next = NULL;
	return tax;
}

tax_list_t tax_list_empty() {
	tax_list_t tax_list = NULL;
	tax_list = (tax_list_t) calloc(1, sizeof(struct _tax_list_t));
	printf("allocated new tax list\n");
	tax_list->list = tax_empty();
	tax_list->length = 0u;
	return tax_list;
}

tax_t do_tax_add(tax_t head, unsigned int data) {
	tax_t res = head;
	tax_t new_node = tax_empty();
	new_node->data = data;

	if(head == NULL)
		return new_node;

	if(comes_before(head->data, data)) {
		res = new_node;
		new_node->next = head;
	}
	else {
		tax_t next_tax;
		while(comes_before(data, head->data) && head != NULL) {
			next_tax = head->next;
			if(next_tax == NULL || comes_before(next_tax->data, data)) {
				head->next = new_node;
				new_node->next = next_tax;
			}
			head = next_tax;
		}
	}
	return res;
}


tax_list_t tax_add(tax_list_t tax_list, unsigned int data) {
	if(tax_exists(tax_list, data)) {
		printf("Tax with specified period already exists.\n");
		return tax_list;
	}
	if(tax_list->list == NULL)
		tax_list->list = tax_empty();
	tax_list->list = do_tax_add(tax_list->list, data);
	tax_list->length++;
	assert(tax_list != NULL);
	return tax_list;
}

tax_t do_tax_remove(tax_t head, unsigned int period) {
	tax_t res = head;

	if(head == NULL)
		return NULL;

	bool is_equal = eq_period(head->data, period);
	if(is_equal) {
		res = head->next;
		free_node(head);
	}
	else {
		tax_t prev_tax = NULL;
		while(head != NULL && !eq_period(head->data, period)) {
			prev_tax = head;
			head = head->next;
		}
		if(head != NULL) {
			prev_tax->next = head->next;
			free_node(head);
		}
	}
	return res;
}

tax_list_t tax_remove(tax_list_t tax_list, unsigned int period) {
	assert(tax_list != NULL);
	if(!tax_exists(tax_list, period)) {
		printf("The specified tax does not exist.\n");
		return tax_list;
	}
	tax_list->list = do_tax_remove(tax_list->list, period);
	tax_list->length--;
	return tax_list;
}

bool tax_exists(tax_list_t tax_list, unsigned int period) {
	if(tax_list == NULL)
		return false;

	bool exists = false;
	tax_t head = tax_list->list;
	while(head != NULL && !exists) {
		exists = eq_period(head->data, period);
		head = head->next;
	}
	return exists;
}

bool tax_is_paid(tax_list_t tax_list, unsigned int period) {
	if(tax_list != NULL && period > 1) {;}
	return true;
}

void tax_dump(tax_list_t tax_list, FILE *file) {
	if(tax_list != NULL) {
		unsigned int len = tax_list->length;
		tax_t tax = tax_list->list;
		while(len > 0){
			info_dump(tax->data, file);
			fprintf(file, "\n");
			tax = tax->next;
			len--;
		}
	}
}

static tax_t free_node(tax_t node) {
    if(node != NULL){
        free(node);
        printf("freed tax node\n");
    }
    return (NULL);
}

tax_t destroy_tax(tax_t tax) {
	if(tax == NULL)
		return NULL;
	if(tax->next != NULL)
		destroy_tax(tax->next);
	free_node(tax);
	tax = NULL;
	return tax;
}

tax_list_t destroy_tax_list(tax_list_t tax_list) {
	if(tax_list == NULL)
		return NULL;
	if(tax_list->length > 0u)
		tax_list->list = destroy_tax(tax_list->list);
	free(tax_list);
	printf("freed tax_list\n");
	tax_list = NULL;
	return tax_list;
}
