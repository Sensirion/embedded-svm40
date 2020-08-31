# See user_config.inc for build customization
-include user_config.inc
include default_config.inc


.PHONY: all clean

all: svm40_example_usage

svm40_example_usage: clean
	$(CC) $(CFLAGS) -o $@ ${svm40_sources} ${${CONFIG_I2C_TYPE}_sources} ${svm40_dir}/svm40_example_usage.c

clean:
	$(RM) svm40_example_usage
