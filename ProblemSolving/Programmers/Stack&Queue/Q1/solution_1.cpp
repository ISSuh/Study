#include <iostream>
#include <string>
#include <stack>

using namespace std;

int solution(string arrangement) {
    int answer = 0;
    stack<char> s;

    for(auto i = arrangement.begin() ; i != arrangement.end() ; i++){
        if(*i == '(')
            s.push('(');
        else{
            s.pop();

            if(*(i-1) == '(')
                answer += s.size();
            else
                answer ++;
        }
    }

    return answer;
}

int main(){
    string N = "";
    int result = 0;

    cin >> N;

    result = solution(N);

    cout << result << '\n';
}