#include "pch.h"
#include "BattlePassSeasonManager.h"

void BattlePassSeasonManager::LoadManager()
{
	if (false == LoadSeasonData())
	{
		spdlog::error("BattlePassSeasonManager::LoadSeasonData failed");
		return;
	}

	if (false == LoadRewardData())
	{
		spdlog::error("BattlePassSeasonManager::LoadRewardData failed");
	}

	mLoadSuccess = true;
}

void BattlePassSeasonManager::StartManager()
{
	if (true == mLoadSuccess)
	{
		// OnTick
	}
}

bool BattlePassSeasonManager::IsSeasonNow() const
{
	return mCurrentSeasonData.mSeasonId > 0;
}

bool BattlePassSeasonManager::IsValidSeason(const int seasonId) const
{
	READ_LOCK;

	if (mSeasonMap.contains(seasonId))
	{
		return true;
	}

	return false;
}

bool BattlePassSeasonManager::StartBattlePassSeason(const int seasonId)
{
	return false;
}

void BattlePassSeasonManager::EndBattlePassSeason()
{
}

bool BattlePassSeasonManager::InsertSeasonData(const BattlePassSeasonData& seasonData)
{
	return false;
}

bool BattlePassSeasonManager::DeleteSeasonData(const int seasonId)
{
	return false;
}

bool BattlePassSeasonManager::UpdateSeasonData(const int prevSeasonId, const BattlePassSeasonData& seasonData)
{
	return false;
}

bool BattlePassSeasonManager::InsertRewardData(const BattlePassRewardData& rewardData)
{
	return false;
}

bool BattlePassSeasonManager::DeleteRewardData(const std::wstring& rewardId)
{
	return false;
}

bool BattlePassSeasonManager::UpdateRewardData(const BattlePassRewardData& rewardData)
{
	return false;
}

OptionalRef<BattlePassSeasonData> BattlePassSeasonManager::GetSeasonData(const int seasonId) const
{
	return OptionalRef<BattlePassSeasonData>();
}

void BattlePassSeasonManager::OnTick()
{
	if (IsSeasonNow())
	{
		if (true == CheckSeasonEnd())
		{
			EndBattlePassSeason();
		}
	}
	else
	{
		if (const auto startableSeasonId = GetStartableSeasonId(DateTime::UtcNow());
			startableSeasonId.has_value())
		{
			StartBattlePassSeason(startableSeasonId.value());
		}
	}

	// DoTimer OnTick
}

bool BattlePassSeasonManager::LoadSeasonData()
{
	return false;
}

bool BattlePassSeasonManager::LoadRewardData()
{
	return false;
}

bool BattlePassSeasonManager::CheckSeasonEnd()
{
	return false;
}

OptionalRef<int> BattlePassSeasonManager::GetStartableSeasonId(const DateTime& currentTime) const
{
	return OptionalRef<int>();
}
