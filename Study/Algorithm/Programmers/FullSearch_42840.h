#pragma once
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;

    std::vector<int> person1 = { 1,2,3,4,5 };
    std::vector<int> person2 = { 2,1,2,3,2,4,2,5 };
    std::vector<int> person3 = { 3,3,1,1,2,2,4,4,5,5 };

    int correct1 = 0;
    int correct2 = 0;
    int correct3 = 0;
    
    for (auto i = 0; i < answers.size(); ++i)
    {
        if (answers[i] == person1[i % person1.size()])
        {
            correct1++;
        }
        if (answers[i] == person2[i % person2.size()])
        {
            correct2++;
        }
        if (answers[i] == person3[i % person3.size()])
        {
            correct3++;
        }
    }

    const auto max = std::max({ correct1, correct2, correct3 });
    if (correct1 == max) answer.push_back(1);
    if (correct2 == max) answer.push_back(2);
    if (correct3 == max) answer.push_back(3);

    return answer;
}