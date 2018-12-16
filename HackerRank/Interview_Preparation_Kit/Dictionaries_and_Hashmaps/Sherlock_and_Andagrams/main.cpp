#include <bits/stdc++.h>

using namespace std;

// nC2 calculate
int nC2(int n){
    int fec = 1;
   
    for(int i=(n-1) ; i<=n ; i++)
        fec *= i;

    return fec/2;
}

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {
    int result = 0;
    map<string,int>store;
    map<string,int>::iterator iter;

    for(int i = 0 ; i < s.length() ; i++){
        for(int j = 1 ; j <= s.length() - i ; j++){
            string tmp = s.substr(i,j);
            sort(tmp.begin(),tmp.end());
            store[tmp]++;
        }
    }

    for(iter = store.begin() ; iter != store.end() ; iter++)
        if(iter->second > 1)
            result += nC2(iter->second);

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);
        
        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
