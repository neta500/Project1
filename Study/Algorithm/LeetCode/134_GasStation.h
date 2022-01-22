#pragma once
#include <numeric>
#include <vector>

// #greedy
// gas = [1,2,3,4,5] cost = [3,4,5,1,2]
// gas에서 기름을 채울 수 있고, 다음 gas station에 갈 때 cost만큼의 기름을 소모한다.
// 한바퀴를 돌 수 있으면 출발한 gas station의 index를, 못돌면 -1

// 1. brute force : 각 gas station마다 한바퀴씩 돌면서 검증한다. O(n^2)
// 2. greedy : 어떤 gas station에서 기름이 부족하면, 그 다음 station부터 검증. O(n)
//             (진행 도중 기름이 부족하면, 어차피 그 station에서 시작해도 기름이 부족함)

class Solution {
public:
    // 1. brute force
    int canCompleteCircuit_bruteforce(std::vector<int>& gas, std::vector<int>& cost) {

        int size = gas.size();

        for (int i = 0; i < size; ++i)
        {
			int remainGas = 0;
            bool success = true;

            for (int j = i; j < size + i; ++j)
            {
                // 만약 3번째 station 시작이면, 3 4 5 1 2 이렇게 돌아야하니까
                // size로 나눠준다. 그냥 for문으로 j를 증가시키면 3 4 5 6 7 이렇게되는데
                // size더하고 size로 나눠줘야 index가 3 4 5 1 2 이렇게 됨.
                int stationIndex = (j + size) % size;
                remainGas += gas[stationIndex] - cost[stationIndex];

                if (remainGas < 0)
                {
                    success = false;
                    break;
                }
            }

            if (success)
            {
                return i;
            }
        }

        return -1;
    }

    // 2. greedy
    int canCompleteCircuit_greedy(std::vector<int>& gas, std::vector<int>& cost) {
        int remainGas = 0;
        const int totalCost = std::accumulate(cost.begin(), cost.end(), 0);
        const int totalGas = std::accumulate(gas.begin(), gas.end(), 0);

        if (totalCost > totalGas)
        {
            return -1;
        }

        int startStation = 0;

        for (int i = 0; i < gas.size(); ++i)
        {
            remainGas += gas[i] - cost[i];

            if (remainGas < 0)
            {
                // 해당 gas station 시작이 불가능하면, 바로 넘어간다.
                startStation = i + 1;
                remainGas = 0;
            }
        }

        return startStation;
    }
};