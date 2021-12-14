#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;

    //commands.emplace_back(std::vector{ 2,5,3 });
    //commands.emplace_back(std::vector{ 2,5,3 });

    for (const auto& vec : commands)
    {
        const auto startIndex = vec[0];
        const auto endIndex = vec[1];
        const auto targetIndex = vec[2];

        std::vector<int> target;
        for (auto i = 0; i < array.size(); ++i)
        {
            if (i >= startIndex - 1 && i <= endIndex - 1)
            {
                target.emplace_back(array[i]);
            }
        }

        std::sort(target.begin(), target.end());

        answer.emplace_back(target[targetIndex-1]);
    }

    return answer;
}