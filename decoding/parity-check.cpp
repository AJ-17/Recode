
//we already have H matrix, the 63 bits message 
// now the vector of bits we have now we need to check every 63 bits form start 
#include "parity-check.h"
#include <vector>
#include <iostream>

//so lets find S=H*cT  where c is the recieved messaege transpose if s =0 then no error if dosen't matched then error is there there if s match any column of H then the no of column = the posiiton of bit where error is there if (no)/(more then 1) column found in H then the error is not fixiable 

std::vector<std::vector<bool>> mul(std::vector<std::vector<bool>>& a,std::vector<std::vector<bool>>& b){
    int r1=a.size();
    int c1;
    if(r1!=0){
        c1=a[0].size();
    }

    int r2=b.size();
    int c2;
    if(r2!=0){
        c2=b[0].size();
    }

    // [r1,c1][r2,c2] c1=r2


    std::vector<std::vector<bool>> result(r1,std::vector<bool>(c2,0));

    //i row 1
    //j col 1 ,row 2 
    //k col 2

   for(int i=0;i<r1;i++){
    for(int j=0;j<c1;j++){
       result[i][0]=( result[i][0])^(a[i][j]*b[j][0]);
    }
   }

   return result;


}

std::vector<std::vector<bool>> findS(std::vector<std::vector<bool>> &H,std::vector<bool> &c){
    std::vector<std::vector<bool>> r(c.size(),std::vector<bool>(1,0));
    for(int i =0;i<c.size();i++){
        r[i][0]=c[i];
    }

    return mul(H,r);
}


void fix(std::vector<std::vector<bool>> &H,std::vector<std::vector<bool>> &s,std::vector<bool> &c){
    
    int f=0;
    int index=-1;
    for(int i=0;i<H[0].size();i++){
        f=0;
        for(int j=0;j<H.size();j++){
            if(H[j][i]!=s[j][0]){
                f=1;
                break;
            }
        }
        if(f==0){
            index=i;
            
        }       
    }
    if(index!=-1){  
        c[index]=c[index]^1;
        std::vector<std::vector<bool>> v = findS(H,c);
        s=v;
} 
}

bool errdet(std::vector<std::vector<bool>> &H,std::vector<bool> &c){
    std::vector<std::vector<bool>> s=findS(H,c);
    //now the only this is that id there is a single error then we need to fix it 
    for(auto i:s){
        if(i[0]!=0)
        {   
            fix(H,s,c);
            break;
        }
    }
    
    

    return 0;//0 means no error detected 
}
