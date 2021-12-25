#pragma once
#include <vector>
#include <stack>
#include <unordered_set>
#include <queue>

class Solution {
public:
    std::unordered_set<int> visited;
    std::unordered_set<int> keys;

    void dfs(std::vector<std::vector<int>>& rooms, int depth)
    {
        visited.emplace(depth);

        for (const int key : rooms[depth])
        {
            keys.emplace(key);
        }

        for (const int key : keys)
        {
            if (false == visited.contains(key))
            {
                dfs(rooms, key);
            }
        }
    }

    bool canVisitAllRooms_dfs(std::vector<std::vector<int>>& rooms) {       

        dfs(rooms, 0);
        return visited.size() == rooms.size();
    }

    bool canVisitAllRooms_bfs(std::vector<std::vector<int>>& rooms) {
        std::queue<int> queue; // queue에는 입장해야할 방번호를 넣는다.
        // 0번방 입성
        visited.emplace(0);
        queue.emplace(0);

        while (false == queue.empty())
        {
            int roomNumber = queue.front(); queue.pop();
            for (const int key : rooms[roomNumber])
            {
                if (visited.contains(key))
                {
                    continue;
                }

                visited.emplace(key);
                queue.push(key); // 중복체크 안할 방법?
            }
        }

        return visited.size() == rooms.size();
    }
};

// rooms를 순회하며 열쇠 획득 후 다음 room을 들어갈 수 있는 지 체크.
// 모든 방을 들어갈 수 있으면 true, 아니면 false
// 0번방은 항상 열려있다. (0번방의 key는 다 획득 가능)

// 예제 [[1,3], [3,0,1], [2], [0]] -> false
// BFS
// queue(0), visited(0)
// 0번방 - key(1,3) 획득, queue(1, 3), visited(0)
// 1번방 - key(3,0,1) 획득, queue(3, 3, 0, 1), visited(0, 1)
// 3번방 - key(0) 획득, queue(3, 0, 1, 0), visited(0, 1, 3)
// 3번방 - visited이므로 패스
// 0번방, 1번방, 0번방 - visited이므로 패스
// queue가 비었으므로 결과 체크


// DFS
// 0번방 - key(1,3) 획득, 1, 3번방 순회
// 0번방 - 가지고 있는 key를 순회하며 방 체크 (1, 3)
// 0번방 -> 1번방 - key(3,0,1) 획득, 0, 1, 3번방 순회
// 0번방 -> 1번방 -> 0번방 - visited이므로 탐색 끝
// 0번방 -> 1번방 -> 1번방 - visited이므로 탐색 끝
// 0번방 -> 1번방 -> 3번방 - key 획득, 0번방 순회
// 0번방 -> 1번방 -> 3번방 - 0번방 - visited이므로 탐색 끝
// 0번방 -> 3번방 - key(0) 획득, 0번방 순회
// 0번방 -> 3번방 -> 0번방 - visited이므로 탐색 끝
// 모든 탐색 끝, visited와 rooms를 비교. 2번방에 못들어갔기 때문에 false