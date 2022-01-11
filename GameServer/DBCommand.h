#pragma once
#include <DateTime.h>

template <class T>
class DBCommand
{
public:
	template <class... Valty>
	DBCommand(Valty&&... obj) {}

	bool Execute()
	{
		return true;
	}

	bool Fetch()
	{
		return true;
	}

	T* operator->()
	{
		return &mBindObj;
	}

	T mBindObj;
};

namespace SP
{
	class LoadBattlePassSeason
	{
	};

	class LoadBattlePassReward
	{
	};

	class InsertBattlePassSeason
	{
	};

	class DeleteBattlePassSeason
	{		
	};

	class UpdateBattlePassSeason
	{		
	};

	class InsertBattlePassReward
	{		
	};

	class DeleteBattlePassReward
	{		
	};

	class UpdateBattlePassReward
	{		
	};

}
