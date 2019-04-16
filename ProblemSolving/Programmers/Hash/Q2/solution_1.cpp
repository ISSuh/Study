#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;

    vector<vector<string>> temp(10);

    for(auto i = 0 ; i < phone_book.size() ; i++){
        int index = phone_book[i][0] - '0';
        temp[index].push_back(phone_book[i]);

        for(auto j = 0 ; j < temp[index].size() - 1 ; j++){
            if (temp[index][j].compare(0, temp[index][temp[index].size() - 1].size(), temp[index][temp[index].size() - 1]) == 0)
				return false;			
			else if (temp[index][temp[index].size() - 1].compare(0, temp[index][j].size(), temp[index][j]) == 0)
				return false;	
        }
    }

    return answer;
}

int main(){
    int N =0;
    cin >> N;
    
    vector<string> book;

    while(N--){
        string temp;
        cin >> temp;

        book.push_back(temp);
    }

    bool val = solution(book);

    cout << val << '\n';
}