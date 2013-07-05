/* 
 * File:   sprotocol.h
 * Author: grey
 *
 * Created on July 3, 2013, 4:39 PM
 */

#ifndef SPROTOCOL_H
#define	SPROTOCOL_H

#include <stdint.h>

#define SP_MAX_DATA_SIZE 6
#define SP_MAX_CHANNEL_COUNT 15

#define SP_STATUS_FREE 0
#define SP_STATUS_BUSY 1
#define SP_STATUS_READY 2

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef union {
        /* Unsigned */
        uint8_t  u8list[sizeof(uint64_t)];
        uint16_t u16list[sizeof(uint64_t) / sizeof(uint16_t)];
        uint32_t u32list[sizeof(uint64_t) / sizeof(uint32_t)];
        
        /* Unsigned */
        int8_t  s8list[sizeof(uint64_t)];
        int16_t s16list[sizeof(uint64_t) / sizeof(int16_t)];
        int32_t s32list[sizeof(uint64_t) / sizeof(int32_t)];
        
        int32_t intVal;
        uint32_t uintVal;
        
        uint8_t  data[sizeof(uint64_t)];
        uint64_t value;
    } SPData __attribute__((__transparent_union__));
    
    typedef struct {
        uint8_t channel;
        SPData data;
    } SPPackage;
    
    typedef struct {
        SPPackage *package;
        int status;
        int _steps;
    } SPWorker;
    
    
    int SP_encodeByte( SPWorker *, uint8_t * );
    int SP_decodeByte( SPWorker *, uint8_t );
    
    int SP_encode( SPWorker *, uint8_t *, size_t );
    int SP_decode( SPWorker *, uint8_t *, size_t );
    
    SPData SP_data( void *, size_t );
    SPPackage SP_package( uint8_t, SPData );
    SPWorker SP_worker( SPPackage * );

#ifdef	__cplusplus
}
#endif

#endif	/* SPROTOCOL_H */

