#include <bits/stdc++.h>

using namespace std;

// Complete the isValid function below.
string isValid(string s) {
    map<char,int> store;
    map<int,int> count;
    int temp = 0;
    
    for(auto i = 0 ; i < s.length() ; i++)
        store[s[i]]++;
    
    for (auto i = store.begin() ; i != store.end() ; i++)
        count[i->second]++;

    if(count.size() == 1)
        return "YES";
    else if(count.size() == 2){
        map<int,int>::iterator i_1 = count.begin();
        map<int,int>::iterator i_2 = i_1++;

        if(((i_1->first + i_1->second)-2 == 0) || ((i_2->first + i_2->second)-2 == 0))
            return "YES";
        else{
            if(((abs(i_1->first - i_2->first) == 1)) && (((i_1->second != 1)&&(i_2->second == 1) || ((i_1->second == 1)&&(i_2->second != 1) || ((i_1->second == 1)&&(i_2->second == 1))))))
                return "YES";
            else
                return "NO";
        }
    }
    else
        return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}

