#include <bits/stdc++.h>

using namespace std;

// Complete the makeAnagram function below.
int makeAnagram(string a, string b) {
    int result = 0;
    map<char,int> store;

    for(auto i = 0 ; i < a.length() ; i++)
        store[a[i]]++;
    for(auto i = 0 ; i < b.length() ; i++)
        store[b[i]]--;
    
    for(auto i = store.begin() ; i != store.end() ; i++)
        result += abs(i->second);
    
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a;
    getline(cin, a);

    string b;
    getline(cin, b);

    int res = makeAnagram(a, b);

    fout << res << "\n";

    fout.close();

    return 0;
}

