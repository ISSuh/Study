# 프로그래머스 문제풀이

## 2020

----------------------------------

### [ 정수 삼각형 ](https://programmers.co.kr/learn/courses/30/lessons/43105) - lv.3

- 문제

주어진 항공권을 모두 이용하여 여행경로를 짜려고 합니다. 항상 "ICN" 공항에서 출발합니다.

항공권 정보가 담긴 2차원 배열 tickets가 매개변수로 주어질 때, 방문하는 공항 경로를 배열에 담아 return 하도록 solution 함수를 작성해주세요.

- 제한사항
  - 모든 공항은 알파벳 대문자 3글자로 이루어집니다.
  - 주어진 공항 수는 3개 이상 10,000개 이하입니다.
  - tickets의 각 행 [a, b]는 a 공항에서 b 공항으로 가는 항공권이 있다는 의미입니다.
  - 주어진 항공권은 모두 사용해야 합니다.
  - 만일 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 합니다.
  - 모든 도시를 방문할 수 없는 경우는 주어지지 않습니다.

- 입출력 예

| tickets | return |
| -- | --| 
| [["ICN", "JFK"], ["HND", "IAD"], ["JFK", "HND"]] | ["ICN", "JFK", "HND", "IAD"] |
| [["ICN", "SFO"], ["ICN", "ATL"], ["SFO", "ATL"], ["ATL", "ICN"], ["ATL","SFO"]] | ["ICN", "ATL", "ICN", "SFO", "ATL", "SFO"] |

`
예제 #1 
["ICN", "JFK", "HND", "IAD"] 순으로 방문할 수 있습니다.
`

`
예제 #2 
["ICN", "SFO", "ATL", "ICN", "ATL", "SFO"] 순으로 방문할 수도 있지만 ["ICN", "ATL", "ICN", "SFO", "ATL", "SFO"] 가 알파벳 순으로 앞섭니다.
`

- 풀이
  - DFS, BFS

```C++
vector<string> solution(vector<vector<string>> tickets) {
    vector<vector<string>> answer;
    vector<vector<int>> answerIndex;
    map<string, vector<pair<string, int>>> m;
    
    // tickets의 요소를 map으로 구성
    for(auto i = 0 ; i < tickets.size() ; ++i){
        m[tickets[i][0]].push_back({tickets[i][1], i});
    }
    
    // ICN부터 시작하여 요소를 DFS로 검사
    for(auto i = m["ICN"].begin() ; i != m["ICN"].end() ; ++i ){
        stack<pair<string, vector<int>>> q;
        q.push({i->first, {i->second}});

        while(!q.empty()){
            auto tmp = q.top();
            q.pop();

            if(tmp.second.size() == tickets.size()){
                answerIndex.push_back(tmp.second);
            }
            
            for(auto j = m[tmp.first].rbegin() ; j != m[tmp.first].rend() ; ++j){
                // 현재까지 저장된 index vector에 현재 index가 없는지 검사 
                if(find(tmp.second.begin(), tmp.second.end(), j->second) == tmp.second.end()){
                    // 현재 검사중인 운항출발지의 여러 목적지가 답이 될수 있으므로
                    // vector를 copy하여 이를 저장
                    auto ans = tmp.second;
                    ans.push_back(j->second);
                    q.push({j->first, ans});
                }
            }
        }
    }

    // 얻은 경로의 index를 기반하여 문자열 생성
    for(auto& i : answerIndex){
        vector<string> temp;
        temp.push_back(tickets[i[0]][0]);
        
        for(auto& j : i){
            temp.push_back(tickets[j][1]);
        }
        answer.push_back(temp);
    }

    // 알파벳 순으로 정렬
    sort(answer.begin(), answer.end());

    return answer[0];
}
```

----------------------------------

### [ 정수 삼각형 ](https://programmers.co.kr/learn/courses/30/lessons/43105) - lv.3

- 문제

![example](https://grepp-programmers.s3.amazonaws.com/files/production/97ec02cc39/296a0863-a418-431d-9e8c-e57f7a9722ac.png)

위와 같은 삼각형의 꼭대기에서 바닥까지 이어지는 경로 중, 거쳐간 숫자의 합이 가장 큰 경우를 찾아보려고 합니다. 아래 칸으로 이동할 때는 대각선 방향으로 한 칸 오른쪽 또는 왼쪽으로만 이동 가능합니다. 예를 들어 3에서는 그 아래칸의 8 또는 1로만 이동이 가능합니다.

삼각형의 정보가 담긴 배열 triangle이 매개변수로 주어질 때, 거쳐간 숫자의 최댓값을 return 하도록 solution 함수를 완성하세요.

- 제한사항
  - 삼각형의 높이는 1 이상 500 이하입니다.
  - 삼각형을 이루고 있는 숫자는 0 이상 9,999 이하의 정수입니다.

- 입출력 예

| triangle | target 
| -- | --| 
| [[7], [3, 8], [8, 1, 0], [2, 7, 4, 4], [4, 5, 2, 6, 5]] | 30 |

- 풀이
  - DP

```C++
int solution(vector<vector<int>> triangle) {
    vector<vector<int>> answer = triangle;
    
    for(auto i = 0 ; i < triangle.size() - 1 ; ++i ){
        for(auto j = 0 ; j < triangle[i].size() ; ++j){
            int left = answer[i][j] + triangle[i+1][j];
            int right = answer[i][j] + triangle[i+1][j+1];
            
            if(left > answer[i+1][j]){
                answer[i+1][j] = left;
            }
            
            if(right > answer[i+1][j+1]){
                answer[i+1][j+1] = right;
            }
        }
    }
    
    return *max_element(answer.rbegin()->begin(), answer.rbegin()->end());
}
```

----------------------------------

### [ 단속카메라 ](https://programmers.co.kr/learn/courses/30/lessons/42884) - lv.3

- 문제

두 개의 단어 begin, target과 단어의 집합 words가 있습니다. 아래와 같은 규칙을 이용하여 begin에서 target으로 변환하는 가장 짧은 변환 과정을 찾으려고 합니다.

```
1. 한 번에 한 개의 알파벳만 바꿀 수 있습니다.
2. words에 있는 단어로만 변환할 수 있습니다.
```

예를 들어 begin이 "hit", target가 "cog", words가 ["hot","dot","dog","lot","log","cog"]라면 "hit" -> "hot" -> "dot" -> "dog" -> "cog"와 같이 4단계를 거쳐 변환할 수 있습니다.

두 개의 단어 begin, target과 단어의 집합 words가 매개변수로 주어질 때, 최소 몇 단계의 과정을 거쳐 begin을 target으로 변환할 수 있는지 return 하도록 solution 함수를 작성해주세요.

- 제한사항
  - 각 단어는 알파벳 소문자로만 이루어져 있습니다.
  - 각 단어의 길이는 3 이상 10 이하이며 모든 단어의 길이는 같습니다.
  - words에는 3개 이상 50개 이하의 단어가 있으며 중복되는 단어는 없습니다.
  - begin과 target은 같지 않습니다.
  - 변환할 수 없는 경우에는 0를 return 합니다.

- 입출력 예

| begin | target | words | return |
| -- | --| --| --|
| "hit" | "cog" | ["hot", "dot", "dog", "lot", "log", "cog"] | 4 |
| "hit" | "cog" | ["hot", "dot", "dog", "lot", "log"] | 0 |

`예제 #1 문제에 나온 예와 같습니다.`
`예제 #2 target인 "cog"는 words 안에 없기 때문에 변환할 수 없습니다.`

- 풀이
  - DFS

```C++
int solution(string begin, string target, vector<string> words) {
    int answer = INT_MAX;
    
    // begin과 하나만 다른words의 elements 찾아서 저장
    vector<string> choice;
    for(auto& str : words){
        int count = 0;
        for(auto i = 0 ; i < begin.size() ; ++i){
            if(begin[i] != str[i]){
                    ++count;
                }
            }
            if(count == 1)
                choice.push_back(str);
    }

    for(auto i = 0 ; i < choice.size() ; ++i){
        // 한번 조회한 element 체크
        vector<bool> check(words.size(), false);
        stack<pair<string, int>> s;
        int val = INT_MAX;
            
        s.push({choice[i], 1});
        
        while(!s.empty()){
            auto temp = s.top();
            s.pop();
            
            // target과 같을때, 현재 저장된 값보다 count가 작으면 저장
            if(temp.first == target){
                if(temp.second < val)
                    val = temp.second;
            }
            
            // 현재 단계에서 하나만 다른words의 elements 찾아서 저장
            for(auto j = 0; j < words.size() ; ++j){
                if(check[j])
                    continue;

                int count = 0;
                for(auto t = 0 ; t < words[j].size() ; ++t){
                    if(words[j][t] != temp.first[t]){
                        ++count;
                    }
                }
                if(count == 1){
                    s.push({words[j], temp.second + 1});
                    check[j] = true;
                }
            }
        }
        
        if(val < answer)
            answer = val;
    }
    
    return answer == INT_MAX ? 0 : answer;
}
```

----------------------------------

### [ 단속카메라 ](https://programmers.co.kr/learn/courses/30/lessons/42884) - lv.3

- 문제

고속도로를 이동하는 모든 차량이 고속도로를 이용하면서 단속용 카메라를 한 번은 만나도록 카메라를 설치하려고 합니다.

고속도로를 이동하는 차량의 경로 routes가 매개변수로 주어질 때, 모든 차량이 한 번은 단속용 카메라를 만나도록 하려면 최소 몇 대의 카메라를 설치해야 하는지를 return 하도록 solution 함수를 완성하세요.

- 제한사항
  - 차량의 대수는 1대 이상 10,000대 이하입니다.
  - routes에는 차량의 이동 경로가 포함되어 있으며 routes[i][0]에는 i번째 차량이 고속도로에 진입한 지점, routes[i][1]에는 i번째 차량이 고속도로에서 나간 지점이 적혀 있습니다.
  - 차량의 진입/진출 지점에 카메라가 설치되어 있어도 카메라를 만난것으로 간주합니다.
  - 차량의 진입 지점, 진출 지점은 -30,000 이상 30,000 이하입니다.

- 입출력 예

| routes | return |
| -- | --|
| [[-20,15], [-14,-5], [-18,-13], [-5,-3]] | 2 |

`-5 지점에 카메라를 설치하면 두 번째, 네 번째 차량이 카메라를 만납니다.
 -15 지점에 카메라를 설치하면 첫 번째, 세 번째 차량이 카메라를 만납니다. `

- 풀이
  - Greedy

```C++
bool comp(vector<int>& a, vector<int>& b){
    return a[1] < b[1];    
}

int solution(vector<vector<int>> routes) {
    int answer = 1;
    int preValue = 0;
    
    sort(routes.begin(), routes.end(), comp);
    
    preValue = routes[0][1];
    for(auto& i : routes){
        if(i[0] > preValue){
            ++answer;
            preValue = i[1];
        }
    }
    
    return answer;
}
```

----------------------------------

### [ 종이접기 ](https://programmers.co.kr/learn/courses/30/lessons/62049?language=cpp) - lv.3

- 문제

직사각형 종이를 n번 접으려고 합니다. 이때, 항상 오른쪽 절반을 왼쪽으로 접어 나갑니다. 다음은 n = 2인 경우의 예시입니다.

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_390/v1500952547/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B01_swcvrz.png)

먼저 오른쪽 절반을 왼쪽으로 접습니다.

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_195/v1500952547/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B02_e49oe3.png)

다시 오른쪽 절반을 왼쪽으로 접습니다.

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_95/v1500952178/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B03_nqdurc.png)

종이를 모두 접은 후에는 종이를 전부 펼칩니다. 종이를 펼칠 때는 종이를 접은 방법의 역순으로 펼쳐서 처음 놓여있던 때와 같은 상태가 되도록 합니다. 위와 같이 두 번 접은 후 종이를 펼치면 아래 그림과 같이 종이에 접은 흔적이 생기게 됩니다.

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_390/v1500952178/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B04_qxfoxr.png)

위 그림에서 ∨ 모양이 생긴 부분은 점선(0)으로, ∧ 모양이 생긴 부분은 실선(1)으로 표시했습니다.

종이를 접은 횟수 n이 매개변수로 주어질 때, 종이를 절반씩 n번 접은 후 모두 펼쳤을 때 생기는 접힌 부분의 모양을 배열에 담아 return 하도록 solution 함수를 완성해주세요.

- 제한사항
  - 종이를 접는 횟수 n은 1 이상 20 이하의 자연수입니다.
  - 종이를 접었다 편 후 생긴 굴곡이 ∨ 모양이면 0, ∧ 모양이면 1로 나타냅니다.
  - 가장 왼쪽의 굴곡 모양부터 순서대로 배열에 담아 return 해주세요.

- 입출력 예

| n | result |
| -- | --|
| 1 | [0] |
| 2 | [0,0,1] |
| 3 | [0,0,1,0,0,1,1] |

`입출력 예 #1 종이의 오른쪽 절반을 왼쪽으로 한번 접었다 펴면 아래 그림과 같이 굴곡이 생깁니다. `

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_390/v1500952178/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B05_fpgzni.png)

`입출력 예 #2 문제의 예시와 같습니다. `

`입출력 예 #3 종이를 절반씩 세 번 접은 후 다시 펼치면 아래 그림과 같이 굴곡이 생깁니다. `

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_390/v1500952178/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B06_sbn7li.png)

- 풀이
  - index

```C++
vector<int> solution(int n) {
    vector<int> answer;
    int N = 0;
    
    for(auto i = 0 ; i < n ; ++i){
        N = N * 2 + 1;
        answer.resize(N);
        
        int size = answer.size() / 2;
        answer[size] = 0;
        for(auto j = 0 ; j < size ; ++j){
            answer[answer.size() - j - 1] = answer[j] == 0 ? 1 : 0;
        }
    }
    
    return answer;
}
```

----------------------------------

### [ 2 x n 타일링 ](https://programmers.co.kr/learn/courses/30/lessons/12900) - lv.3

- 문제

가로 길이가 2이고 세로의 길이가 1인 직사각형모양의 타일이 있습니다. 이 직사각형 타일을 이용하여 세로의 길이가 2이고 가로의 길이가 n인 바닥을 가득 채우려고 합니다. 타일을 채울 때는 다음과 같이 2가지 방법이 있습니다.

    타일을 가로로 배치 하는 경우
    타일을 세로로 배치 하는 경우

예를들어서 n이 7인 직사각형은 다음과 같이 채울 수 있습니다.

![example](https://i.imgur.com/29ANX0f.png)

직사각형의 가로의 길이 n이 매개변수로 주어질 때, 이 직사각형을 채우는 방법의 수를 return 하는 solution 함수를 완성해주세요.

- 제한사항
  - 가로의 길이 n은 60,000이하의 자연수 입니다.
  - 경우의 수가 많아 질 수 있으므로, 경우의 수를 1,000,000,007으로 나눈 나머지를 return해주세요.

- 입출력 예

| n | result |
| -- | --|
| 4 | 5 |

`입출력 예 #1 다음과 같이 5가지 방법이 있다.`

![example](https://i.imgur.com/keiKrD3.png)
![example](https://i.imgur.com/O9GdTE0.png)
![example](https://i.imgur.com/IZBmc6M.png)
![example](https://i.imgur.com/29LWVzK.png)
![example](https://i.imgur.com/z64JbNf.png)

- 풀이
  - DP

```C++
int solution(int n) {
    if(n == 0)
        return 0;
    
    int answer = 0;
    int n_1 = 1;
    int n_2 = 0;
    
    for(auto i = 1; i <= n ; ++i){
        answer = (n_2 + n_1) % 1000000007;
        n_2 = n_1;
        n_1 = answer;
    }
    
    return answer;
}
```

## 2019

----------------------------------

### [ 캐시 ](https://programmers.co.kr/learn/courses/30/lessons/17680) - lv.2

- 문제

지도개발팀에서 근무하는 제이지는 지도에서 도시 이름을 검색하면 해당 도시와 관련된 맛집 게시물들을 데이터베이스에서 읽어 보여주는 서비스를 개발하고 있다.
이 프로그램의 테스팅 업무를 담당하고 있는 어피치는 서비스를 오픈하기 전 각 로직에 대한 성능 측정을 수행하였는데, 제이지가 작성한 부분 중 데이터베이스에서 게시물을 가져오는 부분의 실행시간이 너무 오래 걸린다는 것을 알게 되었다.
어피치는 제이지에게 해당 로직을 개선하라고 닦달하기 시작하였고, 제이지는 DB 캐시를 적용하여 성능 개선을 시도하고 있지만 캐시 크기를 얼마로 해야 효율적인지 몰라 난감한 상황이다.
어피치에게 시달리는 제이지를 도와, DB 캐시를 적용할 때 캐시 크기에 따른 실행시간 측정 프로그램을 작성하시오.

- 제한사항
  - 캐시 크기(cacheSize)와 도시이름 배열(cities)을 입력받는다.
  - cacheSize는 정수이며, 범위는 0 ≦ cacheSize ≦ 30 이다.
  - cities는 도시 이름으로 이뤄진 문자열 배열로, 최대 도시 수는 100,000개이다.
  - 각 도시 이름은 공백, 숫자, 특수문자 등이 없는 영문자로 구성되며, 대소문자 구분을 하지 않는다. 도시 이름은 최대 20자로 이루어져 있다.
  - 입력된 도시이름 배열을 순서대로 처리할 때, "총 실행시간"을 출력한다.
  - 캐시 교체 알고리즘은 LRU(Least Recently Used)를 사용한다.
  - cache hit일 경우 실행시간은 1이다.
  - cache miss일 경우 실행시간은 5이다.


- 입출력 예

| 캐시크기(cacheSize) | 도시이름(cities) | 실행시간 |
| -- | --| --|
| 3 |	["Jeju", "Pangyo", "Seoul", "NewYork", "LA", "Jeju", "Pangyo", "Seoul", "NewYork", "LA"] |	50 |
| 3 |	["Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul"] |	21 |
| 2 |	["Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome"] | 60 |
| 5 |	["Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome"] | 52 |
| 2 |	["Jeju", "Pangyo", "NewYork", "newyork"] |	16 |
| 0 |	["Jeju", "Pangyo", "Seoul", "NewYork", "LA"] |	25 |

- 풀이
  - LRU

```C++
int solution(int cacheSize, vector<string> cities) {
    if(cacheSize < 1)
        return cities.size() * 5;
    
    int answer = 0;
    map<string, int> m;
    queue<string> q;
    
    for(auto& i : cities){
        std::transform(i.begin(), i.end(), i.begin(), ::toupper);
        
        if(m.find(i) != m.end()){
            answer += 1;
            
            queue<string> temp;
            while(!q.empty()){
                if(q.front() != i)
                    temp.push(q.front());
                q.pop();
            }
            temp.push(i);
            
            q.swap(temp);
        }
        else{
            if(m.size() >= cacheSize){
                auto least = q.front();
                q.pop();
                m.erase(least);                
            }
            
            m[i] = 1;
            q.push(i);
            answer += 5;
        }
    }
    
    return answer;
}
```

----------------------------------

### [ 뉴스 클러스터링 ](https://programmers.co.kr/learn/courses/30/lessons/17677) - lv.2

- 문제

여러 언론사에서 쏟아지는 뉴스, 특히 속보성 뉴스를 보면 비슷비슷한 제목의 기사가 많아 정작 필요한 기사를 찾기가 어렵다. Daum 뉴스의 개발 업무를 맡게 된 신입사원 튜브는 사용자들이 편리하게 다양한 뉴스를 찾아볼 수 있도록 문제점을 개선하는 업무를 맡게 되었다.

개발의 방향을 잡기 위해 튜브는 우선 최근 화제가 되고 있는 "카카오 신입 개발자 공채" 관련 기사를 검색해보았다.

    카카오 첫 공채..'블라인드' 방식 채용
    카카오, 합병 후 첫 공채.. 블라인드 전형으로 개발자 채용
    카카오, 블라인드 전형으로 신입 개발자 공채
    카카오 공채, 신입 개발자 코딩 능력만 본다
    카카오, 신입 공채.. "코딩 실력만 본다"
    카카오 "코딩 능력만으로 2018 신입 개발자 뽑는다"

기사의 제목을 기준으로 "블라인드 전형"에 주목하는 기사와 "코딩 테스트"에 주목하는 기사로 나뉘는 걸 발견했다. 튜브는 이들을 각각 묶어서 보여주면 카카오 공채 관련 기사를 찾아보는 사용자에게 유용할 듯싶었다.

유사한 기사를 묶는 기준을 정하기 위해서 논문과 자료를 조사하던 튜브는 "자카드 유사도"라는 방법을 찾아냈다.

자카드 유사도는 집합 간의 유사도를 검사하는 여러 방법 중의 하나로 알려져 있다. 두 집합 A, B 사이의 자카드 유사도 J(A, B)는 두 집합의 교집합 크기를 두 집합의 합집합 크기로 나눈 값으로 정의된다.

예를 들어 집합 A = {1, 2, 3}, 집합 B = {2, 3, 4}라고 할 때, 교집합 A ∩ B = {2, 3}, 합집합 A ∪ B = {1, 2, 3, 4}이 되므로, 집합 A, B 사이의 자카드 유사도 J(A, B) = 2/4 = 0.5가 된다. 집합 A와 집합 B가 모두 공집합일 경우에는 나눗셈이 정의되지 않으니 따로 J(A, B) = 1로 정의한다.

자카드 유사도는 원소의 중복을 허용하는 다중집합에 대해서 확장할 수 있다. 다중집합 A는 원소 "1"을 3개 가지고 있고, 다중집합 B는 원소 "1"을 5개 가지고 있다고 하자. 이 다중집합의 교집합 A ∩ B는 원소 "1"을 min(3, 5)인 3개, 합집합 A ∪ B는 원소 "1"을 max(3, 5)인 5개 가지게 된다. 다중집합 A = {1, 1, 2, 2, 3}, 다중집합 B = {1, 2, 2, 4, 5}라고 하면, 교집합 A ∩ B = {1, 2, 2}, 합집합 A ∪ B = {1, 1, 2, 2, 3, 4, 5}가 되므로, 자카드 유사도 J(A, B) = 3/7, 약 0.42가 된다.

이를 이용하여 문자열 사이의 유사도를 계산하는데 이용할 수 있다. 문자열 "FRANCE"와 "FRENCH"가 주어졌을 때, 이를 두 글자씩 끊어서 다중집합을 만들 수 있다. 각각 {FR, RA, AN, NC, CE}, {FR, RE, EN, NC, CH}가 되며, 교집합은 {FR, NC}, 합집합은 {FR, RA, AN, NC, CE, RE, EN, CH}가 되므로, 두 문자열 사이의 자카드 유사도 J("FRANCE", "FRENCH") = 2/8 = 0.25가 된다.

- 제한사항
  - 입력으로는 str1과 str2의 두 문자열이 들어온다. 각 문자열의 길이는 2 이상, 1,000 이하이다.
  - 입력으로 들어온 문자열은 두 글자씩 끊어서 다중집합의 원소로 만든다. 이때 영문자로 된 글자 쌍만 유효하고, 기타 공백이나 숫자, 특수 문자가 들어있는 경우는 그 글자 쌍을 버린다. 예를 들어 "ab+"가 입력으로 들어오면, "ab"만 다중집합의 원소로 삼고, "b+"는 버린다.
  - 다중집합 원소 사이를 비교할 때, 대문자와 소문자의 차이는 무시한다. "AB"와 "Ab", "ab"는 같은 원소로 취급한다.

- 입출력 예

| str1 | str2 |	answer
| -- | --| --|
| FRANCE | french | 16384 |
| handshake | shake hands | 65536 |
| aa1+aa2 | AAAA12 | 43690 |
| E=M*C^2 | e=m*c^2 | 65536 |

- 풀이
  - sort, set

```C++
int solution(string str1, string str2) {
    int answer = 0;
    vector<string> s1, s2;
    vector<string> unionStr, intersectionStr;
    
    std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    
    for(auto i = 1 ; i < str1.size() ; ++i){
        if(('a' <= str1[i-1] && str1[i-1] <= 'z') && ('a' <= str1[i] && str1[i] <= 'z'))
            s1.push_back(str1.substr(i-1, 2));
    }
    
    for(auto i = 1 ; i < str2.size() ; ++i){
        if(('a' <= str2[i-1] && str2[i-1] <= 'z') && ('a' <= str2[i] && str2[i] <= 'z'))
            s2.push_back(str2.substr(i-1, 2));
    }
    
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(unionStr));    
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(intersectionStr));
    
    if(unionStr.size() < 1)
        answer = 65536;
    else
        answer = (static_cast<float>(intersectionStr.size()) / static_cast<float>(unionStr.size())) * 65536;
    
    return answer;
}
```
----------------------------------

### [ 가장 큰 정사각형 찾기  ](https://programmers.co.kr/learn/courses/30/lessons/12905) - lv.2

- 문제

1와 0로 채워진 표(board)가 있습니다. 표 1칸은 1 x 1 의 정사각형으로 이루어져 있습니다. 표에서 1로 이루어진 가장 큰 정사각형을 찾아 넓이를 return 하는 solution 함수를 완성해 주세요. (단, 정사각형이란 축에 평행한 정사각형을 말합니다.)

예를 들어

| 1 | 2 | 3 | 4 |
| ----------- | ----------- | ----------- | ----------- |
| 0 | 1 | 1 | 1 |
| 1 | 1 | 1 | 1 |
| 1 | 1 | 1 | 1 |
| 0 | 0 | 1 | 0 |

가 있다면 가장 큰 정사각형은

| 1 | 2 | 3 | 4 |
| ----------- | ----------- | ----------- | ----------- |
| 0 | `1` | `1` | `1` |
| 1 | `1` | `1` | `1` |
| 1 | `1` | `1` | `1` |
| 0 | 0 | 1 | 0 |

가 되며 넓이는 9가 되므로 9를 반환해 주면 됩니다.

- 제한사항
  - 표(board)는 2차원 배열로 주어집니다.
  - 표(board)의 행(row)의 크기 : 1,000 이하의 자연수
  - 표(board)의 열(column)의 크기 : 1,000 이하의 자연수
  - 표(board)의 값은 1또는 0으로만 이루어져 있습니다.

- 입출력 예
  
| board |  result |
| ----------- | ----------- |
| [[0,1,1,1],[1,1,1,1],[1,1,1,1],[0,0,1,0]] | 9 |
| [[0,0,1,1],[1,1,1,1]] | 4 |

`입출력 예 #1
위의 예시와 같습니다.

입출력 예 #2
| 0 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 |
로 가장 큰 정사각형의 넓이는 4가 되므로 4를 return합니다.`

- 풀이
  - DP

```C++
int solution(vector<vector<int>> board)
{
    if(board.size() < 2 || board[0].size() < 2)
        return 1;
    
    int answer = 0;

    for(auto i = 1; i < board.size() ; ++i){        
        for(auto j = 1; j < board[0].size() ; ++j){
            if(board[i][j] == 0)
                continue;
            
            board[i][j] = min({board[i-1][j-1], board[i-1][j], board[i][j-1]}) + 1;
        }
        
        int max = *max_element(board[i].begin(), board[i].end());
        if(answer < max)
            answer = max;
    }

    return answer * answer;
}
```

### [ H-Index ](https://programmers.co.kr/learn/courses/30/lessons/42747) - lv.2

- 문제

H-Index는 과학자의 생산성과 영향력을 나타내는 지표입니다. 어느 과학자의 H-Index를 나타내는 값인 h를 구하려고 합니다. 위키백과1에 따르면, H-Index는 다음과 같이 구합니다.
어떤 과학자가 발표한 논문 n편 중, h번 이상 인용된 논문이 h편 이상이고 나머지 논문이 h번 이하 인용되었다면 h가 이 과학자의 H-Index입니다.
어떤 과학자가 발표한 논문의 인용 횟수를 담은 배열 citations가 매개변수로 주어질 때, 이 과학자의 H-Index를 return 하도록 solution 함수를 작성해주세요.

- 제한사항
  - 과학자가 발표한 논문의 수는 1편 이상 1,000편 이하입니다.
  - 논문별 인용 횟수는 0회 이상 10,000회 이하입니다.

- 입출력 예
  
| citations |  result |
| ----------- | ----------- |
| [3, 0, 6, 1, 5] | 3 |

`이 과학자가 발표한 논문의 수는 5편이고, 그중 3편의 논문은 3회 이상 인용되었습니다. 그리고 나머지 2편의 논문은 3회 이하 인용되었기 때문에 이 과학자의 H-Index는 3입니다.`

- 풀이
  - sort

```C++
int solution(vector<int> citations) {
    int answer = 0;
    
    std::sort(citations.begin() , citations.end(), greater<int>());

    for(auto i = 0 ; i < citations.size() ; ++i){
        if(citations[i] < i+1)
            return i;
    }    
        
    return citations.size();
}
```
----------------------------------

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
  - index

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
----------------------------------

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

`가로가 8, 세로가 12인 직사각형을 대각선 방향으로 자르면 총 16개 정사각형을 사용할 수 없게 됩니다. 원래 직사각형에서는 96개의 정사각형을 만들 수 있었으므로, 96 - 16 = 80 을 반환합니다.`

![example](https://grepp-programmers.s3.amazonaws.com/files/production/ee895b2cd9/567420db-20f4-4064-afc3-af54c4a46016.png)

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
----------------------------------

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

`예제 #1 아래와 같이 2개의 네트워크가 있습니다.`

![example](https://grepp-programmers.s3.amazonaws.com/files/ybm/5b61d6ca97/cc1e7816-b6d7-4649-98e0-e95ea2007fd7.png)

`예제 #2 아래와 같이 1개의 네트워크가 있습니다.`

![example](https://grepp-programmers.s3.amazonaws.com/files/ybm/7554746da2/edb61632-59f4-4799-9154-de9ca98c9e55.png)

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
