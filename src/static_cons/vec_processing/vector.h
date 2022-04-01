#include <stdio.h>

#define VEC_SIZE 100

typedef struct {
    float values[VEC_SIZE];
} Vector;

float vec_norm (Vector* vec_to_count);

void scan_vec (FILE* input, Vector* res);
void replace_cur_vec (Vector* rep_to, Vector* rep_from);