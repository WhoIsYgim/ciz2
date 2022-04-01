#include <time.h>
#include "vector_search.h"

int main () {
    Vector* a;
    time_t begin, end;

    begin = time(NULL);
    a = min_diff_search("text.txt", "output.txt");
    if(!a) {
        printf("err");
    }
    end = time(NULL);
    printf("%f",  difftime(end, begin));
    free(a);
}