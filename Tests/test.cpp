#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../API/api.h"
#include "test.h"

//static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n",\
            __FILE__, __LINE__, expect, actual);\
            /*main_ret = 1;*/\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual),\
    expect, actual, "%d")


static void test_api_recover(API &api){
    EXPECT_EQ_INT(0, api.nrfjprog_recover("UNKNOWN"));
}


static void test_api_eraseall(API &api){
    EXPECT_EQ_INT(0, api.nrfjprog_eraseall("UNKNOWN", false));
}


static void test_api_reset(API &api){
    EXPECT_EQ_INT(0, api.nrfjprog_reset("UNKNOWN"));
}


static void test_api_program(API &api){
    EXPECT_EQ_INT(0, api.nrfjprog_program("D:\\Workspace\\QT\\Nrfjprogmer\\Tests\\test_ALL.hex",
                                          "UNKNOWN", true,
                                          true, false,
                                          false, false,
                                          false, false));
}



static void test_api(void){
    API api;
    test_api_recover(api);
    test_api_eraseall(api);
    test_api_reset(api);
    test_api_program(api);

}



void test_all(void){
    test_api();
    printf("\n%d/%d (%3.2f%%) passed\n", test_pass,
           test_count, test_pass * 100.0 / test_count);
}
