# 리츠코드 문제풀이

## 2020

----------------------------------

### [ 1277. Count Square Submatrices with All Ones ](https://leetcode.com/problems/count-square-submatrices-with-all-ones/) - medium

- 문제

Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

- 제한사항
  - 1 <= arr.length <= 300
  - 1 <= arr[0].length <= 300
  - 0 <= arr[i][j] <= 1

- 입출력 예
  
```
Example 1:

Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation: 
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.

Example 2:

Input: matrix = 
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation: 
There are 6 squares of side 1.  
There is 1 square of side 2. 
Total number of squares = 6 + 1 = 7.

```

- 풀이
  - DP

```C++
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int count = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> result = vector<vector<int>>(m, vector<int>(n, 0));
        
        for(auto i = 0 ; i < m ; ++i){
            for(auto j = 0 ; j < n ; ++j){
                // 가로, 세로 첫줄은 그대로 저장
                if(i == 0 || j == 0){
                    result[i][j] = matrix[i][j];
                }
                // 0인 값은 그대로 0을 저장
                else if(matrix[i][j] == 0){
                    result[i][j] = 0;
                }
                // 현재 index의 왼쪽, 위, 왼쪽 위 대각선, 이 세가지 값을 비교후 작은 값에 +1
                // +1 하느 이유는 크기가 1인 사각형을 포함해야 하므로
                else{
                    auto temp = min(matrix[i][j-1], result[i-1][j-1]);
                    result[i][j] = min(result[i-1][j], min(result[i][j-1], result[i-1][j-1])) + 1;
                }
                
                count += result[i][j];
            }
        }
        
        return count;
    }
};
```

----------------------------------

### [ 746. Min Cost Climbing Stairs ](https://leetcode.com/problems/min-cost-climbing-stairs/submissions/) - easy

- 문제

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

- 제한사항
  - cost will have a length in the range [2, 1000].
  - Every cost[i] will be an integer in the range [0, 999]

- 입출력 예
  
```
Example 1:

Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.

Example 2:

Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].

```

- 풀이
  - DP

```C++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> result(cost.size(), 0);
        int len = cost.size();
        
        result[0] = cost[0];
        result[1] = cost[1];
        
        for(auto i = 2 ; i < len ; ++i){
            result[i] = min(cost[i] + result[i-1], cost[i] + result[i-2]);
        }
        
        return result[len-1] < result[len-2] ? result[len-1] : result[len-2];
    }
};
```

----------------------------------

### [ 303. Range Sum Query - Immutable ](https://leetcode.com/problems/range-sum-query-immutable/) - easy

- 문제

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

- 제한사항
  - You may assume that the array does not change.
  - There are many calls to sumRange function.

- 입출력 예
  
```
Example 1:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
```

- 풀이
  - sum

```C++
class NumArray {
private:
    const vector<int>& m_nums;
public:
    NumArray(vector<int>& nums) : m_nums(nums){}
    
    int sumRange(int i, int j) {
        int sum = 0;
        
        for(auto index = i ; index <= j ; ++index){
            sum += m_nums[index];
        }
        
        return sum;
    }
};
```
----------------------------------

### [ 290. Word Pattern ](https://leetcode.com/problems/word-pattern/) - easy

- 문제

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

- 제한사항
  - You may assume pattern contains only lowercase letters, and str contains lowercase letters that may be separated by a single space


- 입출력 예
  
```
Example 1:
Input: pattern = "abba", str = "dog cat cat dog"
Output: true
```
```
Example 2:
Input:pattern = "abba", str = "dog cat cat fish"
Output: false
```
```
Example 3:
Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false
```
```
Example 4:
Input: pattern = "abba", str = "dog dog dog dog"
Output: false
```

- 풀이
  - hash

```C++
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        vector<string> strVec;
        string token;
        stringstream ss(str);
        
        while (getline(ss, token, ' ')) {
		    strVec.push_back(token);
	    }
        
        map<char, string> m;
        set<string> s;
        
        if(pattern.size() != strVec.size())
            return false;
        
        for(auto i = 0 ; i < pattern.size() ; ++i){
            if(m.find(pattern[i]) != m.end()){
                if(m[pattern[i]] != strVec[i])
                    return false;
            }
            else{
                m[pattern[i]] = strVec[i];
                s.insert(m[pattern[i]]);
            }
        }
        
        if(s.size() == m.size())
            return true;
        else
            return false;
    }
};
```

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
```
Example 1:
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
```
```
Example 2:
Input:[1, 2, 3, 4, 5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
```
```
Example 3:
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
