#include <Arduino.h>
#include <arduino-svm40.h>
#include <Wire.h>

void setup() {

  // Initialize Serial for debugging
  Serial.begin(115200);

  while (!Serial) {
    delay(100);
  }

  int16_t err;
  uint16_t ix;

  const char* driver_version = svm40_get_driver_version();
  if (driver_version) {
    Serial.print("SVM40 driver version");
    Serial.println(driver_version);
  } else {
    Serial.println("fatal: Getting driver version failed");
    return;
  }

  /* Initialize I2C bus */
  Wire.begin();

  /* Busy loop for initialization. The main loop does not work without
     a sensor. */
  while (svm40_probe() != NO_ERROR) {
    Serial.println("SVM40 sensor probing failed");
    delay(1000);
  }
  Serial.println("SVM40 sensor probing successful");

  char serial_id[SVM40_MAX_SERIAL_LEN];
  err = svm40_get_serial(serial_id);
  if (err != NO_ERROR) {
    Serial.print("Error reading SVM40 serial: ");
    Serial.println(err);

  } else {
    Serial.print("Serial Number: ");
    Serial.println(serial_id);
  }
  do {
    err = svm40_start_continuous_measurement();
    if (err) {
      Serial.print("Error starting measurement: ");
      Serial.println(err);
      delay(100);
    }
  } while(err);
}

void loop() {
  int16_t err;
  int16_t voc_index;
  int16_t relative_humidity;
  int16_t temperature_celsius;
  delay(1000); /* wait 1s */
  err = svm40_read_measured_values_as_integers(
          &voc_index, &relative_humidity, &temperature_celsius);
  if (err) {
    Serial.print("Error reading measurement values: ");
    Serial.println(err);
  } else {
    Serial.println("Measurement result");
    Serial.print(" VOC index: ");
    Serial.println(voc_index / 10.0f);
    Serial.print(" Relative Humidity: ");
    Serial.println(relative_humidity / 100.0f);
    Serial.print(" Temperature: ");
    Serial.println( temperature_celsius / 200.0f);
  }

}
