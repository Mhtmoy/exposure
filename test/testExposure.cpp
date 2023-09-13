#include <gtest/gtest.h>
#include <../include/Exposure.h>
TEST(TestExposure, gtestExample_ExposureValueMethod) {
Exposure e;
EXPECT_EQ(-3, e.exposureValue(1, 1, 800));
EXPECT_NEAR(e.exposureValue(2, 1, 100), 2, 0.01);
EXPECT_NEAR(e.exposureValue(4, 0.125, 100), 7, 0.01);
EXPECT_NEAR(e.exposureValue(64, 0.125, 100), 15, 0.01);
}
TEST(TestExposure, gtestEXample_exposureFunction) {
Exposure e;
EXPECT_EQ(0, e.exposure(NIGHT, e.exposureValue(1, 1, 800)));
EXPECT_EQ(0, e.exposure(DIM_LIGHT, e.exposureValue(2, 1, 100)));
EXPECT_EQ(0, e.exposure(MEDIUM_LIGHT, e.exposureValue(4, 0.125, 100)));
EXPECT_EQ(0, e.exposure(BRIGHT_LIGHT, e.exposureValue(64, 0.125, 100)));
EXPECT_EQ(-1, e.exposure(BRIGHT_LIGHT, e.exposureValue(2, 0.125, 100)));
}
TEST(TestExposure, gtestEXample_BoundaryValueAnalysis) {
Exposure e;
EXPECT_LT(e.exposure(NIGHT, -1.0), 0);
EXPECT_EQ(e.exposure(NIGHT, -1.1), 0);
EXPECT_LT(e.exposure(DIM_LIGHT, 6.0), 0);
EXPECT_EQ(e.exposure(DIM_LIGHT, -1.0), 0);
//EXPECT_GT(e.exposure(DIM_LIGHT, -1.1), 0);
EXPECT_LT(e.exposure(MEDIUM_LIGHT, 12.0), 0);
EXPECT_EQ(e.exposure(MEDIUM_LIGHT, 6.0), 0);
//EXPECT_GT(e.exposure(MEDIUM_LIGHT, 5.9), 0);
//EXPECT_GT(e.exposure(BRIGHT_LIGHT, 11.0), 0);
EXPECT_EQ(e.exposure(BRIGHT_LIGHT, 12.0), 0);
}
