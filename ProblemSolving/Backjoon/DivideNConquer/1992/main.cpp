/*
https://www.acmicpc.net/problem/1992

흑백 영상을 압축하여 표현하는 데이터 구조로 쿼드 트리(Quad Tree)라는 방법이 있다. 흰 점을 나타내는 0과 검은 점을 나타내는 1로만 이루어진 영상(2차원 배열)에서 같은 숫자의 점들이 한 곳에 많이 몰려있으면, 쿼드 트리에서는 이를 압축하여 간단히 표현할 수 있다.

주어진 영상이 모두 0으로만 되어 있으면 압축 결과는 "0"이 되고, 모두 1로만 되어 있으면 압축 결과는 "1"이 된다. 만약 0과 1이 섞여 있으면 전체를 한 번에 나타내지를 못하고, 왼쪽 위, 오른쪽 위, 왼쪽 아래, 오른쪽 아래, 이렇게 4개의 영상으로 나누어 압축하게 되며, 이 4개의 영역을 압축한 결과를 차례대로 괄호 안에 묶어서 표현한다
*/

#include <iostream>
#include <string>
#include <vector>

bool check(std::vector<std::vector<int>> &item, int N, int col, int row){
      for(auto i = col ; i < col+N ; i++)
            for(auto j = row ; j < row+N ; j++)
                  if(item[col][row] != item[i][j])
                        return false;
             
      return true;
}

void QuardTree(std::vector<std::vector<int>> &item, int N, int col, int row){
      if(check(item, N, col, row))
            std::cout << item[col][row];
      else{
            std::cout << "(" ;

            int newSize = N >> 1;

            QuardTree(item, newSize, col, row);
            QuardTree(item, newSize, col, row+newSize);
            QuardTree(item, newSize, col+newSize, row);
            QuardTree(item, newSize, col+newSize, row+newSize);

            std::cout << ")" ;
      }
}

int main(){
      int N = 0;
      std::cin >> N;

      std::vector<std::vector<int>> item(N, std::vector<int>(N));

      for (auto i = 0 ; i < N ; i++){
            std::string line;
            std::cin >> line;

            for(auto j = 0 ; j < N ; j++)
                  item[i][j] = line[j] - '0';
      }
      
      QuardTree(item, N, 0, 0);
      std::cout << "\n";
}