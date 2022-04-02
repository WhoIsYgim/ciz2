#include <time.h>
#include "vector_search.h"

int main () {
    Vector* a;
    time_t begin, end;

    begin = time(NULL);
    a = min_diff_search("in_file.txt", "output.txt");

    if(!a) {
        printf("Search operation error!\n");
    }

    end = time(NULL);
    printf("%f\n",  difftime(end, begin));

    free(a);
}