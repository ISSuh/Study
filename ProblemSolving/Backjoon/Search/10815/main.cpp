/*
 * https://www.acmicpc.net/problem/10815
 *
 * 숫자 카드는 정수 하나가 적혀져 있는 카드이다. 상근이는 숫자 카드 N개를 가지고 있다. 정수 M개가 주어졌을 때, 이 수가 적혀있는 숫자 카드를 상근이가 가지고 있는지 아닌지를 구하는 프로그램을 작성하시오.
 * */

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
	    int N = 0,M = 0;
	        std::cin >> N;
		    
		    std::vector<long> item(N);
		        for(auto i = 0 ; i < N ; i++)
				        std::cin >> item[i];

			    std::sort(item.begin(),item.end());

			        std::cin >> M;
				    std::vector<long> findItem(M);
				        for(auto i = 0 ; i < M ; i++)
						        std::cin >> findItem[i];

					    for(auto i = 0 ; i < M ; i++)
						            std::cout << (std::binary_search(item.begin(), item.end(), findItem[i]) ? 1 : 0) << " ";    
					        
					        std::cout << "\n";
}
