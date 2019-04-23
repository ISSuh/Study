#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
        int answer = n;
        vector<int> lostFiltered, reserveFiltered;
        
        for(auto i = lost.begin() ; i != lost.end() ; i++){
            auto now =  find(reserve.begin(), reserve.end(), *i);
            if(now == reserve.end())
                lostFiltered.push_back(*i);
        }

        for(auto i = reserve.begin() ; i != reserve.end() ; i++){
            auto now =  find(lost.begin(), lost.end(), *i);
            if(now == lost.end())
                reserveFiltered.push_back(*i);
        }

        for(auto i = lostFiltered.begin() ; i != lostFiltered.end() ; i++){
            auto previous =  find(reserveFiltered.begin(), reserveFiltered.end(), *i - 1);
            if(previous != reserveFiltered.end()){
                reserveFiltered.erase(previous);
                continue;
            }

            auto next =  find(reserveFiltered.begin(), reserveFiltered.end(), *i + 1);
            if(next != reserveFiltered.end()){
                reserveFiltered.erase(next);
                continue;
            }
            
            answer--;
        }

        return answer;
}

int main(){
    int N = 0, M = 0, n = 0, result = 0;
    vector<int> lost, reserve;

    cin >> n >> N >> M;

    while (N--){
        int temp = 0;
        cin >> temp;

        lost.push_back(temp);
    }

    while (M--){
        int temp = 0;
        cin >> temp;

        reserve.push_back(temp);
    }
    
    result = solution(n, lost, reserve);

    cout << result << '\n';
}