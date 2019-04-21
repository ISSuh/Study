#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    for(auto i = commands.begin() ; i != commands.end() ; i++){
        vector<int> temp;
        copy(array.begin()+(*i)[0]-1, array.begin()+(*i)[1], back_inserter(temp));

        sort(temp.begin(), temp.end());

        answer.push_back(temp[(*i)[2]-1]);
    }
    
    return answer;
}

int main(){
    int N = 0 , M = 3;
    cin >> N;

    vector<int> array, result;
    vector<vector<int>> commands(1);

    while(N--){
        int temp = 0;
        cin >> temp;

        array.push_back(temp);
    }

    while(M--){
        int temp = 0;
        cin >> temp;

        commands[0].push_back(temp);
    }

    result = solution(array, commands);

    for(auto i = result.begin() ; i != result.end() ; i++)
        cout << *i << " ";
    
    cout << '\n';
}