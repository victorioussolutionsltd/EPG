#pragma once
#include <memory>
#include <set>

class AbstractAccount;
class AbstractEligibilityService;

enum class Reward;

class RewardsService
{
public:
    RewardsService(std::shared_ptr<AbstractEligibilityService> eligibilityService);
    virtual ~RewardsService();

    void connect();

    void setAccount(const std::shared_ptr<AbstractAccount> account);

    std::set<Reward> getRewards() const;

    std::string getLastStatus() const;

private:
    struct Private;
    std::unique_ptr<Private> d;
};
