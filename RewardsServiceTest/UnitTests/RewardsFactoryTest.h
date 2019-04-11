#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <memory>

#include "../RewardsFactory.h"
#include "../RewardEnums.h"
#include "../ChannelEnums.h"

struct RewardsFactoryTest : testing::Test
{
    std::unique_ptr<RewardsFactory> rewardsFactory;

    RewardsFactoryTest() :
        rewardsFactory(new RewardsFactory())
    {
    }

    virtual ~RewardsFactoryTest()
    {
    }
};

TEST_F(RewardsFactoryTest, championsForSport)
{
    const auto result = rewardsFactory->getRewardForChannel(Channel::SPORTS);
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(*result.begin(), Reward::CHAMPIONS_LEAGUE_FINAL_TICKET);
}

TEST_F(RewardsFactoryTest, karaokeForMusic)
{
    const auto result = rewardsFactory->getRewardForChannel(Channel::MUSIC);
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(*result.begin(), Reward::KARAOKE_PRO_MICROPHONE);
}


TEST_F(RewardsFactoryTest, piratesForMovies)
{
    const auto result = rewardsFactory->getRewardForChannel(Channel::MOVIES);
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(*result.begin(), Reward::PIRATES_OF_THE_CARIBBEAN_COLLECTION);
}

TEST_F(RewardsFactoryTest, nothingForKids)
{
    const auto result = rewardsFactory->getRewardForChannel(Channel::KIDS);
    EXPECT_EQ(0, result.size());
}

TEST_F(RewardsFactoryTest, nothingForNews)
{
    const auto result = rewardsFactory->getRewardForChannel(Channel::NEWS);
    EXPECT_EQ(0, result.size());
}
