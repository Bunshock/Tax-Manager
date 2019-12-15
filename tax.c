/*
 * tax.c
 *
 * TAD tax implementation 
 */
#include <assert.h>

#include "tax.h"
#include "info.h"

struct _tax_t {
	info_t data;
	tax_t left;
	tax_t right;
}

tax_t tax_empty() {
	tax_t tax = NULL;
	tax = (tax_t) calloc(1, sizeof(struct _tax_t));
	tax->data = info_empty();
	tax->left = NULL;
	tax->right = NULL;
}

tax_t tax_add(tax_t root, info_t data) {
	
}