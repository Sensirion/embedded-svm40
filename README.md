# embedded-svm40 [![CircleCI](https://circleci.com/gh/Sensirion/embedded-svm40.svg?style=shield)](https://circleci.com/gh/Sensirion/embedded-svm40) [![GitHub license](https://img.shields.io/badge/license-BSD3-blue.svg)](https://raw.githubusercontent.com/Sensirion/embedded-svm40/master/LICENSE)

Embedded I2C driver for the Sensirion SVM40 module which measures humidity,
temperature and VOC in the air.

Compared to the SVM30 (which is included in the
https://github.com/Sensirion/embedded-sgp repository), the SVM40 combines
multiple sensors with a separate micro controller and is thus quite different
to use. For that reason the SVM40 driver lives in this separate repository.

## Download the Latest Driver Release

**Download the latest ready-to-use driver bundle from the [releases
page](https://github.com/Sensirion/embedded-svm40/releases/)**

We strongly recommend to use the driver from the release bundle instead of
cloning the repository.

## Clone this repository
```
 git clone --recursive https://github.com/Sensirion/embedded-svm40.git
```

## Repository content
* `embedded-common` submodule repository for the common embedded driver HAL
* `svm40` SVM40 driver

## Collecting resources
```
make release
```
This will create the `release` folder with the necessary driver files in it,
including a Makefile. That way, you have just ONE folder with all the sources
ready to build your driver for your platform.

## Files to adjust (from embedded-common)
You only need to touch the following files:

* `sensirion_arch_config.h` (architecture specifics, you need to specify
  the integer sizes)

and depending on your i2c implementation either of the following:

* `embedded-common/hw_i2c/sensirion_hw_i2c_implementation.c`
  functions for hardware i2c communication if your platform supports that
* `embedded-common/sw_i2c/sensirion_sw_i2c_implementation.c`
  functions for software i2c communication via GPIOs

## Building the driver
1. Adjust `sensirion_arch_config.h` if you don't have the `<stdint.h>` header
   file available
2. Implement necessary functions in one of the `*_implementation.c` files
   described above
3. make

---

Please check the [embedded-common](https://github.com/Sensirion/embedded-common)
repository for further information and sample implementations.

---

## Other Resources

 * https://www.sensirion.com/en/environmental-sensors/gas-sensors/sgp40/ for
   more information about SGP40 and the SVM40 evaluation module
 * https://pypi.org/project/sensirion-shdlc-svm40/ for a Python driver for the
   SVM40 module.
