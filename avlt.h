/*
  @file avlt.h
  @brief TAD avlt implementation.
*/
#ifndef AVLT_H
#define AVLT_H

#include <stdbool.h>

#include "info.h"
#include "types.h"

typedef struct _avlt_t *avlt_t;

avlt_t avlt_empty();

avlt_t avlt_add(avlt_t tree, info_t data);

bool avlt_contains(avlt_t tree, period_t period);

info_t avlt_info(avlt_t tree, period_t period);

unsigned int avlt_length(avlt_t tree);

avlt_t avlt_remove(avlt_t tree, period_t period);

avlt_t avlt_remove_all(avlt_t tree);

void avlt_dump(avlt_t tree, FILE *file);

avlt_t avlt_destroy(avlt_t tree);

#endif