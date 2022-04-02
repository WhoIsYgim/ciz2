#include "vector.h"
#define VECS_NUM 1000000
#define FILENAME_BUF 100
#define FILES_NUM 10

Vector* min_norm_dif (FILE* input, Vector* to_compare);
Vector* min_diff_search (const char* input_filename, const char* output_filename);