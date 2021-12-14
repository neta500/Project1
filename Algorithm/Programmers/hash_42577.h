#pragma once
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;

    std::unordered_set<std::string> set;
    for (const auto& num : phone_book)
    {
        set.emplace(num);
    }

    for (const auto& num : phone_book)
    {
        for (auto i = 0; i < num.size(); ++i)
        {
            const auto subString = num.substr(0, i);
            if (const auto found = set.find(subString); found != set.cend())
            {
                answer = false;
            }
        }
    }

    return answer;
}

//��ȭ��ȣ�ο� ���� ��ȭ��ȣ ��, �� ��ȣ�� �ٸ� ��ȣ�� ���ξ��� ��찡 �ִ��� Ȯ���Ϸ� �մϴ�.
//��ȭ��ȣ�� ������ ���� ���, ������ ��ȭ��ȣ�� �������� ��ȭ��ȣ�� ���λ��Դϴ�.
//
//������ : 119
//���ؿ� : 97 674 223
//������ : 11 9552 4421
//��ȭ��ȣ�ο� ���� ��ȭ��ȣ�� ���� �迭 phone_book �� solution �Լ��� �Ű������� �־��� ��, � ��ȣ�� �ٸ� ��ȣ�� ���ξ��� ��찡 ������ false�� �׷��� ������ true�� return �ϵ��� solution �Լ��� �ۼ����ּ���.
//
//���� ����
//phone_book�� ���̴� 1 �̻� 1, 000, 000 �����Դϴ�.
//�� ��ȭ��ȣ�� ���̴� 1 �̻� 20 �����Դϴ�.
//���� ��ȭ��ȣ�� �ߺ��ؼ� ������� �ʽ��ϴ�.
//����� ����
//phone_book	return
//["119", "97674223", "1195524421"]	false
//["123", "456", "789"]	true
//["12", "123", "1235", "567", "88"]	false
//����� �� ����
//����� �� #1
//�տ��� ������ ���� �����ϴ�.
//
//����� �� #2
//�� ��ȣ�� �ٸ� ��ȣ�� ���λ��� ��찡 �����Ƿ�, ���� true�Դϴ�.
//
//����� �� #3
//ù ��° ��ȭ��ȣ, ��12���� �� ��° ��ȭ��ȣ ��123���� ���λ��Դϴ�.���� ���� false�Դϴ�.