#include<iostream>
#include<unordered_map>
using namespace std;

//mostly correct but with an overflow problem

long long hex_binary(string hex){
    long long binary=0;
    unordered_map<char, int>hex_base2 = {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3},
        {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
        {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11},
        {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15},
        {'a', 10}, {'b', 11},
        {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}
    };
    for(int i=0; i<hex.length(); i++){
        binary= (binary<<4) + hex_base2[hex[i]];
    }
    return binary;
}

int len_binary(long long binary){
    int len=0;
    while(binary>0){
        len++;
        binary>>=1;
    }
    return len;
}

string binary_hex(long long binary){
    string hex="";
    int start= ((len_binary(binary)-1)/4)*4;
    for(int i=start; i>=0; i-=4){ //can be avoided if i start from pos 0 and go to len_binary(binary) but then the hex will be reversed
        int val= (binary>>i) & 0xF;
        if(val<10){
            hex+= (char)(val+'0');
        }else{
            hex+= (char)(val-10+'A');
        }
    }
    return hex;
}

int main(){
    string hex1, hex2;
    //entering the hexas
    cout<<"Enter hex1: ";
    cin>>hex1;
    cout<<"\nEnter hex2: ";
    cin>>hex2;

    //hexa to binary conversion
    long long bin1= hex_binary(hex1);
    long long bin2= hex_binary(hex2);
    string ans= binary_hex(bin1 ^ bin2);

    //answer
    cout<<"XOR: "<<ans<<endl;    
    return 0;
}