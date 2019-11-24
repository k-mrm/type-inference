#include <stdlib.h>
#include <assert.h>

#include "util.h"

Vector *New_Vector() {
    Vector *self = malloc(sizeof(Vector));

    self->data = malloc(sizeof(void *) * 16);
    self->len = 0;
    self->reserved = 16;

    return self;
}

Vector *New_Vector_With_Size(int size) {
    Vector *self = malloc(sizeof(Vector));

    self->data = malloc(sizeof(void *) * size);
    self->len = size;
    self->reserved = size;

    for(int i = 0; i < size; ++i) {
        self->data[i] = NULL;
    }

    return self;
}

void Delete_Vector(Vector *self) {
    free(self->data);

    free(self);
}

void vec_push(Vector *self, void *d) {
    if(self->len == self->reserved) {
        self->reserved *= 2;
        self->data = realloc(self->data, sizeof(void *) * self->reserved);
    }

    self->data[self->len++] = d;
}

void *vec_pop(Vector *self) {
    assert(self->len != 0);

    return self->data[--self->len];
}

void *vec_last(Vector *self) { return self->data[self->len - 1]; }

Map *New_Map() {
    Map *self = malloc(sizeof(Map));

    self->key = New_Vector();
    self->value = New_Vector();

    return self;
}

void map_push(Map *self, void *key, void *value) {
    vec_push(self->key, key);
    vec_push(self->value, value);
}
