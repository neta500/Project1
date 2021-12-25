#pragma once
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<int> numbers) {
    string answer = "";

    std::sort(numbers.begin(), numbers.end(), [](const int a, const int b)
        {
            const auto strA = std::to_string(a);
            const auto strB = std::to_string(b);

            return strA + strB > strB + strA;
        }
    );

    for (const auto& num : numbers)
    {
        answer.append(std::to_string(num));
    }

    bool zeroString = true;
    for (const auto& ch : answer)
    {
        if (ch != '0')
        {
            zeroString = false;
        }
    }
    
    if (zeroString)
    {
        answer = "0";
    }

    return answer;
}