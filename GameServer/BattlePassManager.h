#pragma once
#include "BattlePassData.h"

class User;

class BattlePassManager
{
public:
	explicit BattlePassManager(User* user);
	~BattlePassManager() = default;


private:
	User* mUser;
	BattlePassAccountData mBattlePassData;
};