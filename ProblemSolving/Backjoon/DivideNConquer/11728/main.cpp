/*
 * https://www.acmicpc.net/problem/11728
 *
 * 정렬되어있는 두 배열 A와 B가 주어진다. 두 배열을 합친 다음 정렬해서 출력하는 프로그램을 작성하시오.
 * */

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main(){
	    int N = 0,M = 0;
	        int i = 0, j = 0, k = 0;
		    
		    std::cin >> N >> M;

		        std::vector<int> A(N), B(M), result(N+M);

			    for(auto i = A.begin() ; i != A.end() ; i++)
				            std::cin >> *i;

			        for(auto i = B.begin() ; i != B.end() ; i++)
					        std::cin >> *i;

				    while(i < N && j < M){
					            if(A[i] < B[j])
							                result[k++] = A[i++];
						            else
								                result[k++] = B[j++];
							        }

				        if(i < N)
						        for(auto idx = i ; idx < N ; idx++)
								            result[k++] = A[idx];
					    else
						            for(auto idx = j ; idx < M ; idx++)
								                result[k++] = B[idx];
					        
					        for(auto i = result.begin() ; i != result.end() ; i++)
							        std::cout << *i << " ";

						    std::cout << "\n";
}
