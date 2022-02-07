#pragma once
#include <string>
#include <unordered_map>

// s = "abcd", t = "abcde" -> "e'
// t는 s보다 한글자 많음. (s를 랜덤셔플한다음, 아무자리에 한글자 넣었음)
// brute force로 생각하면, s와 t를 순회하면서 찾으면 된다. O(n^2)
// hash_map을 사용하면, O(n)으로 찾을 수 있다.
// xor를 사용하면 space complexity를 없앨 수 있다. (feat. 136_SingleNumber)
// 원소 한개 차이를 구하는 문제는 xor를 고려해보자.

class Solution {
public:
    char findTheDifference(std::string s, std::string t) {

        std::unordered_map<char, int> map;

        for (const char c : t)
        {
            map[c]++;
        }

        for (const char c : s)
        {
	        if (map.find(c) == map.end())
	        {
                return c;
	        }

            map[c]--;
        }

        for (const auto& [c, count] : map)
        {
	        if (count != 0)
	        {
                return c;
	        }
        }

        return 'a';
    }

    char findTheDifference_xor(std::string s, std::string t)
    {
        char result = 0;

        // xor를 두번하면 0이된다는걸 이용함.
        for (const char c : s)
        {
            result ^= c;
        }

        for (const char c : t)
        {
            result ^= c;
        }

        return result;
    }
};