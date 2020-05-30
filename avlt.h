/*
  @file avlt.h
  @brief TAD avlt implementation.
*/
#ifndef AVLT_H
#define AVLT_H

#include <stdbool.h>

#include "info.h"
#include "types.h"

/* avlt_t is a pointer to a structure. Points to an auto-balanced binary search tree. The order of the
 * tree's nodes is defined by a period value. */
typedef struct _avlt_t *avlt_t;

/* Creates an empty avl tree. */
avlt_t avlt_empty();

/* Adds a node to the tree @tree with information @data. */
avlt_t avlt_add(avlt_t tree, info_t data);

/* Returns true if the tree @tree contains a node with period @period. */
bool avlt_contains(avlt_t tree, period_t period);

/* Returns the information of the node of period @period. If there is not a node with period @period, the
 * function returns NULL. */
info_t avlt_info(avlt_t tree, period_t period);

/* Returns the number of nodes of the tree @tree. */
unsigned int avlt_length(avlt_t tree);

/* Deletes the node, if it exists, of period @period from the tree @tree. */
avlt_t avlt_remove(avlt_t tree, period_t period);

/* Deletes all the nodes from the tree @tree, but does not destroy it. */
avlt_t avlt_remove_all(avlt_t tree);

/* Prints out the information from the tree @tree to the file @file. */
void avlt_dump(avlt_t tree, FILE *file);

/* Frees all allocated memory used by the tree @tree. */
avlt_t avlt_destroy(avlt_t tree);

#endif
