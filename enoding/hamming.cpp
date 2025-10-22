//(63,57) hamming code standard

// Steps how to use : 
/*
    after getting the data in bits form from the huffman encoder 

    Step 1 :  pass that 
*/

#include "hamming.h"
#include <vector>

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
    for(int k=0;k<c2;k++){
        for(int j=0;j<c1;j++){
            result[i][k]=result[i][k]^((a[i][j])*(b[j][k]));
        }
    }
   }

   return result;


}


//this will convert the 57 bits to 63 bits by adding the parity bits
std::vector<bool> conv(std::vector<bool>& w,std::vector<std::vector<bool>> &G ){
        std::vector<std::vector<bool>> send(1,w);
        auto result=mul(send,G);
        return result[0];
}




//now we need make a fnx to break the bits in 57 bit chunks and the reminder will get added to obtain 57 by 0's 

//send the total no of bits in message eg the reminder bits are required 


std::vector<bool> breakcodes(std::vector<bool> data,std::vector<std::vector<bool>> &G){
    int len=data.size();
    int rem=len%57;
    //0's are added now the string data is properly of 57 multiple 
    if(rem!=0){
     data.insert(data.end(), 57 - rem, false);
}
    int ns=data.size()/57;
    std::vector<bool> ret;
    ret.reserve(ns * 64);
    for(int i =0;i<ns;i++)
    {
        //now for every pair of w the loop will run and for every pair we need to store that particular thing
        std::vector<bool> w(data.begin()+i*57,data.begin()+(i+1)*57);
        w=conv(w,G);
        ret.insert(ret.end(),w.begin(),w.end());
    }
    return ret;
}