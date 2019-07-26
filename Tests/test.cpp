#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../API/api.h"
#include "test.h"

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


#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")

#define EXPECT_EQ_STRING(expect, actual, alength) \
    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength) == 0, expect, actual, "%s")

#define EXPECT_TRUE(actual) EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s")

#define EXPECT_FALSE(actual) EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s")


static void test_api_recover(API &api){
    EXPECT_EQ_INT(Success, api.nrfjprog_recover());
}


static void test_api_eraseall(API &api){
    EXPECT_EQ_INT(Success, api.nrfjprog_eraseall());
}

static void test_api_reset(API &api){
    EXPECT_EQ_INT(Success, api.nrfjprog_reset());
}


static void test_api_program(API &api){
    EXPECT_EQ_INT(Success, api.nrfjprog_program("../Tests\\test_ALL.hex"));
}


static void test_api_memwr(API &api){
    api.nrfjprog_recover();
    EXPECT_EQ_INT(Success, api.nrfjprog_memwr("0x00008790", "0x12345678"));
}

static void test_api_memrd(API &api){

    EXPECT_EQ_INT(Success, api.nrfjprog_memrd("0x00008790"));
}

static void test_api_eraseuicr(API &api){

    EXPECT_EQ_INT(Success, api.nrfjprog_eraseuicr());
}

static void test_api_erasepage(API &api){
    EXPECT_EQ_INT(Success, api.nrfjprog_erasepage("0x2000", "0x8000"));
}

static void test_api_rbp(API &api){
    EXPECT_EQ_INT(Success, api.nrfjprog_rbp() && (api.nrfjprog_eraseall() != 0));
}

static void test_api_ids(API &api){
    QString ids;
    EXPECT_EQ_INT(Success, api.nrfjprog_ids(ids));
}


static void test_api_readcode(API &api){
    EXPECT_EQ_INT(Success, api.nrfjprog_readcode("../Tests\\test_readback.hex"));
}

static void test_api_setpath(API &api){
    api.nrfjprog_set_path("C:\\Program Files (x86)\\Nordic Semiconductor\\nrf5x\\bin\\nrfjprog.exe");
    QString s;
    EXPECT_EQ_INT(Success, api.nrfjprog_ids(s));
}


static void test_api(void){
    API api;

    test_api_setpath(api);

    test_api_recover(api);
    test_api_reset(api);
    test_api_memwr(api);
    test_api_memrd(api);
    test_api_eraseuicr(api);
    test_api_erasepage(api);
    test_api_eraseall(api);
    test_api_program(api);
    Sleep(3000);

    test_api_readcode(api);


    test_api_rbp(api);

    test_api_ids(api);

}



void test_all(void){
    test_api();
    printf("\nTests result:%d/%d (%3.2f%%) passed\n", test_pass,
           test_count, test_pass * 100.0 / test_count);
}
