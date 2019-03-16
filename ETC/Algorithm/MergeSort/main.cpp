#include <iostream>
#include <vector>
#include <algorithm>

void merge(std::vector<int> &arr, int left, int mid, int right)
{
	int i = left, j = mid + 1, k = left;
	std::vector<int> temp(arr.size());

	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j])
		{
			temp[k] = arr[i];
			i++;
		}
		else
		{
			temp[k] = arr[j];
			j++;
		}
		k++;
	}

	if (i <= mid)
	{
		for (auto m = i; m <= mid; m++)
		{
			temp[k] = arr[m];
			k++;
		}
	}
	else
	{
		for (auto m = j; m <= right; m++)
		{
			temp[k] = arr[m];
			k++;
		}
	}

	for (auto m = left; m <= right; m++)
		arr[m] = temp[m];
}
void mergeSort(std::vector<int> &arr, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

int main()
{
	int n = 0;
	std::cin >> n;

	std::vector<int> item(n);

	for (auto i = 0; i < n; i++)
		std::cin >> item[i];

	mergeSort(item, 0, item.size() - 1);

	for (auto i = 0; i < n; i++)
		std::cout << item[i] << "\n";
}
