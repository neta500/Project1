#pragma once

template <class T>
class DBCommand
{
public:
	template <class... Valty>
	DBCommand(Valty&&... obj)
	{
		
	}

	bool Execute()
	{
		return true;
	}

	bool Fetch()
	{
		return false;
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
