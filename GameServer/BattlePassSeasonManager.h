#pragma once
#include "BattlePassData.h"
#include <SpinLock.h>

class BattlePassSeasonManager
{
public:
	static BattlePassSeasonManager& Get()
	{
		static BattlePassSeasonManager instance;
		return instance;
	}

	void LoadManager();
	void StartManager();

	bool IsSeasonNow() const;
	bool IsValidSeason(const int seasonId) const;

	const BattlePassSeasonData& GetCurrentSeasonData() const { return mCurrentSeasonData; }

	bool StartBattlePassSeason(const int seasonId);
	void EndBattlePassSeason();

	bool InsertSeasonData(const BattlePassSeasonData& seasonData);
	bool DeleteSeasonData(const int seasonId);
	bool UpdateSeasonData(const int prevSeasonId, const BattlePassSeasonData& seasonData);

	bool InsertRewardData(const BattlePassRewardData& rewardData);
	bool DeleteRewardData(const std::wstring& rewardId);
	bool UpdateRewardData(const BattlePassRewardData& rewardData);

	OptionalRef<BattlePassSeasonData> GetSeasonData(const int seasonId) const;

private:
	BattlePassSeasonManager() = default;
	~BattlePassSeasonManager() = default;

	void OnTick();
	bool LoadSeasonData();
	bool LoadRewardData();

	bool CheckSeasonEnd();
	OptionalRef<BattlePassSeasonData> GetStartableSeasonData(const DateTime& currentTime) const;

	void SetSeasonData(const BattlePassSeasonData& seasonData) { mCurrentSeasonData = seasonData; }

private:
	USE_LOCK;

	bool mLoadSuccess = false;
	BattlePassSeasonData mCurrentSeasonData;

	std::unordered_map<int, BattlePassSeasonData> mSeasonMap;
	std::unordered_map<std::wstring, BattlePassRewardData> mRewardMap;
};