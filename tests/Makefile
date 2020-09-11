include ../embedded-common/test-config/base_config.inc
svm40_driver_dir := ${driver_dir}/embedded-svm40
include ${svm40_driver_dir}/svm40/default_config.inc

svm40_test_binaries := svm40-test-hw_i2c svm40-test-sw_i2c

.PHONY: all clean prepare test

all: clean prepare test

prepare:
	cd ${svm40_driver_dir} && $(MAKE) prepare

svm40-test-hw_i2c: svm40-test.cpp ${hw_i2c_sources} ${sensirion_test_sources}
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

svm40-test-sw_i2c: CONFIG_I2C_TYPE := sw_i2c
svm40-test-sw_i2c: svm40-test.cpp ${sw_i2c_sources} ${sensirion_test_sources}
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) ${svm40_test_binaries}

test: prepare ${svm40_test_binaries}
	set -ex; for test in ${svm40_test_binaries}; do echo $${test}; ./$${test}; echo; done;
