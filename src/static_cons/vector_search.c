#include "vector_search.h"
#include <stdlib.h>
#include <math.h>

#define VECS_NUM 1000000



Vector* min_norm_dif (FILE* input, Vector* to_compare) {

    Vector* cur = malloc(sizeof (Vector));

    scan_vec(input, cur);

    Vector* result_vec = malloc(sizeof (Vector));
    float min_diff = fabsf(vec_norm(to_compare) - vec_norm(cur));

    replace_cur_vec(result_vec, cur);

    for(int i = 1; i < VECS_NUM; ++i) {

        if(fabsf(vec_norm(to_compare) - vec_norm(cur)) < min_diff) {
            min_diff = fabsf(vec_norm(to_compare) - vec_norm(cur));
            replace_cur_vec(result_vec, cur);
        }
        scan_vec(input, cur);
    }
    free(cur);
    return result_vec;
}
Vector* min_diff_search (const char* input_filename, const char* output_filename) {

    FILE* in_file = fopen(input_filename, "r");
    if (!in_file) {
        printf("file open error");
        return NULL;
    }
    Vector* to_compare = malloc(sizeof (Vector));
    scan_vec(in_file, to_compare);
    Vector* result = min_norm_dif(in_file, to_compare);


    FILE* out_file = fopen(output_filename, "w");
    for (int i = 0; i < VEC_SIZE; ++i) {
        fprintf(out_file, "%f ", result->values[i]);
    }
    free(to_compare);
    fclose(in_file);
    fclose(out_file);
    return result;
}

