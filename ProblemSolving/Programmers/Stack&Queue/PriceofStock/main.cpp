#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer;

    for(auto i=prices.begin() ; i != prices.end() - 1 ; i++){
        int period = 1;
        for(auto j = i + 1 ; j != prices.end() ; j++, period++){
            cout << *i << " / " << *j << '\n';

            if(*i > *j){
                answer.push_back(period);
                break;
            }
            else if(j == prices.end() - 1){
                answer.push_back(period);
                break;
            }
        }
    }

    return answer;
}

int main(){
    int N = 0;
    vector<int> answers, result;

    cin >> N;

    while (N--){
        int temp = 0;
        cin >> temp;

        answers.push_back(temp);
    }
    
    result = solution(answers);

    for(auto &i : result)
        cout << i << ' ';
    cout << '\n';
}