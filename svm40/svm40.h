/*
 * Copyright (c) 2020, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SVM40_H
#define SVM40_H

#include "sensirion_arch_config.h"
#include "sensirion_common.h"
#include "sensirion_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SVM40_I2C_ADDRESS 0x6a

#define SVM40_CMD_START_CONTINUOUS_MEASUREMENT 0x0010
#define SVM40_CMD_STOP_MEASUREMENT 0x0104
#define SVM40_CMD_READ_MEASURED_VALUES_AS_INTEGERS 0x03A6
#define SVM40_CMD_READ_MEASURED_VALUES_AS_INTEGERS_WITH_RAW_PARAMETERS 0x03B0
#define SVM40_CMD_GET_VERSION 0xD100
#define SVM40_CMD_GET_SERIAL_NUMBER 0xD033
#define SVM40_CMD_DEVICE_RESET 0xD304

/**
 * Check if SVM40 sensor is available
 *
 * @return  NO_ERROR on success, an error code otherwise
 */
int16_t svm40_probe(void);

struct svm40_version_information {

    /** Major part of the firmware version major.minor */
    uint8_t firmware_major;
    /** Minor part of the firmware version major.minor */
    uint8_t firmware_minor;
    /** Marks a development firmware version */
    bool firmware_debug;

    /** Major part of the hardware version major.minor */
    uint8_t hardware_major;
    /** Minor part of the hardware version major.minor */
    uint8_t hardware_minor;

    /** Major part of the protocol version major.minor */
    uint8_t protocol_major;
    /** Minor part of the protocol version major.minor */
    uint8_t protocol_minor;
};

/**
 * Read the hardware and firmware version information
 *
 * @param version_information   Struct to store the version information
 * @return  NO_ERROR on success, an error code otherwise
 */
int16_t
svm40_get_version(struct svm40_version_information* version_information);

/**
 * Start a continuous measurement.
 *
 * @note This command is only available in idle mode.
 * @return  NO_ERROR on success, an error code otherwise
 */
int16_t svm40_start_continuous_measurement(void);

/**
 * Return the driver version
 *
 * @return  Driver version string
 */
const char* svm40_get_driver_version(void);

#ifdef __cplusplus
}
#endif

#endif /* SVM40_H */
