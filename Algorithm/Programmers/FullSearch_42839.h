#pragma once
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// "1234"
int solution(string numbers) {
    int answer = 0;

    std::vector<int> splited;

    for (auto i = 0; i < numbers.size(); ++i)
    {
        splited.emplace_back(std::stoi(std::string{ numbers[i] }));
    }

    // splited <1 2 3 4>
    
    std::vector<int> vec;

    do
    {
        std::string str{};

        for (const int elem : splited)
        {
            str.append(std::to_string(elem));
        }

        if (str.front() == '0')
        {
            str = str.substr(1, str.size());
        }

        vec.emplace_back(std::stoi(str));
        
    } while (std::next_permutation(splited.begin(), splited.end()));

    return answer;
}