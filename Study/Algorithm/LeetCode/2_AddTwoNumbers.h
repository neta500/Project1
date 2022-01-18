#pragma once
#include "TreeNode.h"

// �� ����Ʈ�� �� ���ϱ�
// [2,4,3], [5,6,4] -> [7,0,8]

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode preHead(0);
        ListNode* ptr = &preHead;
        int extra = 0;

        // l1, l2�� ���Ұ� �����ְų�, extra�� 0���� ū ���
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

            // ���� ���ҿ� extra�� 10���� ���� �������� �������ְ�, extra�� 10���� ������.
            // l1, l2�� 2, 5������ ptr->next�� 7�� ����, extra�� 0�̵ǰ�
            // l1, l2�� 4, 6�̾����� ptr->next�� 0���� ����, extra�� 1�̵Ǿ ���� while
            // ������ ���ؼ� ����.
            ptr->next = new ListNode(extra % 10);
            extra /= 10;
            ptr = ptr->next;
        }

        return preHead.next;
    }
};