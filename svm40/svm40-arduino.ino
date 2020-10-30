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

#include "svm40.h"

void setup() {
  int16_t err;
  Serial.begin(115200);  // start serial for output

  // wait for serial connection from PC
  // comment the following line if you'd like the output
  // without waiting for the interface being ready
  while(!Serial);

  const char* driver_version = svm40_get_driver_version();
  Serial.println(driver_version);

  
  /* Initialize I2C bus */
  sensirion_i2c_init();
  /* Try to detect sensor */
  while ((err = svm40_probe())) {
    Serial.print("SVM40 sensor probing failed: ");
    Serial.println(err);
    sensirion_sleep_usec(1000000); /* wait one second */
  }
  Serial.println("initialization successful");

  char serial_id[SVM40_MAX_SERIAL_LEN];
  err = svm40_get_serial(serial_id);
  if (err) {
      Serial.print("Error reading SVM40 serial: ");
      Serial.println(err);
  } else {
      Serial.print("Serial Number: ");
      Serial.println(serial_id);
  }

  err = svm40_start_continuous_measurement();
  if (err) {
    Serial.print("Error starting measurement: ");
    Serial.println(err);
  }
}


void loop(void) {
  int16_t err;
  int16_t voc_index;
  int16_t relative_humidity;
  int16_t temperature;
  sensirion_sleep_usec(SVM40_MEASUREMENT_INTERVAL_USEC); /* wait 1s */
  err = svm40_read_measured_values_as_integers(
      &voc_index, &relative_humidity, &temperature);

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
      Serial.println(temperature / 200.0f);
  }
}
