#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    map<string, int> temp;
    
    for(auto i = participant.begin() ; i != participant.end() ; i++)
        temp[*i]++;
    
    for(auto i = completion.begin() ; i != completion.end() ; i++)
        temp[*i]--;
    
    for(auto i = temp.begin() ; i != temp.end() ; i++)
        if(i->second)
            return i->first;
}