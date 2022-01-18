#pragma once
#include "TreeNode.h"

// 두 리스트의 합 구하기
// [2,4,3], [5,6,4] -> [7,0,8]

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode preHead(0);
        ListNode* ptr = &preHead;
        int extra = 0;

        // l1, l2의 원소가 남아있거나, extra가 0보다 큰 경우
        while (l1 || l2 || extra)
        {
	        if (l1)
	        {
                extra += l1->val;
                l1 = l1->next;
	        }

            if (l2)
            {
                extra += l2->val;
                l2 = l2->next;
            }

            // 다음 원소에 extra를 10으로 나눈 나머지를 세팅해주고, extra는 10으로 나눈다.
            // l1, l2가 2, 5였으면 ptr->next는 7로 세팅, extra는 0이되고
            // l1, l2가 4, 6이었으면 ptr->next는 0으로 세팅, extra는 1이되어서 다음 while
            // 문에서 더해서 계산됨.
            ptr->next = new ListNode(extra % 10);
            extra /= 10;
            ptr = ptr->next;
        }

        return preHead.next;
    }
};