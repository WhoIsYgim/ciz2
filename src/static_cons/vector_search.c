#include "vector_search.h"
#include <stdlib.h>
#include <math.h>

#define VECS_NUM 1000000
#define FILE_NUM 10
#define MAX_FILENAME_LEN 20



Vector* min_norm_dif (FILE* input, Vector* to_compare) {

    Vector* cur = malloc(sizeof (Vector));

    if(!cur) {
        printf("Memory allocation error\n");
        return NULL;
    }

    scan_vec(input, cur);

    Vector* result_vec = malloc(sizeof (Vector));

    if(!result_vec) {
        printf("Memory allocation error\n");
        return NULL;
    }

    float min_diff = fabsf(vec_norm(to_compare) - vec_norm(cur));

    replace_cur_vec(result_vec, cur);

    for(int i = 1; i < VECS_NUM/FILE_NUM; ++i) {

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
        printf("file open error\n");
        return NULL;
    }
    char* filename_buffer = malloc(sizeof(char)*MAX_FILENAME_LEN);

    fscanf(in_file,"%s",filename_buffer);
    FILE* cur_file = fopen(filename_buffer, "r");

    Vector* to_compare = malloc(sizeof (Vector));
    scan_vec(cur_file, to_compare);
    fclose(cur_file);

    Vector *result = NULL;

    for(int i = 0; i < FILE_NUM; ++i) {
        fscanf(in_file,"%s",filename_buffer);
        cur_file = fopen(filename_buffer, "r");
        if(!i) {
            result = min_norm_dif(cur_file, to_compare);
        }
        else {
            Vector* cur_min_diff_vec = min_norm_dif(cur_file, to_compare);
            if(vec_norm(cur_min_diff_vec) < vec_norm(result)) {
                replace_cur_vec(result, cur_min_diff_vec);
            }
            free(cur_min_diff_vec);
        }
    }

    FILE* out_file = fopen(output_filename, "w");
    for (int i = 0; i < VEC_SIZE; ++i) {
        fprintf(out_file, "%f ", result->values[i]);
    }

    free(to_compare);


    fclose(in_file);
    fclose(out_file);

    return result;
}

