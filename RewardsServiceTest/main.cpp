#include "RewardsFactoryTest.h"
#include "AccountTest.h"
#include "RewardsServiceTest.h"
#include "EligibilityServiceTest.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
