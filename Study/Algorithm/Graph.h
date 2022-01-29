#pragma once
#include <vector>
#include <queue>
#include <spdlog/spdlog.h>

namespace graph
{
	// sample graph
	std::vector<std::vector<int>> adjcentList =
	{ {1,2,7}, {6}, {3,4}, {2}, {2}, {6}, {1,5}, {0} };
	std::vector<bool> visited(adjcentList.size(), false);

	// DFS (���� �켱 Ž��) - ����Լ��� ����. #greedy
	void dfs(int here)
	{
		if (visited[here])
		{
			return;
		}

		visited[here] = true;
		spdlog::info("dfs: {}", here);

		// ���� ��忡 ���� dfs�� ��������� �����Ѵ�.
		for (const int there : adjcentList[here])
		{
			if (false == visited[there])
			{
				dfs(there);
			}
		}
	}

	// BFS (�ʺ� �켱 Ž��) - queue�� ����. #��ã��
	void bfs()
	{
		std::queue<int> queue;
		queue.push(0);

		while (false == queue.empty())
		{
			int here = queue.front();
			queue.pop();

			if (visited[here])
			{
				continue;
			}

			visited[here] = true;
			spdlog::info("bfs: {}", here);

			// ���� ������ queue�� ����ִ´�.
			for (const int next : adjcentList[here])
			{
				queue.push(next);
			}
		}
	}

	// ���ͽ�Ʈ�� �˰��� O(ElogV)
	using VertexInfo = std::pair<int, int>; // ����, ���(�Ÿ�)
	std::vector<std::vector<VertexInfo>> vertexVec
	{
		/*0*/ {{1,5}, {2,3}, {3,7}},
		/*1*/ {{0,5}, {2,4}, {4,7}},
		/*2*/ {{0,3}, {1,4}, {3,3}, {4,8}},
		/*3*/ {{0,7}, {2,3}, {4,4}},
		/*4*/ {{1,7}, {2,8}, {3,4}}
	};
	std::vector<int> costVec(vertexVec.size(), INT_MAX);

	class Compare
	{
	public:
		// �Ÿ��� ª�� ������� ť���� �������Ѵ�.
		bool operator()(const VertexInfo& left, const VertexInfo& right) const
		{
			return left.second > right.second;
		}
	};	

	void dijkstra()
	{
		costVec[0] = 0;
		std::priority_queue<VertexInfo, std::vector<VertexInfo>, Compare> queue;
		queue.push({ 0, 0 });

		while (false == queue.empty())
		{
			const VertexInfo here = queue.top();
			const int vertex = here.first;
			const int cost = here.second;
			queue.pop();

			if (costVec[vertex] < cost)
			{
				continue;
			}

			// ���� ������ �˻��Ѵ�.
			for (const auto& [nextVertex, nextCost] : vertexVec[vertex])
			{
				// ���� ��� ������ �Ÿ��� ����ؼ�, costVec�� ���Ѵ�.
				const int totalCost = cost + nextCost;
				if (totalCost < costVec[nextVertex])
				{
					costVec[nextVertex] = totalCost;
					queue.push({ nextVertex, totalCost });
				}
			}
		}

		// print
		for (int i = 1; i < costVec.size(); ++i)
		{
			spdlog::info("dijkstra cost 0 -> {} : {}", i, costVec[i]);
		}
	}
}
