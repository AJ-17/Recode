
#include <vector>
#include "generator-H.h"

bool isPowerOfTwo(int x) {
    return (x & (x - 1)) == 0;
} 

std::vector<std::vector<bool>>  generate(){
    std::vector<std::vector<bool>> Generator(57,std::vector<bool>(63,0));
    for(int i =0;i<57;i++){
        Generator[i][i]=1;
    }
    int k=0;
    for(int i =1;i<=63;i++){
        if(!isPowerOfTwo(i)){
            for(int j=0;j<6;j++){
                Generator[k][57+j]=(i >> j) & 1;
            }
            k++;
        }
    }
    return Generator;
    }

std::vector<std::vector<bool>> h(){
    
        std::vector<std::vector<bool>> H(6,std::vector<bool>(63,0));
        for(int i =57;i<63;i++){
            H[i-57][i]=1;
        }
        int k=0;
        for(int i =1;i<=63;i++){
            if(!isPowerOfTwo(i)){
                for(int j=0;j<6;j++){
                H[j][k]=(i >> j) & 1;
            }
                
            k++;
            }

        }
        return H;
}