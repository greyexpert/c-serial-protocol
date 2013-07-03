/* 
 * File:   mock_serial.h
 * Author: grey
 *
 * Created on July 3, 2013, 5:13 PM
 */

#ifndef MOCK_SERIAL_H
#define	MOCK_SERIAL_H

#include <stdint.h>

#define MC_BUFFER_SIZE 100

#ifdef	__cplusplus
extern "C" {
#endif

    void writeByte( uint8_t );
    uint8_t readByte( void );
    
    int read( uint8_t *, int );
    int write( uint8_t *, int );

#ifdef	__cplusplus
}
#endif

#endif	/* MOCK_SERIAL_H */

