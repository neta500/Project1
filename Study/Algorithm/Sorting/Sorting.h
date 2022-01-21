#pragma once
#include <vector>

// 인접한 원소를 비교하여 swap. O(n^2)
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

// 가장 작은 원소를 선택해서, 처음거랑 swap. O(n^2)
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

// index 1부터 시작해서 적절한 위치에 삽입 O(n) ~ O(n^2)
void InsertionSort(std::vector<int>& vec)
{
	for (int i = 1; i < vec.size(); ++i)
	{
		int temp = vec[i];
		int prevIndex = i - 1;

		// 앞의 원소들을 밀고,
		while (prevIndex >= 0 && vec[prevIndex] > temp)
		{
			vec[prevIndex + 1] = vec[prevIndex];
			prevIndex--;
		}

		// 알맞은 위치에 삽입
		vec[prevIndex + 1] = temp;
	}
}

int partition(std::vector<int>& vec, int left, int right)
{
	// pivot은 중간으로 잡아주는게 좋다.
	int mid = (left + right) / 2;
	// left와 pivot을 바꿔준뒤,
	std::swap(vec[left], vec[mid]);

	int pivot = vec[left];
	int i = left; int j = right;

	// left와 right를 좁혀주면서, left는 pivot보다 큰값, right는 작은값을 찾아 swap
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