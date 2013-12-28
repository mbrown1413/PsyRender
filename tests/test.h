#ifndef _TEST_H
#define _TEST_H

#include <stdio.h>

#define TEST_PASS (-1)
#define TEST_SKIP (-2)
#define TEST_FAIL (__LINE__)
#define ASSERT(s) if((s) != true) { return TEST_FAIL; }

typedef int (*test_func_t)();

static inline int test_main(test_func_t* test_functions) {
    int result;
    test_func_t test;

    int num_tests = 0;
    int failures = 0;
    int skips = 0;
    for(int i=0; ; i++) {
        test = test_functions[i];
        if(test == NULL) {
            break;
        }
        num_tests++;
        result = test();
        if(result == TEST_PASS) {
            //printf("Passsed\n");
        } else if(result == TEST_SKIP) {
            skips++;
        } else {
            printf("Failed, line %d\n", result);
            failures++;
        }
    }

    if(failures) {
        printf("Tests Failed: %d of %d", failures, num_tests-skips);
    } else {
        printf("All %d Tests Passed!", num_tests-skips);
    }
    if(skips) {
        printf("  (excluding %d skipped)", skips);
    }
    printf("\n");
    return failures;
}

#endif
