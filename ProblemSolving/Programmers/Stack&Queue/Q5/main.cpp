#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> heights) {
    vector<int> answer;
    vector<pair<int, int>> s;
    int index = 0, temp = 0;

    for(auto i = heights.begin() ; i != heights.end() ; index++, i++)
        s.push_back(pair<int, int>(index, *i));
        
    for(auto i = s.rbegin() ; i != s.rend() ; i++){
        for(auto j = i + 1 ; j != s.rend() ; j++){
            if(i->second < j->second){
                temp = j->first+1;
                break;
            }
        }

        if(temp)
            answer.push_back(temp);
        else
            answer.push_back(0);

        temp = 0;
    }

    reverse(answer.begin(), answer.end());
    return answer;
}

int main(){
    int N = 0;
    cin >> N;

    vector<int> heights, result;

    while(N--){
        int heights_input = 0;
        cin >> heights_input;

        heights.push_back(heights_input);
    }

    result = solution(heights);

    for(auto i = result.begin() ; i != result.end() ; i++)
        cout << *i << ' ';
    cout << endl;
}