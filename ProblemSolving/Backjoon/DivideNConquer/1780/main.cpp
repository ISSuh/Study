/*
 * https://www.acmicpc.net/problem/1780
 *
 * N×N크기의 행렬로 표현되는 종이가 있다. 종이의 각 칸에는 -1, 0, 1의 세 값 중 하나가 저장되어 있다. 우리는 이 행렬을 적절한 크기로 자르려고 하는데, 이때 다음의 규칙에 따라 자르려고 한다.
 *
 *     만약 종이가 모두 같은 수로 되어 있다면 이 종이를 그대로 사용한다.
 *         (1)이 아닌 경우에는 종이를 같은 크기의 9개의 종이로 자르고, 각각의 잘린 종이에 대해서 (1)의 과정을 반복한다.
 *
 *         이와 같이 종이를 잘랐을 때, -1로만 채워진 종이의 개수, 0으로만 채워진 종이의 개수, 1로만 채워진 종이의 개수를 구해내는 프로그램을 작성하시오.
 *
 *         */

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

std::map<int,int> ans;

bool check(int row, int colum, int size, std::vector<std::vector<int>> &item){
	    for(auto i = row ; i < row+size ; i++)
		            for(auto j = colum ; j < colum+size ; j++)
				                if(item[row][colum] != item[i][j])
							                return false;
	            
	        return true;
}

void divide(int row, int colum, int size, std::vector<std::vector<int>> &item){
	    if(check(row, colum, size, item))
		            ans[item[row][colum]]++;
	        else{
			        int divideSize = size / 3;
				        for(auto i = 0 ; i < 3 ; i++){
						            for(auto j = 0 ; j < 3 ; j++){
								                    divide(row+(divideSize*i), colum+(divideSize*j), divideSize,item);
										                }
							            }
					    }
}

int main(){
	    int N = 0;

	        std::cin >> N;

		    std::vector<std::vector<int>> item(N,std::vector<int>(N));
		        for(auto i = 0 ; i < N ; i++)
				        for(auto j = 0 ; j < N ; j++)
						            std::cin >> item[i][j];

			    divide(0,0,N,item);
			         
			        std::cout << ans[-1] << "\n";
				    std::cout << ans[0] << "\n";
				        std::cout << ans[1] << "\n";

}
