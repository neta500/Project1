#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

string solutionvector<string> participant, vector<string> completion) {
    string answer = "";
    std::unordered_map<std::string, int> map;
    for (const auto& name : participant)
    {
        if (const auto& found = map.find(name); found != map.cend())
        {
            map[name]++;
        }
        else
        {
            map.emplace(name, 1);
        }
    }

    for (const auto& name : completion)
    {
        if (const auto& found = map.find(name); found != map.cend())
        {
            map[name]--;
        }
    }

    for (const auto& [name, count] : map)
    {
        if (count > 0)
        {
            answer = name;
        }
    }

    return answer;
}

//���� ����
//������ ������ �������� �����濡 �����Ͽ����ϴ�.�� �� ���� ������ �����ϰ�� ��� ������ �������� �����Ͽ����ϴ�.
//
//�����濡 ������ �������� �̸��� ��� �迭 participant�� ������ �������� �̸��� ��� �迭 completion�� �־��� ��, �������� ���� ������ �̸��� return �ϵ��� solution �Լ��� �ۼ����ּ���.
//
//���ѻ���
//������ ��⿡ ������ ������ ���� 1�� �̻� 100, 000�� �����Դϴ�.
//completion�� ���̴� participant�� ���̺��� 1 �۽��ϴ�.
//�������� �̸��� 1�� �̻� 20�� ������ ���ĺ� �ҹ��ڷ� �̷���� �ֽ��ϴ�.
//������ �߿��� ���������� ���� �� �ֽ��ϴ�.
//����� ��
//participant	completion	return
//["leo", "kiki", "eden"]["eden", "kiki"]	"leo"
//["marina", "josipa", "nikola", "vinko", "filipa"]["josipa", "filipa", "marina", "nikola"]	"vinko"
//["mislav", "stanko", "mislav", "ana"]["stanko", "ana", "mislav"]	"mislav"
//����� �� ����
//���� #1
//"leo"�� ������ ��ܿ��� ������, ������ ��ܿ��� ���� ������ �������� ���߽��ϴ�.
//
//���� #2
//"vinko"�� ������ ��ܿ��� ������, ������ ��ܿ��� ���� ������ �������� ���߽��ϴ�.
//
//���� #3
//"mislav"�� ������ ��ܿ��� �� ���� ������, ������ ��ܿ��� �� ��ۿ� ���� ������ �Ѹ��� �������� ���߽��ϴ�.