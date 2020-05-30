/*
  @file tax.h
  @brief TAD tax and related functions implementations.
*/
#ifndef TAX_H
#define TAX_H

#include <stdbool.h>

#include "info.h"
#include "types.h"

/* tax_tree_t is a pointer to a structure. It contains a tree of taxes and its length. */
typedef struct _tax_tree_t *tax_tree_t;

/* Creates an empty tax tree. */
tax_tree_t tax_tree_empty();

/* Adds a new tax node with info @data to the tax tree pointed by @tax_tree.
 * Returns the new tax tree. */
tax_tree_t tax_add(tax_tree_t tax_tree, info_t data);

/* Removes the tax of period @period from the tax tree @head (of type @tax_type -> this 
 * will be implemented outside tax.c). */
tax_tree_t tax_remove(tax_tree_t tax_tree, period_t period);

/* Returns the @tax_tree tree length. */
unsigned int tax_tree_length(tax_tree_t tax_tree);

/* Returns true if there is already a tax with period @period in the tree. */
bool tax_exists(tax_tree_t tax_tree, period_t period);

/* Returns the info structure pointer for a specified period @period of the tax tree @tax_tree. */
info_t tax_info(tax_tree_t tax_tree, period_t period);

/* Puts time information specified in @date into the tax specified by @period. */
tax_tree_t set_payment_date(tax_tree_t tax_tree, period_t period, date_t date);

/* Returns true if the tax specified by @period has already been paid. */
bool tax_is_paid(tax_tree_t tax_tree, period_t period);

/* Prints the tax tree @tax_tree into file @file. */
void tax_dump(tax_tree_t tax_tree, FILE *file);

/* Frees all allocated memory of a tax_tree @tax_tree. */
tax_tree_t destroy_tax_tree(tax_tree_t tax_tree);

#endif