/*
  @file tax.h
  @brief TAD tax and related functions implementations 
*/
#ifndef TAX_H
#define TAX_H

#include <stdbool.h>
#include "info.h"

/* tax_t is a pointer to a structure. It is implemented as a binary
 * search tree. */
typedef struct _tax_t *tax_t;

/* Creates an empty tax. */
tax_t tax_empty();

/* Adds a new tax node with info @data to the tax tree @root.
 * Returns the new tax tree root @result. */
tax_t tax_add(tax_t root, info_t data);

/* Removes the tax of date @date from the tax tree @root (of type
 * @tax_type -> this will be implemented outside tax.c). */
tax_t tax_remove(tax_t root, date_t date);

/* Returns true if the tax specified by @date has already been paid. */
bool tax_is_paid(tax_t root, date_t date);


#endif