/*
 * https://www.acmicpc.net/problem/1654
 *
 * 집에서 시간을 보내던 오영식은 박성원의 부름을 받고 급히 달려왔다. 박성원이 캠프 때 쓸 N개의 랜선을 만들어야 하는데 너무 바빠서 영식이에게 도움을 청했다.
 *
 * 이미 오영식은 자체적으로 K개의 랜선을 가지고 있다. 그러나 K개의 랜선은 길이가 제각각이다. 박성원은 랜선을 모두 N개의 같은 길이의 랜선으로 만들고 싶었기 때문에 K개의 랜선을 잘라서 만들어야 한다. 예를 들어 300cm 짜리 랜선에서 140cm 짜리 랜선을 두 개 잘라내면 20cm 은 버려야 한다.(이미 자른 랜선은 붙일 수 없다.)
 *
 * 편의를 위해 랜선을 자르거나 만들 때 손실되는 길이는 없다고 가정하며, 기존의 K개의 랜선으로 N개의 랜선을 만들 수 없는 경우는 없다고 가정하자. 그리고 자를 때는 항상 센티미터 단위로 정수길이만큼 자른다고 가정하자. 이때 만들 수 있는 최대 랜선의 길이를 구하는 프로그램을 작성하시오.
 * */

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
	    int K = 0, N = 0;
	        std::cin >> K >> N;
		    
		    std::vector<long long> item(K);
		        for(auto i = 0 ; i < K ; i++)
				        std::cin >> item[i];

			    long long left = 0, right = __LONG_LONG_MAX__, mid = 0, result = 0;
			        while(left <= right){
					        int temp = 0;

						        mid = (left+right)/2;

							        for(auto i = 0 ; i < K ; i++)
									            temp += item[i] / mid;
								        
								        if(temp < N)
										            right = mid - 1;
									        else{
											            left = mid + 1;
												                if(result < mid)
															                result = mid;
														        }
										    }

				    std::cout << result << std::endl;
}
