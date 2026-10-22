#include <iostream>
#include<unordered_map>
#include<string>

using namespace std;


//friendly version with no bit masking :D will comment out rest of the algo later
string hex_to_bin(string hex){
    unordered_map<char, string>hex_base2 = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}, 
        {'a', "1010"}, {'b', "1011"},
        {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}
    };
    string ans="";
    for(char c: hex){
        ans+= hex_base2[c];
    }
    return ans;
}

int bin_to_dec(string val){
    int ans=0;
    for(int i=val.length()-1; i>=0; i--){
        if(val[i]=='1'){
            ans+= (1<<(val.length()-1-i));
        }
    }
    return ans;
}

int main(){
    string ans="";
    unordered_map<int, string>dec_base64 = {
        {0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}, {4, "E"}, {5, "F"},
        {6, "G"}, {7, "H"}, {8, "I"}, {9, "J"}, {10, "K"}, {11, "L"},
        {12, "M"}, {13, "N"}, {14, "O"}, {15, "P"}, {16, "Q"}, {17, "R"},
        {18, "S"}, {19, "T"}, {20, "U"}, {21, "V"}, {22, "W"}, {23, "X"},
        {24, "Y"}, {25, "Z"}, {26, "a"}, {27, "b"}, {28, "c"}, {29, "d"},
        {30, "e"}, {31, "f"}, {32, "g"}, {33, "h"}, {34, "i"}, {35, "j"},
        {36, "k"}, {37, "l"}, {38, "m"}, {39, "n"}, {40, "o"}, {41, "p"},
        {42, "q"}, {43, "r"}, {44, "s"}, {45, "t"}, {46, "u"}, {47, "v"},
        {48, "w"}, {49, "x"}, {50, "y"}, {51,"z"},{52,"0"},{53,"1"},{54,"2"},
        {55,"3"},{56,"4"},{57,"5"},{58,"6"},{59,"7"},{60,"8"},{61,"9"},{62,"+"},{63,"/"}
    };
    string hex;
    cout<<"Enter the hexadecimal number: ";
    cin>>hex;

    if(hex.length()%2!=0){
        hex= "0"+ hex;
    }

    string hex_in_bin= hex_to_bin(hex);
    for(int i=0; i<hex_in_bin.length(); i+=6){
        string temp="";
        if(i+6>hex_in_bin.length()){
            temp= hex_in_bin.substr(i, hex_in_bin.length()-i);
            while(temp.length()<6){
                temp+="0";
            }
            int dec= bin_to_dec(temp);
            ans+=dec_base64[dec];
            break;
        }else{
            temp= hex_in_bin.substr(i, 6);
        }
        int dec= bin_to_dec(temp);
        ans+=dec_base64[dec];

    }
    if(ans.length()%4!=0){
        while(ans.length()%4!=0){
            ans+="=";
        }
    }
    cout<<"Base64: "<<ans<<endl;

}