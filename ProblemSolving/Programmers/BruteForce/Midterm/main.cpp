#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer, score = {0,0,0};
    vector<int> p1 = {1,2,3,4,5};
    vector<int> p2 = {2,1,2,3,2,4,2,5};
    vector<int> p3 = {3,3,1,1,2,2,4,4,5,5};
    int indexP1 = 0, indexP2 = 0, indexP3 = 0;

    for(auto i = 0 ; i < answers.size() ; i++){
        if(answers[i] == p1[indexP1])
            score[0]++;
        
        if(answers[i] == p2[indexP2])
            score[1]++;

        if(answers[i] == p3[indexP3])
            score[2]++;

        indexP1++;
        if(indexP1 >= p1.size())
            indexP1 = 0;

        indexP2++;
        if(indexP2 >= p2.size())
            indexP2 = 0;

        indexP3++;
        if(indexP3 >= p3.size())
            indexP3 = 0;
    }

    auto itMax = max_element(score.begin(), score.end());
    for(auto i = 0 ; i < score.size() ; i++)
        if(*itMax == score[i])
            answer.push_back(i+1);

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