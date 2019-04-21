#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<pair<int, int>> q;
    int sizeCount = 0, progressCount = 0, index = 0;

    for(auto i = progresses.begin(); i != progresses.end() ; index++, i++)
        q.push(pair<int,int>(index, *i));

    while (!q.empty()){
        if(sizeCount % q.size() == 0){
            int size = q.size();

            for(auto i = 0 ; i < size ; i++){
                if(q.front().second >= 100){
                    q.pop();
                    progressCount++;
                }
            }
            
            if(progressCount)
                answer.push_back(progressCount);

            sizeCount = 0;
        }
        
        q.push(pair<int,int>(q.front().first, q.front().second + speeds[q.front().first]));
        q.pop();

        progressCount = 0;
        sizeCount++;
    }
    
    return answer;
}

int main(){
    int N = 0;
    cin >> N;

    vector<int> progresses, speeds, result;

    while(N--){
        int progresses_input = 0, speeds_input = 0;
        cin >> progresses_input >> speeds_input;

        progresses.push_back(progresses_input);
        speeds.push_back(speeds_input);
    }

    result = solution(progresses, speeds);

    for(auto i = result.begin() ; i != result.end() ; i++)
        cout << *i << ' ';
    cout << endl;
}