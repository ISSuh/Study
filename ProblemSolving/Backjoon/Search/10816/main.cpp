/*
 * https://www.acmicpc.net/problem/10816
 *
 * 숫자 카드는 정수 하나가 적혀져 있는 카드이다. 상근이는 숫자 카드 N개를 가지고 있다. 정수 M개가 주어졌을 때, 이 수가 적혀있는 숫자 카드를 상근이가 몇 개 가지고 있는지 구하는 프로그램을 작성하시오.
 * */

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main(){
	    int N = 0,M = 0;
	        
	        std::cin >> N;

		    std::vector<int> item(N);
		        for(auto i = 0 ; i < N ; i++)
				        std::cin >> item[i];

			    std::cin >> M;
			        
			        std::vector<int> findItem(M);
				    for(auto i = 0 ; i < M ; i++)
					            std::cin >> findItem[i];

				        std::map<int,int> count;
					    std::vector<int> sortedFindItem = findItem;

					        std::sort(sortedFindItem.begin(),sortedFindItem.end());

						    for(auto i = item.begin() ; i != item.end() ; i++)
							            if(std::binary_search(sortedFindItem.begin(),sortedFindItem.end(),*i))
									                count[*i]++;

						        for(auto i = findItem.begin() ; i != findItem.end() ; i++)
								        std::cout << count[*i] << " ";
							    

							    std::cout << "\n";
}
