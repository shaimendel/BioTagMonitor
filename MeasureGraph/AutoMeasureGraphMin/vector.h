#pragma once
#include "pulse.h"

typedef struct vector_ {
    pulseData* data;
    int size;
    int count;
} vector;

void vector_init(vector*);
int vector_count(vector*);
void vector_add(vector*, pulseData*);
void vector_set(vector*, int, pulseData*);
pulseData* vector_get(vector*, int);
void vector_delete(vector*, int);
void vector_free(vector*);
void vector_reset(vector*);
void vector_serialize(vector*);
bool vector_is_empty(vector*);
pulseData* vector_get_last_sample(vector*);
