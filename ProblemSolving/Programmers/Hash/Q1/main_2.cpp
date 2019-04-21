#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());
        
    auto i = completion.begin();
    auto j = participant.begin();
    
    for( ; i != completion.end() ; i++, j++)
        if(*i != *j)
            return *j;
}