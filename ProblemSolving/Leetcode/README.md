# 리츠코드 문제풀이

## 2020

----------------------------------

### [ 283. Move Zeroes ](https://leetcode.com/problems/k-diff-pairs-in-an-array/) - easy

- 문제

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

- 제한사항
  - You must do this in-place without making a copy of the array.
  - Minimize the total number of operations.


- 입출력 예
  - Example 1:

```
Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
```

- 풀이
  - array

```C++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int numsSize = nums.size(), count = 0;
        for(int index = 0 ; index < numsSize - count;){
            if(nums[index] == 0){
                ++count;
                nums.push_back(0);
                nums.erase(nums.begin() + index);
            }
            else
                ++index;
        }
    }
};
```

----------------------------------

### [ K-diff Pairs in an Array ](https://leetcode.com/problems/k-diff-pairs-in-an-array/) - easy

- 문제

Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array. Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k. 

- 제한사항
  - The pairs (i, j) and (j, i) count as the same pair.
  - The length of the array won't exceed 10,000.
  - All the integers in the given input belong to the range: [-1e7, 1e7].

- 입출력 예

  - Example 1:

```
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
```

  - Example 2:

```
Input:[1, 2, 3, 4, 5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
```

  - Example 3:

```
Input: [1, 3, 1, 5, 4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
```

- 풀이
  - map

```C++
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (k < 0) 
            return 0;
        
        int count = 0;
        unordered_map<int,int> m;
        
        for(const auto& i : nums)
            ++m[i];
        
        for(const auto& i : m){
          if ((!k && i.second > 1) || (k && m.count(i.first + k))) 
              ++count;
        }
            
        return count;
    }
};
```
----------------------------------
