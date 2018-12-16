include <bits/stdc++.h>

using namespace std;

// Complete the repeatedString function below.
long repeatedString(string s, long n) {
    long result = 0, count = 0,a_count = 0;

    for(int i = 0 ; i < s.length() ; i++){
        if (s[i] == 'a'){
            count++;
            
            if(i < (n % s.length()))
              a_count++;
        }
    }
    result = (n / s.length() * count) + a_count;
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    long n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    long result = repeatedString(s, n);

    fout << result << "\n";

    fout.close();

    return 0;
}

