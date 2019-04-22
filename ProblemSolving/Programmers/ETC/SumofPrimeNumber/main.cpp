#include <iostream>
#include <vector>

using namespace std;

long long solution(int N) {
    long long answer = 0;
    vector<int> check(N);

    for(auto i = 2 ; i <= N ; i++)
        check[i] = i;
    
      for (auto i = 2 ; i*i <= N ; i++) { 
        if (check[i] == 0)
            continue;
        for (int j = i+i; j <= N; j += i)
            check[j] = 0;
    }

    for (auto i = 2; i <= N; i++) {
        if (check[i] != 0)
            answer += check[i]; 
    }

    return answer;
}

int main(){
    int N = 0;
    long long result = 0;

    cin >> N;

    result = solution(N);

    cout << result << '\n';
}