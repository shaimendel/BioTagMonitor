#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "arduino.h"

void vector_init(vector *v)
{
  v->data = NULL;
  v->size = 0;
  v->count = 0;
}

void vector_reset(vector *v)
{
  if (v->data != NULL) {
    vector_free(v);
  }
  vector_init(v);
}

int vector_count(vector *v)
{
  return v->count;
}

void vector_add(vector *v, pulseData *e)
{
  if (v->size == 0) {
    v->size = 10;
    v->data = (pulseData*)malloc(sizeof(pulseData) * v->size);
    memset(v->data, '\0', sizeof(pulseData) * v->size);
  }

  // condition to increase v->data:
  // last slot exhausted
  if (v->size == v->count) {
    v->size *= 2;
    v->data = (pulseData*)realloc(v->data, sizeof(pulseData) * v->size);
  }

  v->data[v->count] = *e;
  v->count++;
}

void vector_set(vector *v, int index, pulseData *e)
{
  if (index >= v->count) {
    return;
  }

  v->data[index] = *e;
}

pulseData *vector_get(vector *v, int index)
{
  if (index >= v->count) {
    return NULL;
  }

  return &v->data[index];
}

void vector_delete(vector *v, int index)
{
  if (index >= v->count) {
    return;
  }

  //v->data[index] = NULL;

  int i, j;
  pulseData *newarr = (pulseData*)malloc(sizeof(pulseData) * v->count * 2);
  for (i = 0, j = 0; i < v->count; i++) {
      newarr[j] = v->data[i];
      j++;
  }

  free(v->data);

  v->data = newarr;
  v->count--;
}

void vector_free(vector *v)
{
  free(v->data);
  v->data = NULL;
}

void vector_serialize(vector* v) {
  for (int i = 0; i < vector_count(v); i++) {
    pulseData* d = vector_get(v, i);

    if (i > 0) {
      Serial.print(",");
    }
    Serial.print(d->voltage, 5);
    Serial.print("@");
    Serial.print(d->current, 5);
    Serial.print("@");
    Serial.print(d->micros_from_start);
  }
}

//int main(void)
//{
//  vector v;
//  vector_init(&v);
//
//  vector_add(&v, "emil");
//  vector_add(&v, "hannes");
//  vector_add(&v, "lydia");
//  vector_add(&v, "olle");
//  vector_add(&v, "erik");
//
//  int i;
//  printf("first round:\n");
//  for (i = 0; i < vector_count(&v); i++) {
//    printf("%s\n", vector_get(&v, i));
//  }
//
//  vector_delete(&v, 1);
//  vector_delete(&v, 3);
//
//  printf("second round:\n");
//  for (i = 0; i < vector_count(&v); i++) {
//    printf("%s\n", vector_get(&v, i));
//  }
//
//  vector_free(&v);
//
//  return 0;
//}
