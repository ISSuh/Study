/*
https://www.acmicpc.net/problem/1946



언제나 최고만을 지향하는 굴지의 대기업 진영 주식회사가 신규 사원 채용을 실시한다. 인재 선발 시험은 1차 서류심사와 2차 면접시험으로 이루어진다. 최고만을 지향한다는 기업의 이념에 따라 그들은 최고의 인재들만을 사원으로 선발하고 싶어 한다.

그래서 진영 주식회사는, 다른 모든 지원자와 비교했을 때 서류심사 성적과 면접시험 성적 중 적어도 하나가 다른 지원자보다 떨어지지 않는 자만 선발한다는 원칙을 세웠다. 즉, 어떤 지원자 A의 성적이 다른 어떤 지원자 B의 성적에 비해 서류 심사 결과와 면접 성적이 모두 떨어진다면 A는 결코 선발되지 않는다.

이러한 조건을 만족시키면서, 진영 주식회사가 이번 신규 사원 채용에서 선발할 수 있는 신입사원의 최대 인원수를 구하는 프로그램을 작성하시오.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

int main(){
    int T = 0;
    std::cin >> T;

    while(T--){
        int N = 0, count = 0;
        std::cin >> N;
    
        std::vector<std::pair<int,int>> item;
        std::stack<int> stack;

        for(auto i = 0 ; i < N ; ++i){
            int a = 0, b = 0;
            std::cin >> a >> b;
            item.push_back(std::make_pair(a,b));
        }

        std::sort(item.begin(), item.end());

        stack.push(item[0].second);
        for(auto i = item.begin() + 1 ; i != item.end() ; ++i){
            if(i->second < stack.top()){
                stack.push(i->second);
                ++count;                
            }
        }
        
        std::cout << count + 1 << '\n';
    }
}