#include<iostream>
#include <string>
#include <bitset>
#include<vector>

using namespace std;

string hex_to_binary(string hex_string){
    //cout<<"\nThe hex string is: "<<hex_string<<"\n";
    unordered_map<char, string>hex_base2 = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}, 
        {'a', "1010"}, {'b', "1011"},
        {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}
    };
    string ans="";
    for(char c: hex_string){
        ans+= hex_base2[c];
    }
    //cout<<"\nThe binary string is: "<<ans<<"\n";
    return ans;
}

string binary_to_ascii(string binary_string) {
    string final_ans;
    for (int i = 0; i < binary_string.length(); i += 8) {
        int ans = 0;
        for (int j = i; j < i + 8 && j < binary_string.length(); j++) {
            if (binary_string[j] == '1') {
                ans += (1 << (7 - (j - i)));
            }
        }
        //cout<<"Ans is: "<<ans<<"\n";
        final_ans += static_cast<char>(ans);
    }
    return final_ans;
}

string decimal_to_binary(int decimal, int length){
    string binary="";
    for(int i=length-1; i>=0; i--){
        binary+= ((decimal>>i) & 1) ? '1' : '0';
    }
    return binary;
}

string xor_binary_strings(const string& b1, const string& b2) {
    // Pad b2 to a whole number of bytes
    size_t b2_len = ((b2.size() + 7) / 8) * 8;
    string key = string(b2_len - b2.size(), '0') + b2;

    string result;

    // XOR each byte of b1 with the corresponding repeating byte of b2
    for (size_t i = 0; i < b1.size(); i += 8) {
        size_t key_pos = (i / 8 * 8) % key.size();

        bitset<8> byte1(b1.substr(i, 8));
        bitset<8> byte2(key.substr(key_pos, 8));

        result += (byte1 ^ byte2).to_string();
    }

    return result;
}

int main(){
    cout<<"\nEnter the 60 hex string to decrypt: ";
    string hex_string;
    do{
        
        cin>>hex_string;
        //hex_strings.push_back(hex_string);
         string hex_binary= hex_to_binary(hex_string);
        string decrypted_binary= binary_to_ascii(hex_binary); 
        string decrypted_text= "";
        for(int i=0; i<256; i++){
        string potential_key= decimal_to_binary(i, 8); 
        string binary_output= xor_binary_strings(hex_binary, potential_key);
        decrypted_text= binary_to_ascii(binary_output);
        cout<<"\nKey: "<<i<<" Decrypted text: "<<decrypted_text;
        for(int j=0; j<decrypted_text.length(); j++){
            if(decrypted_text[j]<32 || decrypted_text[j]>126){
                break;
            }
        }
        cout<<"\nKey: "<<i<<" for encrypted text no: "<<I<<" Decrypted text: "<<decrypted_text;
        }
        
cout<<"\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    }while(hex_string!="0");
   
    return 0;
}