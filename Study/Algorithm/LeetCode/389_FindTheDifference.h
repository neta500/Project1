#pragma once
#include <string>
#include <unordered_map>

// s = "abcd", t = "abcde" -> "e'
// t�� s���� �ѱ��� ����. (s�� ���������Ѵ���, �ƹ��ڸ��� �ѱ��� �־���)
// brute force�� �����ϸ�, s�� t�� ��ȸ�ϸ鼭 ã���� �ȴ�. O(n^2)
// hash_map�� ����ϸ�, O(n)���� ã�� �� �ִ�.
// xor�� ����ϸ� space complexity�� ���� �� �ִ�. (feat. 136_SingleNumber)
// ���� �Ѱ� ���̸� ���ϴ� ������ xor�� ����غ���.

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

        // xor�� �ι��ϸ� 0�̵ȴٴ°� �̿���.
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