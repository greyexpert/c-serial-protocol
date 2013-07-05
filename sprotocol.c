#include <string.h>
#include "sprotocol.h"

SPWorker SP_worker(SPPackage *package) {
    SPWorker worker = {};
    worker.package = package;

    return worker;
}

SPData SP_data(void *data, size_t size) {
    SPData _data = {};
    memcpy(&_data, data, size > SP_MAX_DATA_SIZE ? SP_MAX_DATA_SIZE : size);

    return _data;
}

SPPackage SP_package(uint8_t channel, SPData data) {
    SPPackage package = {};
    package.channel = channel;
    package.data = data;

    return package;
}

int SP_encodeByte(SPWorker *worker, uint8_t *byte) {
    if (worker->status == 0) {
        worker->_steps = 0;
        while (worker->_steps <= SP_MAX_DATA_SIZE && worker->package->data.value >> 7 * worker->_steps) {
            worker->_steps++;
        }

        *byte = (0x80 | (worker->package->channel & 0x0F) << 3) + worker->_steps; // Package Marker
        worker->status = 1;
    } else if (worker->status == 1) {
        if ((worker->_steps--) == 0) {
            worker->status = 0;
        }
        *byte = (worker->package->data.value >> (worker->_steps * 7)) & 0x7F;
    }

    return worker->status;
}

int SP_decodeByte(SPWorker *worker, uint8_t byte) {
    if (byte >= 0x80) { // Check if byte is marker
        worker->package->data.value = 0;
        worker->_steps = byte & 0x07;
        worker->package->channel = (byte & 0x7F) >> 3;
        worker->status = worker->_steps > 0 ? 1 : 2;
    } else if (worker->status == 1) {
        if ((--worker->_steps) == 0) {
            worker->status = 2;
        }

        worker->package->data.value <<= 7;
        worker->package->data.value |= byte;
    }

    return worker->status;
}

int SP_encode(SPWorker *worker, uint8_t *buffer, size_t size) {
    int i, status;
    for (i = 0; i < size; i++) {
        status = SP_encodeByte(worker, buffer + i);

        if (status != SP_STATUS_BUSY) break;
    }

    return status;
}

int SP_decode(SPWorker *worker, uint8_t *buffer, size_t size) {
    int i, status;
    for (i = 0; i < size; i++) {
        status = SP_decodeByte(worker, buffer[i]);

        if (status != SP_STATUS_READY) break;
    }

    return status;
}