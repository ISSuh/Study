nclude <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the freqQuery function below.
vector<int> freqQuery(vector<vector<int>> queries) {
    vector<int> result;
    vector<vector<int>>::iterator x;
    vector<int>::iterator y;
    map<int,int> counting;
    map<int,int> temp;
    map<int,int>::iterator i;

    for(x = queries.begin() ; x != queries.end() ; x++){
        y = x->begin();
        
        switch(*y){
            case 1:
                y++;

                temp[counting[*y]]--;
                if (temp[counting[*y]] < 0)
                  temp[counting[*y]] = 0;

                counting[*y]++;
                temp[counting[*y]]++;
                
                break;
            case 2:
                y++;

                temp[counting[*y]]--;
                counting[*y]--;
                temp[counting[*y]]++;
                
                if (temp[counting[*y]+1] < 0)
                    temp[counting[*y]+1] = 0;
                
                if (counting[*y] < 0)
                    counting[*y] = 0;

                break;
            case 3:
                y++;

                if(temp[*y] > 0)
                    result.push_back(1);
                else
                    result.push_back(0);
              break;
        }
    }
    return result; 
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    vector<vector<int>> queries(q);

    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int queries_row_item = stoi(queries_row_temp[j]);

            queries[i][j] = queries_row_item;
        }
    }

    vector<int> ans = freqQuery(queries);

    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i];

        if (i != ans.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

