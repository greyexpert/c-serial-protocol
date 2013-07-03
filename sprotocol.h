/* 
 * File:   sprotocol.h
 * Author: grey
 *
 * Created on July 3, 2013, 4:39 PM
 */

#ifndef SPROTOCOL_H
#define	SPROTOCOL_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef union __SPData {
        uint8_t data8list[sizeof(uint64_t)];
        uint16_t data16list[sizeof(uint64_t) / sizeof(uint16_t)];
        uint32_t data32list[sizeof(uint64_t) / sizeof(uint32_t)];
        uint64_t data64;
    } SPData;
    
    typedef enum __SPChanelStatus {
        SPReady, SPBusy
    } SPChanelStatus;
    
    typedef struct __SPChanel {
        uint8_t chanel;
        SPData data;
        SPChanelStatus status;
    } SPChanel;
    
    
    SPChanelStatus SP_encodeByte( SPChanel *, uint8_t * );
    SPChanelStatus SP_decodeByte( SPChanel *, uint8_t );
    
#ifdef	__cplusplus
}
#endif

#endif	/* SPROTOCOL_H */

