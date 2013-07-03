#include "mock_serial.h"

static uint8_t _buff[MC_BUFFER_SIZE];
static int _readCoursor = 0;
static int _writeCoursor = 0;

void writeByte( uint8_t c  ) {
    _buff[_writeCoursor] = c;
    _writeCoursor = _writeCoursor + 1 >= sizeof(_buff) ? 0 : _writeCoursor + 1;
}

uint8_t readByte() {
    uint8_t byte = _buff[_readCoursor];
    _readCoursor = _readCoursor + 1 >= sizeof(_buff) ? 0 : _readCoursor + 1;
    
    return byte;
}

int read( uint8_t *b, int s ) {
    int i;
    for ( i = 0; i < s; i++ ) {
        b[i] = readByte();
    }
    
    return s;
}

int write( uint8_t *b, int s ) {
    int i;
    for ( i = 0; i < s; i++ ) {
        writeByte(b[i]);
    }
    
    return s;
}
