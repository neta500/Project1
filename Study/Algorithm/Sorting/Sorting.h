#pragma once
#include <vector>

// ������ ���Ҹ� ���Ͽ� swap. O(n^2)
void BubbleSort(std::vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int j = 1; j < vec.size() - i; ++j)
		{
			if (vec[j] < vec[j - 1])
			{
				std::swap(vec[j], vec[j - 1]);
			}
		}
	}
}

// ���� ���� ���Ҹ� �����ؼ�, ó���Ŷ� swap. O(n^2)
void SelectionSort(std::vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		int minIndex = i;

		for (int j = i; j < vec.size(); ++j)
		{
			if (vec[minIndex] > vec[j])
			{
				minIndex = j;
			}
		}

		std::swap(vec[minIndex], vec[i]);
	}
}

// index 1���� �����ؼ� ������ ��ġ�� ���� O(n) ~ O(n^2)
void InsertionSort(std::vector<int>& vec)
{
	for (int i = 1; i < vec.size(); ++i)
	{
		int temp = vec[i];
		int prevIndex = i - 1;

		// ���� ���ҵ��� �а�,
		while (prevIndex >= 0 && vec[prevIndex] > temp)
		{
			vec[prevIndex + 1] = vec[prevIndex];
			prevIndex--;
		}

		// �˸��� ��ġ�� ����
		vec[prevIndex + 1] = temp;
	}
}

int partition(std::vector<int>& vec, int left, int right)
{
	// pivot�� �߰����� ����ִ°� ����.
	int mid = (left + right) / 2;
	int pivot = vec[mid];

	// left�� pivot�� �ٲ��ص�,
	std::swap(vec[left], vec[mid]);

	int i = left; int j = right;

	// left�� right�� �����ָ鼭, left�� pivot���� ū��, right�� �������� ã�� swap
	while (i < j)
	{
		while (pivot < vec[j])
		{
			j--;
		}

		while (i < j && pivot >= vec[i])
		{
			i++;
		}

		std::swap(vec[i], vec[j]);
	}

	// ó���� �ٲ���� left�� pivot ���󺹱� (���� �ι�° while������ i�� pivot >=���� ����
	// ���ױ� ������, i�� �ٲ���� �Ѵ�. (i�� mid�� �ٸ� �� ����)	
	vec[left] = vec[i];
	vec[i] = pivot;
	return i;
}

// pivot, divide & conquer
void QuickSort(std::vector<int>& vec, int left, int right)
{
	if (left >= right)	return;

	// partition
	int pivot = partition(vec, left, right);

	// divide and conquer
	QuickSort(vec, left, pivot - 1);
	QuickSort(vec, pivot + 1, right);
}