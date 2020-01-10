# HackerRank 문제풀이

## 2020

### [ Apple and Orange ](https://www.hackerrank.com/challenges/apple-and-orange/problem?isFullScreen=true) - easy

- 문제

Sam's house has an apple tree and an orange tree that yield an abundance of fruit. In the diagram below, the red region denotes his house, where is the start point, and is the endpoint. The apple tree is to the left of his house, and the orange tree is to its right. You can assume the trees are located on a single point, where the apple tree is at point , and the orange tree is at point .

![example](https://s3.amazonaws.com/hr-challenge-images/25220/1474218925-f2a791d52c-Appleandorange2.png)

When a fruit falls from its tree, it lands
units of distance from its tree of origin along the -axis. A negative value of means the fruit fell units to the tree's left, and a positive value of means it falls

units to the tree's right.

Given the value of
for apples and oranges, determine how many apples and oranges will fall on Sam's house (i.e., in the inclusive range

)?

For example, Sam's house is between
and . The apple tree is located at and the orange at . There are apples and oranges. Apples are thrown units distance from , and units distance. Adding each apple distance to the position of the tree, they land at . Oranges land at . One apple and two oranges land in the inclusive range

so we print

```
1
2
```

- Function Description

Complete the countApplesAndOranges function in the editor below. It should print the number of apples and oranges that land on Sam's house, each on a separate line.

countApplesAndOranges has the following parameter(s):

```
    s: integer, starting point of Sam's house location.
    t: integer, ending location of Sam's house location.
    a: integer, location of the Apple tree.
    b: integer, location of the Orange tree.
    apples: integer array, distances at which each apple falls from the tree.
    oranges: integer array, distances at which each orange falls from the tree.
```

- Input Format

```
The first line contains two space-separated integers denoting the respective values of
and .
The second line contains two space-separated integers denoting the respective values of and .
The third line contains two space-separated integers denoting the respective values of and .
The fourth line contains space-separated integers denoting the respective distances that each apple falls from point .
The fifth line contains space-separated integers denoting the respective distances that each orange falls from point
```

- 입출력 예
  
```
Example Input 0

7 11
5 15
3 2
-2 2 1
5 -6

Example Output 0

1
1
```

- 풀이
  - sum

```C++
void countApplesAndOranges(int s, int t, int a, int b, vector<int> apples, vector<int> oranges) {
    int applesCount = 0, orangeount = 0;
    
    for(auto&i : apples){
        i += a;
    }

    for(auto&i : oranges){
        i += b;
    }

    for(auto&i : apples){
        if(s <= i && i <= t){
            ++applesCount;
        }
    }

    for(auto&i : oranges){
        if(s <= i && i <= t){
            ++orangeount;
        }
    }

    cout << applesCount << endl;
    cout << orangeount << endl;
}
```
