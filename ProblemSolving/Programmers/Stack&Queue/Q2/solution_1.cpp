#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0, index = 0;
    queue<pair<int, int>> q;
    auto it = priorities.begin();

    for(auto i = priorities.begin() ; i != priorities.end() ; i++){
        q.push(pair<int,int>(index, *i));
        index++;
    }

    sort(priorities.begin(), priorities.end(), greater<int>());
`
    index = 1;
    while(!q.empty()){  
        if(*it != q.front().second){
            q.push(q.front());
            q.pop();
        }
        else{
            if(q.front().first == location){
                answer = index;
                break;
            }

            it++;
            q.pop();
            index++; 
        }
    }

    return answer;
}

int main(){
    int N = 0, location = 0;
    cin >> N >> location;

    vector<int> priorities;

    while(N--){
        int temp = 0;
        cin >> temp;
        priorities.push_back(temp);
    }

    int result = solution(priorities, location);

    cout << result << '\n';
}