#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(const string &p1, const string &p2){
    string p1p2 = p1+p2;
    string p2p1 = p2+p1;

    if(p1p2 > p2p1)
        return true;
    else
        return false;
}

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> temp;

    for(const auto &i : numbers)
        temp.push_back(to_string(i));
    
    sort(temp.begin(), temp.end(), compare);

    for(const auto &i : temp)
        answer += i; 

    if(atoi(answer.c_str()))
        return answer;
    else
        return to_string(0);
}

int main(){
    int N = 0 , M = 3;
    cin >> N;

    vector<int> array;
    string result;
    while(N--){
        int temp = 0;
        cin >> temp;

        array.push_back(temp);
    }

    result = solution(array);

    cout << result << '\n';
}