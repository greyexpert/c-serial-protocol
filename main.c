/* 
 * File:   main.c
 * Author: grey
 *
 * Created on July 3, 2013, 3:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sprotocol.h"
#include "mock_serial.h"
#include "debug.h"

/*
 * 
 */
int main(int argc, char** argv) {

    uint8_t byte;
    uint8_t channel = SP_MAX_CHANNEL_COUNT;
    
    uint8_t v = 0;
    
    SPData data = SP_data(&v, sizeof(v));
    SPPackage p1 = SP_package(channel, data);
    
    SPWorker encoder = SP_worker(&p1);
    while ( SP_encodeByte(&encoder, &byte) == 1 ) {
        writeByte(byte);
    }
    
    SPPackage p2;
    SPWorker decoder = SP_worker(&p2);
    do {
        byte = readByte();
    } while ( SP_decodeByte(&decoder, byte) == SP_STATUS_FREE );
    
    //printb(p2.data.value);
    printf("%u\n", p2.data.uintVal);
    printf("Chanel: %s\n", p2.channel == p1.channel ? "Success" : "Fail");
    printf("Data: %s\n", p2.data.value == p1.data.value ? "Success" : "Fail");
    
    return (EXIT_SUCCESS);
}

