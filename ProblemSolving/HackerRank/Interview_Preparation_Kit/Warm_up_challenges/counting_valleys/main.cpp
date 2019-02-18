nclude <bits/stdc++.h>

using namespace std;

// Complete the countingValleys function below.
int countingValleys(int n, string s) {
    stack<int> path;
    int count = 0, level = 0;
    for(int i = 0 ; i < n ; i++){
        switch (s.at(i)){
        case 'U':
            {
                level++;

                if(level <= 0){
                    path.pop();
                    
                    if(path.size() == 0)
                        count++;
                }
            }
            break;
        case 'D':
            {
                level--;

                if(level < 0){
                    path.push(s.at(i));
                }
            }
            break; 
        }
    }

    return count;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    int result = countingValleys(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}

