/*
 * tax.c
 *
 * TAD tax implementation 
 */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "tax.h"
#include "avlt.h"

struct _tax_tree_t {
	avlt_t root;
	unsigned int length;
};

tax_tree_t tax_tree_empty() {
	tax_tree_t tax_tree = calloc(1, sizeof(struct _tax_tree_t));
	tax_tree->root = avlt_empty();
	tax_tree->length = 0u;
	assert(tax_tree != NULL);
	return tax_tree;
}

tax_tree_t tax_add(tax_tree_t tax_tree, info_t data) {
	tax_tree->root = avlt_add(tax_tree->root, data);
	tax_tree->length++;
	return tax_tree;
}

tax_tree_t tax_remove(tax_tree_t tax_tree, period_t period) {
	tax_tree->root = avlt_remove(tax_tree->root, period);
	tax_tree->length--;
	return tax_tree;
}

unsigned int tax_tree_length(tax_tree_t tax_tree) {
	return tax_tree->length;
}

bool tax_exists(tax_tree_t tax_tree, period_t period) {
	return avlt_contains(tax_tree->root, period);
}

info_t tax_info(tax_tree_t tax_tree, period_t period) {
	return avlt_info(tax_tree->root, period);
}

tax_tree_t set_payment_date(tax_tree_t tax_tree, period_t period, date_t date) {
	assert(tax_tree->root != NULL && period != NULL && date != NULL);
	info_t info = tax_info(tax_tree, period);
	
	if(info != NULL) {
		if(info->pay_date != NULL) {
			free(info->pay_date);
			info->pay_date = NULL;
		}
		info->pay_date = date;
	}

	return tax_tree;
}

bool tax_is_paid(tax_tree_t tax_tree, period_t period) {
	assert(tax_tree->root != NULL && period != NULL);
	info_t info = tax_info(tax_tree, period);
	
	if(info == NULL)
		return false;

	return info->paid;
}

void tax_dump(tax_tree_t tax_tree, FILE *file) {
	assert(tax_tree != NULL && file != NULL);
	avlt_dump(tax_tree->root, file);
	fprintf(file, "\nTax count: %u\n", tax_tree_length(tax_tree));
}

tax_tree_t destroy_tax_tree(tax_tree_t tax_tree) {
	assert(tax_tree != NULL);
	tax_tree->root = avlt_destroy(tax_tree->root);
	free(tax_tree);
	tax_tree = NULL;
	return tax_tree;
}