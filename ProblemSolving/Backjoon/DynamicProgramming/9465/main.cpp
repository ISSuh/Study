#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int T = 0;

    std::cin >> T;

    for(auto t = 0 ; t < T ; t++){
        int n = 0, max = 0;
        std::cin >> n;

        std::vector<std::vector<int>> item(2,std::vector<int>(n));
        std::vector<std::vector<int>> val(2,std::vector<int>(n+1));
        
        for (auto i = 0; i < 2; i++)
			for (auto j = 0; j < n; j++)
				std::cin >> item[i][j];

        val[0][0] = 0;          val[1][0] = 0;
        val[0][1] = item[0][0]; val[1][1] = item[1][0];

        for(auto i=2 ; i<n+1; i++){
            for(auto j=0 ; j<2 ; j++){
                
                val[j][i] = item[j][i-1] + std::max({val[!j][i-1],val[!j][i-2],val[j][i-2]});

            }
        }

        std::cout << std::max(val[0][n],val[1][n]) << std::endl;
    }
}

