#pragma once
#include <numeric>
#include <vector>

// #greedy
// gas = [1,2,3,4,5] cost = [3,4,5,1,2]
// gas���� �⸧�� ä�� �� �ְ�, ���� gas station�� �� �� cost��ŭ�� �⸧�� �Ҹ��Ѵ�.
// �ѹ����� �� �� ������ ����� gas station�� index��, ������ -1

// 1. brute force : �� gas station���� �ѹ����� ���鼭 �����Ѵ�. O(n^2)
// 2. greedy : � gas station���� �⸧�� �����ϸ�, �� ���� station���� ����. O(n)
//             (���� ���� �⸧�� �����ϸ�, ������ �� station���� �����ص� �⸧�� ������)

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
                // ���� 3��° station �����̸�, 3 4 5 1 2 �̷��� ���ƾ��ϴϱ�
                // size�� �����ش�. �׳� for������ j�� ������Ű�� 3 4 5 6 7 �̷��ԵǴµ�
                // size���ϰ� size�� ������� index�� 3 4 5 1 2 �̷��� ��.
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
                // �ش� gas station ������ �Ұ����ϸ�, �ٷ� �Ѿ��.
                startStation = i + 1;
                remainGas = 0;
            }
        }

        return startStation;
    }
};