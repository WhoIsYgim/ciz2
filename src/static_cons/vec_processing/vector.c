#include <math.h>
#include "vector.h"


float vec_norm (Vector* vec_to_count){
    if (!vec_to_count) {
        return -1;
    }
    double comp_squares_sum = 0;
    for (int i = 0; i < VEC_SIZE; ++i) {
        comp_squares_sum += vec_to_count->values[i]*vec_to_count->values[i];
    }
    return (float)(sqrt(comp_squares_sum));
}

void scan_vec (FILE* input, Vector* res) {
    if (!input) {
        printf("Input file open error!\n");
        return;
    }
    if(!res) {
        printf("Vector ident err\n");
    }

    for(int i = 0; i < VEC_SIZE; ++i) {

        fscanf(input,"%f", &(res->values[i]));
    }
}
void replace_cur_vec (Vector* rep_to, Vector* rep_from) {
    if(!rep_from || !rep_to){
        printf("Vector ident err\n");
        return;

    }
    for ( int i = 0; i < VEC_SIZE; ++i) {
        rep_to->values[i] = rep_from->values[i];
    }
}
