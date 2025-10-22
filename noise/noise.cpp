
#include <iostream> 
#include <vector>
void addnoise(std::vector<bool>&data){
    int ner;
    std::cout<<"Enter a number of error in message  : ";
    std::cin>>ner;
    std::vector<int>BytePos(ner);
    int tc=(data.size()+62)/63;//total combination of 63 bits
    
    std::vector<int> BitNumber(ner);
    std::cout<<"Enter the Byte Numbers where you want errors (1-"<<tc<<") : ";
    char c;

    for(int i=0;i<ner;i++){
        if(i!=ner-1){
        std::cin>>BytePos[i]>>c;
        }
        else{
            std::cin>>BytePos[i];
        }
        
    }


    std::cout<<"Enter the Bit Numbers where you want errors (1-64) : ";

    for(int i=0;i<ner;i++){
        if(i!=ner-1){
        std::cin>>BitNumber[i]>>c;
        }
        else{
            std::cin>>BitNumber[i];
        }    
    }

    for(int i=0;i<ner;i++){
        int bitIndex = (BytePos[i] - 1) * 63 + (BitNumber[i] - 1);
        if (bitIndex >= 0 && bitIndex < (int)data.size()) {
            data[bitIndex] = data[bitIndex] ^ 1;
        }
    }

}