#include <gtest/gtest.h>
#include <cmath>

extern "C" {
//#include "vector_search.h"
#include "vector.h"

};


TEST(VEC_NORM, TEST_VEC_NORM) {
    Vector* test_vec =(Vector*)malloc(sizeof(Vector));

    for(int i = 0; i < VEC_SIZE; ++i) {
        test_vec->values[i] = (float)i;
    }
    float expected_norm = sqrtf(328350);
    float test_vec_norm = vec_norm(test_vec);

    EXPECT_EQ(test_vec_norm, expected_norm);

    free(test_vec);
}

TEST(SCAN_VEC, TEST_SCAN_VEC) {
    Vector* expected_vector = (Vector*)malloc(sizeof (Vector));
    for (int i = 0; i < VEC_SIZE; ++i) {
        expected_vector->values[i] = (float)i;
    }
    Vector* test_vec =(Vector*)malloc(sizeof (Vector));

    FILE* input_file = fopen("./tests/input/test_vector.txt","r");

    scan_vec(input_file, test_vec);
    bool result = true;
    for(int i = 0; i < VEC_SIZE; ++i){
        if(expected_vector->values[i] != test_vec->values[i]) {
            result = false;
        }
    }
    EXPECT_TRUE(result);

    fclose(input_file);
    free(expected_vector);
    free(test_vec);
}

/*TEST(STRESS, STRESS_TEST) {
    FILE* input_file = fopen("stest.txt", "r");
    FILE* output_file = fopen("out_file.txt", "w");
    Vector* test_vector = NULL;
    time_t begin, end;

    begin = time(NULL);

    test_vector = min_dif_search(input_file, output_file);

    end = time(NULL);
    std::cout << "runtime: " << difftime(end, begin) << "\n";
    fclose(input_file);
    fclose(output_file);

    FILE* check = fopen("scheck.txt", "r");
    Vector* check_vector = (Vector*)malloc(sizeof(Vector));

    scan_vec(check, check_vector);
    fclose(check);

    bool result = true;
    for(int i = 0; i < VEC_SIZE; ++i){
        if(check_vector->values[i] != test_vector->values[i]) {
            result = false;
        }
    }

    EXPECT_TRUE(result);

    free(test_vector);
    free(check_vector);
}
*/