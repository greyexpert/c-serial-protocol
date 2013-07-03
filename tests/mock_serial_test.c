/*
 * File:   mock_serial_test.c
 * Author: grey
 *
 * Created on Jul 3, 2013, 5:26:59 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mock_serial.h"

/*
 * Simple C Test Suite
 */

void test() {
    uint8_t in[5] = "test",
            out[5];
    
    write(in, 5);
    read(out, 5);
    
    if ( memcmp(in, out, 5) != 0 )
        printf("%%TEST_FAILED%% time=0 testname=test (mock_serial_test) message=error message sample\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% mock_serial_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test (mock_serial_test)\n");
    test();
    printf("%%TEST_FINISHED%% time=0 test (mock_serial_test) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
