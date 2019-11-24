#ifndef TI_UTIL_H
#define TI_UTIL_H

typedef struct Vector {
    void **data;
    int len;
    int reserved;
} Vector;

Vector *New_Vector(void);
Vector *New_Vector_With_Size(int);
void Delete_Vector(Vector *);
void vec_push(Vector *self, void *d);
void *vec_pop(Vector *self);
void *vec_last(Vector *self);

typedef struct Map {
    Vector *key;
    Vector *value;
} Map;

Map *New_Map(void);
void map_push(Map *, void *, void *);

#endif
