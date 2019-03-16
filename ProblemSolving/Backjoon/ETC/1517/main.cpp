/*
https://www.acmicpc.net/problem/1517


N개의 수로 이루어진 수열 A[1], A[2], …, A[N]이 있다. 이 수열에 대해서 버블 소트를 수행할 때, Swap이 총 몇 번 발생하는지 알아내는 프로그램을 작성하시오.

버블 소트는 서로 인접해 있는 두 수를 바꿔가며 정렬하는 방법이다. 예를 들어 수열이 3 2 1 이었다고 하자. 이 경우에는 인접해 있는 3, 2가 바뀌어야 하므로 2 3 1 이 된다. 다음으로는 3, 1이 바뀌어야 하므로 2 1 3 이 된다. 다음에는 2, 1이 바뀌어야 하므로 1 2 3 이 된다. 그러면 더 이상 바꿔야 할 경우가 없으므로 정렬이 완료된다.

*/
#include <iostream>
#include <vector>
#include <algorithm>

long count;

void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    std::vector<int> temp(arr.size());

    while(i <= mid && j <= right){
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else{
            temp[k++] = arr[j++];
            count += mid + 1 - i;
        }
    }

    if(i <= mid)
        for(auto m = i; m <= mid; m++)
            temp[k++] = arr[m];
    else
        for(auto m = j; m <= right; m++)
            temp[k++] = arr[m];

    for (auto m = left; m <= right; m++)
        arr[m] = temp[m];
}
void mergeSort(std::vector<int> &arr, int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main(){
    int n = 0;
    std::cin >> n;

    std::vector<int> item(n);

    for (auto i = 0; i < n; i++)
        std::cin >> item[i];

    mergeSort(item, 0, item.size() - 1);

    std::cout << count << "\n";
}
