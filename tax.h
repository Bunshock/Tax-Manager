/*
  @file tax.h
  @brief TAD tax and related functions implementations.
*/
#ifndef TAX_H
#define TAX_H

#include <stdbool.h>
#include <stdio.h>

#include "info.h"
#include "types.h"

/* tax_t is a pointer to a structure. It is implemented as a linked list. Taxes will be 
 * sorted from earliest to oldest counting from the head. For example,
 * head->(NULL, december, next)->(prev, november, next)->...->(prev, january, NULL)<-end */
typedef struct _tax_t {
	info_t data;
	struct _tax_t *next;
} *tax_t;

/* tax_list_t is a pointer to a structure. It contains a list of taxes tax_t and its 
 * length. */
typedef struct _tax_list_t {
	tax_t list;
	unsigned int length;
} *tax_list_t;

/* Creates an empty tax. */
tax_t tax_empty();

/* Creates an empty tax list. */
tax_list_t tax_list_empty();

/* Adds a new tax node with info @data to the tax list pointed by @tax_list.
 * Returns the new tax list. */
tax_list_t tax_add(tax_list_t tax_list, info_t data);

/* Removes the tax of period @period from the tax list @head (of type @tax_type -> this 
 * will be implemented outside tax.c). */
tax_list_t tax_remove(tax_list_t tax_list, period_t period);

/* Returns the @tax_list list length. */
unsigned int tax_list_length(tax_list_t tax_list);

/* Returns true if there is already a tax with period @period in the list. */
bool tax_exists(tax_list_t tax_list, period_t period);

/* Puts time information specified in @date into the tax specified by @period. */
tax_list_t set_payment_date(tax_list_t tax_list, period_t period, date_t date);

/* Returns true if the tax specified by @period has already been paid. */
bool tax_is_paid(tax_list_t tax_list, period_t period);

/* Prints the tax list @tax_list into file @file. */
void tax_dump(tax_list_t tax_list, FILE *file);

/* Frees allocated memory for specified @tax. */
tax_t destroy_tax(tax_t tax);

/* Frees all allocated memory of a tax_list @tax_list. */
tax_list_t destroy_tax_list(tax_list_t tax_list);

#endif