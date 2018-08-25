#ifndef VECTOR_H__
#define VECTOR_H__

typedef struct pulseData_ {
    float voltage;
    float current;
    int micros_from_start;
} pulseData;

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


#endif
