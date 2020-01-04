# Algospot 문제풀이

## 알고리즘 문제해결전략 시리즈

----------------------------------

### [ Microwaving Lunch Boxes ](https://www.algospot.com/judge/problem/read/LUNCHBOX)

- 문제

After suffering from the deficit in summer camp, Ainu7 decided to supply lunch boxes instead of eating outside for Algospot.com winter camp.

He contacted the famous packed lunch company "Doosot" to prepare N lunch boxes for N participants. Due to the massive amount of order, Doosot was not able to prepare the same menu. Instead, they provided different N lunch boxes. Ainu7 put all the lunch boxes to a refrigerator.

The lunch time has come, and suddenly Ainu7 noticed that there is only one microwave available. As all lunch boxes are not the same, they need a different amount of time to microwave and eat. Specifically, i-th lunch box needs Mi seconds to microwave and Ei seconds to eat.

Ainu7 needs to schedule microwave usage order to minimize lunch time. Lunch time is defined as the duration from the beginning of microwaving of any lunch box to the end of eating for all participants. Write a computer program that finds minimum lunch time to help Ainu7. Note that substituting lunch while microwave is turned on is totally unnecessary, because the lunch will be cooled down.

- 입력
 
The first line of the input contains one integer T, the number of test cases.
Each test case consists of three lines. The first line of each test case contains N(1≤N≤10000), the number of the participants.

N integers will follow on the second line. They represent M1, M2, ⋯, MN.
Similarly, N integers will follow on the third line, representing E1, E2, ⋯, EN

- 입출력 예

```
// Input
2
3
2 2 2
2 2 2
3
1 2 3
1 2 1

// Output
8
7
```

- 풀이
  - Greedy

```C++
bool comp(std::pair<int,int>& a, std::pair<int,int>& b){
	return a.first > b.first;
}

int solution(int n, std::vector<int>& heating, std::vector<int>& eating){
	unsigned int time = 0, vecSize = heating.size();
	std::vector<std::pair<int,int>> sch;
	std::vector<int> reaminEat(eating);
	
	for(auto i = 0 ; i < vecSize ; ++i){
		sch.push_back(std::make_pair(eating[i], heating[i]));
	}
	
	std::sort(sch.begin(), sch.end(), comp);
	
	for(auto i = 0; i < vecSize ; ++i){
		time += sch[i].second;
			
		int sum = 0;
		for(auto j = i+1 ; j < vecSize ; ++j){
			sum += sch[j].second;
		}
		
		int remainTime = sch[i].first - sum;
		reaminEat[i] = remainTime <= 0 ? 0 : remainTime;
	}
	
	return time + *std::max_element(reaminEat.begin(), reaminEat.end());
}
```

----------------------------------

### [ 출전 순서 정하기 ](https://www.algospot.com/judge/problem/read/MATCHORDER)

- 문제

전세계 최대의 프로그래밍 대회 알고스팟 컵의 결승전이 이틀 앞으로 다가왔습니다. 각 팀은 n명씩의 프로 코더들로 구성되어 있으며, 결승전에서는 각 선수가 한 번씩 출전해 1:1 경기를 벌여 더 많은 승리를 가져가는 팀이 최종적으로 우승하게 됩니다. 각 팀의 감독은 대회 전날, 주최측에 각 선수를 출전시킬 순서를 알려 주어야 합니다.

결승전 이틀 전, 한국팀의 유감독은 첩보를 통해 상대 러시아팀의 출전 순서를 알아냈습니다. 이 대회에서는 각 선수의 실력을 레이팅(rating)으로 표현합니다. 문제를 간단히 하기 위해 1:1 승부에서는 항상 레이팅이 더 높은 선수가 승리하고, 레이팅이 같을 경우 우리 선수가 승리한다고 가정합시다.

| 경기 | 1 | 2 | 3 | 4 | 5 | 6 |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| 러시아팀 | 3,000 | 2,700 | 2,800 | 2,200 |	2,500 |	1,900 |
| 한국팀	| 2,800	| 2,750	| 2,995 |	1,800 |	2,600 |	2,000 |

표와 같이 출전 순서를 정했다고 하면 한국팀은 2번, 3번, 5번, 6번 경기에서 승리해 전체 네 경기를 이기게 됩니다. 그러나 대신 4번 경기와 1번 경기에 나갈 선수를 바꾸면 1번 경기만을 제외하고 모든 경기에 승리할 수 있지요. 상대방 팀 선수들의 순서를 알고 있을 때, 어느 순서대로 선수들을 내보내야 승수를 최대화할 수 있을까요?


- 입력
 
입력의 첫 줄에는 테스트 케이스의 수 C (C≤50)가 주어집니다. 각 테스트 케이스의 첫 줄에는 각 팀 선수의 수 N(1≤N≤100)가 주어집니다. 그 다음 줄에는 N개의 정수로 러시아팀 각 선수의 레이팅이 출전 순서대로 주어지며, 그 다음 줄에는 N개의 정수로 한국팀 각 선수의 레이팅이 무순으로 주어집니다. 모든 레이팅은 1 이상 4000 이하의 정수입니다.

- 입출력 예

```
3
6
3000 2700 2800 2200 2500 1900
2800 2750 2995 1800 2600 2000
3
1 2 3
3 2 1
4
2 3 4 5
1 2 3 4
```

- 풀이
  - Greedy

```C++
int solution(int n, std::vector<int>& enermy, std::vector<int>& korea){
	unsigned int count = 0;
	unsigned int korPlayer = 0, enrPlayer = 0;
		
	std::sort(enermy.begin(), enermy.end(), std::greater<int>());
	std::sort(korea.begin(), korea.end(), std::greater<int>());
	
	while(korPlayer < korea.size() && enrPlayer < enermy.size()){
		if(korea[korPlayer] < enermy[enrPlayer]){
			++enrPlayer;
		}
		else{
			++korPlayer;
			++enrPlayer;
			++count;
		}
		
	}
	
	return count;
}
```
