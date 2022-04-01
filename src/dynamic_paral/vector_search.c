#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/wait.h>


#include "vector_search.h"


#define MAX_FILENAME_LEN 20



Vector* min_norm_dif (FILE* input, Vector* to_compare) {

    Vector* cur = malloc(sizeof (Vector));

    scan_vec(input, cur);

    Vector* result_vec = malloc(sizeof (Vector));
    float min_diff = fabsf(vec_norm(to_compare) - vec_norm(cur));

    replace_cur_vec(result_vec, cur);

    for(int i = 1; i < VECS_NUM/FILES_NUM; ++i) {

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
    if(!in_file) {
        printf("Input file open error paral!\n");
        return NULL;
    }
    char* filename_buffer_str = malloc(sizeof (char)*MAX_FILENAME_LEN);

    fscanf(in_file, "%s", filename_buffer_str);
    FILE* compare_vec = fopen(filename_buffer_str, "w");

    Vector* to_compare = malloc(sizeof (Vector));
    scan_vec(compare_vec, to_compare);

    fclose(compare_vec);

    int proc_count = 1;
    pid_t proc = getpid();
    fscanf(in_file, "%s", filename_buffer_str);

    Vector* shared_vecs = mmap(NULL, sizeof(Vector)*FILES_NUM, PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1,0);


    while (proc) {

        proc = fork();
        if (proc < 0) {
            printf("Fork failed!\n");
            return NULL;
        }
        if (proc) {
            fscanf(in_file, "%s", filename_buffer_str);
        }
        ++proc_count;

        if(proc_count == FILES_NUM) {
            if(proc) {
                proc_count = 1;
                break;
            }
        }
    }

    FILE* cur_proc_file = fopen(filename_buffer_str,"r");

    Vector* cur_min_dif_vec = min_norm_dif(cur_proc_file, to_compare);

    fclose(cur_proc_file);

    replace_cur_vec(&shared_vecs[proc_count-1],cur_min_dif_vec);


    if(!proc) {
        exit(0);
    }

    int exit_proc_count = 0;

    while (exit_proc_count < FILES_NUM-1) {
        pid_t status;
        waitpid(-1, &status, 0);
        ++exit_proc_count;
    }

    Vector* result = malloc(sizeof (Vector));

    replace_cur_vec(result, &shared_vecs[0]);
    float min_diff = fabsf(vec_norm(to_compare) - vec_norm(&shared_vecs[0]));

    for ( int i = 1; i < FILES_NUM; ++i) {
        if(fabsf(vec_norm(to_compare) - vec_norm(&shared_vecs[i])) < min_diff) {
            min_diff = fabsf(vec_norm(to_compare) - vec_norm(&shared_vecs[i]));
            replace_cur_vec(result, &shared_vecs[i]);
        }
    }

    free(to_compare);
    munmap(shared_vecs, sizeof(Vector)*FILES_NUM);
    FILE* out_file = fopen(output_filename, "w");
    for (int i = 0; i < VEC_SIZE; ++i) {
        fprintf(out_file, "%f ", result->values[i]);
    }

    fclose(in_file);
    fclose(out_file);
    return result;
}

