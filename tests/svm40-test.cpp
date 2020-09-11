#include "sensirion_i2c.h"
#include "sensirion_test_setup.h"

TEST_GROUP(SVM40){void setup(){sensirion_i2c_init();
}

void teardown() {
    sensirion_i2c_release();
}
}
;

TEST(SVM40, dummy) {
}
