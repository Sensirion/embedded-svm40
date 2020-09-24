#include "sensirion_test_setup.h"
#include "svm40.h"
#include <inttypes.h>
#include <stdio.h>

#define MAX_VOC_INDEX 500
#define MIN_VOC_INDEX 0
#define MAX_VOC_RAW 65535
#define MIN_VOC_RAW 0
#define MAX_RH_RAW (119 * 100)
#define MIN_RH_RAW (-6 * 100)
#define MAX_T (130 * 200)
#define MIN_T (-45 * 200)

TEST_GROUP (SVM40_Tests) {
    void setup() {
        int16_t error;
        sensirion_i2c_init();

        // Select MUX 2 channel 7 (SVM40) on ch-sta-p-rp0002
        error = sensirion_i2c_mux_set_single_channel(0x72, 7);

        CHECK_ZERO_TEXT(error, "sensirion_i2c_mux_set_single_channel");
    }

    void teardown() {
        int16_t error;
        error = svm40_device_reset();
        CHECK_ZERO_TEXT(error, "svm40_device_reset");
        sensirion_i2c_release();
    }
};

TEST (SVM40_Tests, SVM40_Test_Driver_Version) {
    const char* version = svm40_get_driver_version();
    CHECK_TEXT(version, "svm40_get_driver_version();")
    printf("SVM40 Driver version: %s\n", version);
}

TEST (SVM40_Tests, SVM40_Test_Probe) {
    int16_t error;
    error = svm40_probe();
    CHECK_ZERO_TEXT(error, "svm40_probe");
}

TEST (SVM40_Tests, SVM40_Test_Get_Serial) {
    int16_t error;
    char serial_id[SVM40_MAX_SERIAL_LEN];
    error = svm40_get_serial(serial_id);
    CHECK_ZERO_TEXT(error, "svm40_get_serial");
    printf("Serial Number: %s\n", serial_id);
}

TEST (SVM40_Tests, SVM40_Test_Get_Version) {
    int16_t error;
    struct svm40_version_information version_information;
    error = svm40_get_version(&version_information);
    CHECK_ZERO_TEXT(error, "svm40_get_version");
    if (version_information.firmware_debug) {
        printf("Development firmware version: ");
    }
    printf(
        "FW: %u.%u, HW: %u.%u, protocol: %u.%u\n",
        version_information.firmware_major, version_information.firmware_minor,
        version_information.hardware_major, version_information.hardware_minor,
        version_information.protocol_major, version_information.protocol_minor);
}

TEST (SVM40_Tests, SVM40_Test_Measurement) {
    int16_t error;
    error = svm40_start_continuous_measurement();
    CHECK_ZERO_TEXT(error, "svm40_start_continuous_measurement");

    int16_t voc_index;
    int16_t relative_humidity;
    int16_t temperature;

    sensirion_sleep_usec(SVM40_MEASUREMENT_INTERVAL_USEC); /* wait 1s */
    error = svm40_read_measured_values_as_integers(
        &voc_index, &relative_humidity, &temperature);
    CHECK_ZERO_TEXT(error, "svm40_read_measured_values_as_integers");

    CHECK_TRUE_TEXT(voc_index >= MIN_VOC_INDEX && voc_index <= MAX_VOC_INDEX,
                    "svm40_read_measured_values_as_integers");
    CHECK_TRUE_TEXT(relative_humidity >= MIN_RH_RAW &&
                        relative_humidity <= MAX_RH_RAW,
                    "svm40_read_measured_values_as_integers");
    CHECK_TRUE_TEXT(temperature >= MIN_T && temperature <= MAX_T,
                    "svm40_read_measured_values_as_integers");

    error = svm40_stop_measurement();
    CHECK_ZERO_TEXT(error, "svm40_stop_measurement");
}

TEST (SVM40_Tests, SVM40_Test_Mesurement_Raw) {
    int16_t error;
    error = svm40_start_continuous_measurement();
    CHECK_ZERO_TEXT(error, "svm40_start_continuous_measurement");

    int16_t voc_index;
    int16_t relative_humidity;
    int16_t temperature;
    uint16_t voc_ticks_raw;
    int16_t uncompensated_relative_humidity_raw;
    int16_t uncompensated_temperature;

    sensirion_sleep_usec(SVM40_MEASUREMENT_INTERVAL_USEC); /* wait 1s */
    error = svm40_read_measured_values_as_integers_with_raw_params(
        &voc_index, &relative_humidity, &temperature, &voc_ticks_raw,
        &uncompensated_relative_humidity_raw, &uncompensated_temperature);
    CHECK_ZERO_TEXT(error,
                    "svm40_read_measured_values_as_integers_with_raw_params");

    CHECK_TRUE_TEXT(voc_index >= MIN_VOC_INDEX && voc_index <= MAX_VOC_INDEX,
                    "svm40_read_measured_values_as_integers");
    CHECK_TRUE_TEXT(relative_humidity >= MIN_RH_RAW &&
                        relative_humidity <= MAX_RH_RAW,
                    "svm40_read_measured_values_as_integers_with_raw_params");
    CHECK_TRUE_TEXT(temperature >= MIN_T && temperature <= MAX_T,
                    "svm40_read_measured_values_as_integers_with_raw_params");
    CHECK_TRUE_TEXT(uncompensated_relative_humidity_raw >= MIN_RH_RAW &&
                        uncompensated_relative_humidity_raw <= MAX_RH_RAW,
                    "svm40_read_measured_values_as_integers_with_raw_params");
    CHECK_TRUE_TEXT(uncompensated_temperature >= MIN_T &&
                        uncompensated_temperature <= MAX_T,
                    "svm40_read_measured_values_as_integers_with_raw_params");
    CHECK_TRUE_TEXT(voc_ticks_raw >= MIN_VOC_RAW &&
                        voc_ticks_raw <= MAX_VOC_RAW,
                    "svm40_read_measured_values_as_integers_with_raw_params");

    error = svm40_stop_measurement();
    CHECK_ZERO_TEXT(error, "svm40_stop_measurement");
}

TEST (SVM40_Tests, SVM40_Test_Reset_Device_Idle) {
    int16_t error;
    error = svm40_device_reset();
    CHECK_ZERO_TEXT(error, "svm40_device_reset");
}

TEST (SVM40_Tests, SVM40_Test_Reset_Device_Measure_Mode) {
    int16_t error;
    error = svm40_start_continuous_measurement();
    CHECK_ZERO_TEXT(error, "svm40_start_continuous_measurement");

    error = svm40_device_reset();
    CHECK_ZERO_TEXT(error, "svm40_device_reset");
}
