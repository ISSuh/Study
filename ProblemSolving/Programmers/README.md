# 프로그래머스 문제풀이
## 2019

### [스킬트리](https://programmers.co.kr/learn/courses/30/lessons/49993) - lv.2

- 문제

선행 스킬이란 어떤 스킬을 배우기 전에 먼저 배워야 하는 스킬을 뜻합니다.
예를 들어 선행 스킬 순서가 스파크 → 라이트닝 볼트 → 썬더일때, 썬더를 배우려면 먼저 라이트닝 볼트를 배워야 하고, 라이트닝 볼트를 배우려면 먼저 스파크를 배워야 합니다.
위 순서에 없는 다른 스킬(힐링 등)은 순서에 상관없이 배울 수 있습니다. 따라서 스파크 → 힐링 → 라이트닝 볼트 → 썬더와 같은 스킬트리는 가능하지만, 썬더 → 스파크나 라이트닝 볼트 → 스파크 → 힐링 → 썬더와 같은 스킬트리는 불가능합니다.
선행 스킬 순서 skill과 유저들이 만든 스킬트리1를 담은 배열 skill_trees가 매개변수로 주어질 때, 가능한 스킬트리 개수를 return 하는 solution 함수를 작성해주세요.

- 제한사항
  - 스킬은 알파벳 대문자로 표기하며, 모든 문자열은 알파벳 대문자로만 이루어져 있습니다.
  - 스킬 순서와 스킬트리는 문자열로 표기합니다.
    - 예를 들어, C → B → D 라면 "CBD"로 표기합니다
  - 선행 스킬 순서 skill의 길이는 1 이상 26 이하이며, 스킬은 중복해 주어지지 않습니다.
  - skill_trees는 길이 1 이상 20 이하인 배열입니다.
  - skill_trees의 원소는 스킬을 나타내는 문자열입니다.
    - skill_trees의 원소는 길이가 2 이상 26 이하인 문자열이며, 스킬이 중복해 주어지지 않습니다.


- 입출력 예
  
| Skill | skill_trees | result |
| ----------- | ----------- | ----------- |
| "CBD" | ["BACDE", "CBADF", "AECB", "BDA"] |	2 |

- 풀이
  - GCD

```C++
int solution(string skill, vector<string> skill_trees) {
    int answer = 0, flag = 1;
    
    for(auto &i : skill_trees){
        int skillIndex = 0;
        
        for(auto &j : i){
            if(skill.find(j) == std::string::npos)
                continue;
            
            if(skill[skillIndex] == j)
                ++skillIndex;
            else{
                flag = 0;
                break;
            }
        }
        if(flag)
            answer++;
        
        flag = 1;
    }
    
    return answer;
}
```

### [멀쩡한 사각형](https://programmers.co.kr/learn/courses/30/lessons/62048) - lv.2

- 문제

가로 길이가 Wcm, 세로 길이가 Hcm인 직사각형 종이가 있습니다. 종이에는 가로, 세로 방향과 평행하게 격자 형태로 선이 그어져 있으며, 모든 격자칸은 1cm x 1cm 크기입니다. 이 종이를 격자 선을 따라 1cm × 1cm의 정사각형으로 잘라 사용할 예정이었는데, 누군가가 이 종이를 대각선 꼭지점 2개를 잇는 방향으로 잘라 놓았습니다. 그러므로 현재 직사각형 종이는 크기가 같은 직각삼각형 2개로 나누어진 상태입니다. 새로운 종이를 구할 수 없는 상태이기 때문에, 이 종이에서 원래 종이의 가로, 세로 방향과 평행하게 1cm × 1cm로 잘라 사용할 수 있는 만큼만 사용하기로 하였습니다.
가로의 길이 W와 세로의 길이 H가 주어질 때, 사용할 수 있는 정사각형의 개수를 구하는 solution 함수를 완성해 주세요.

- 제한사항
  - W, H : 1억 이하의 자연수

- 입출력 예
  
| W | H | result |
| ----------- | ----------- | ----------- |
| 8 | 12 |	80 |

- 풀이
  - GCD

```C++
long long getGCD(int a, int b){
    if(a == 0) return b;
    return getGCD(b % a, a);
}

long long solution(int w,int h)
{
	long long gcd = getGCD(w, h);
	long long sum = (long long)w * (long long)h;
    
	return sum - (w + h - gcd);
}
```

### [네트워크](https://programmers.co.kr/learn/courses/30/lessons/43162) - lv.3

- 문제
네트워크란 컴퓨터 상호 간에 정보를 교환할 수 있도록 연결된 형태를 의미합니다. 예를 들어, 컴퓨터 A와 컴퓨터 B가 직접적으로 연결되어있고, 컴퓨터 B와 컴퓨터 C가 직접적으로 연결되어 있을 때 컴퓨터 A와 컴퓨터 C도 간접적으로 연결되어 정보를 교환할 수 있습니다. 따라서 컴퓨터 A, B, C는 모두 같은 네트워크 상에 있다고 할 수 있습니다.
컴퓨터의 개수 n, 연결에 대한 정보가 담긴 2차원 배열 computers가 매개변수로 주어질 때, 네트워크의 개수를 return 하도록 solution 함수를 작성하시오.

- 제한사항
  - 컴퓨터의 개수 n은 1 이상 200 이하인 자연수입니다.
  - 각 컴퓨터는 0부터 n-1인 정수로 표현합니다.
  - i번 컴퓨터와 j번 컴퓨터가 연결되어 있으면 computers[i][j]를 1로 표현합니다.
  - computer[i][i]는 항상 1입니다.

- 입출력 예
  - n	computers	return
  
| n | vector | return |
| ----------- | ----------- | ----------- |
| 3 | [[1, 1, 0], [1, 1, 0], [0, 0, 1]] | 2 |
| 3 | [[1, 1, 0], [1, 1, 1], [0, 1, 1]] | 1 |

- 풀이
  - DFS, BFS

```C++
int solution(int n, vector<vector<int>> computers) {
    int answer = 0;   
    stack<int> s;

    for(auto index = 0 ; index < n ; ++index){
        if(!computers[index][index])
            continue;
        
        s.push(index);

        while(!s.empty()){
            int i = s.top();
            s.pop();

            for(auto j = 0 ; j < n ; ++j){                
                if(computers[i][j] && computers[j][i]){
                    computers[i][j] = 0;
                    s.push(j);
                }
            }
        }
        
        ++answer;
    }
    
    return answer;
}
```
