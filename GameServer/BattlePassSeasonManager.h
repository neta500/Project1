#pragma once
#include "BattlePassData.h"
#include <SpinLock.h>
#include <Timer.h>

class BattlePassSeasonManager : public Timer
{
	static constexpr int TickInterval = 1000;
public:
	BattlePassSeasonManager() = default;
	~BattlePassSeasonManager() = default;

	void LoadManager();
	void StartManager();

	bool IsSeasonNow() const;
	bool IsValidSeason(const int seasonId) const;

	const BattlePassSeasonData& GetCurrentSeasonData() const { return mCurrentSeasonData; }
		
	bool InsertSeasonData(const BattlePassSeasonData& seasonData);
	bool DeleteSeasonData(const int seasonId);
	bool UpdateSeasonData(const int prevSeasonId, const BattlePassSeasonData& seasonData);

	bool InsertRewardData(const BattlePassRewardData& rewardData);
	bool DeleteRewardData(const std::wstring& rewardId);
	bool UpdateRewardData(const BattlePassRewardData& rewardData);

	OptionalRef<const BattlePassSeasonData> GetSeasonData(const int seasonId) const;

private:
	void OnTick();
	bool LoadSeasonData();
	bool LoadRewardData();
	
	bool CheckSeasonEnd();
	std::optional<int> GetStartableSeasonId(const DateTime& currentTime) const;

	void SetSeasonData(const BattlePassSeasonData& seasonData) { mCurrentSeasonData = seasonData; }

	bool StartBattlePassSeason(const int seasonId);
	void EndBattlePassSeason();
	
private:
	USE_LOCK;

	bool mLoadSuccess = false;
	BattlePassSeasonData mCurrentSeasonData;

	std::unordered_map<int, BattlePassSeasonData> mSeasonMap;
	std::unordered_map<std::wstring, BattlePassRewardData> mRewardMap;
};
