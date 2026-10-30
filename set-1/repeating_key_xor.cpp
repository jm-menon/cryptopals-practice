#include<iostream>
#include<bitset>
using namespace std;


string ascii_to_binary(string &val){
    string binary_final="";
    for(int i=0; i<val.length(); i++){
        string binary="";
        int letter_numero= static_cast<int>(val[i]);
        //cout<<val[i]<<" , "<<letter_numero<<"\n";
        for(int j=7; j>=0; j--){
            binary+= ((letter_numero>>j)&1)?'1':'0';
        }
        binary_final+=binary;
    }
    return binary_final;
}


string binary_hex(string &binary) {
    string hex = "";
    for (int i = 0; i < binary.length(); i += 4) {
        int val = 0;

        for (int j = 0; j < 4; j++) {
            val = (val << 1) | (binary[i + j] - '0');
        }
        if (val < 10) {
            hex += (char)(val + '0');
        } else {
            hex += (char)(val - 10 + 'a');
        }
    }

    return hex;
}

string xor_encrypt_binary(string &input, string &key){
    //normalize the key
    //then go on and do xor operation -- now handling only for cases where key is less than the size of input string
    int remaining_letters=0;
    string extra_for_key="", binary_input="", binary_key="";
    if(key.length()< input.length()){
        remaining_letters= input.length() - key.length();
        int p1= remaining_letters/key.length();
        int p2= remaining_letters%key.length();
        for(int i=0; i<p1; i++)
            extra_for_key+=key;
        extra_for_key+=key.substr(0, p2);
        key=key+extra_for_key;
    }
    binary_input= ascii_to_binary(input);
    binary_key= ascii_to_binary(key);
    string result;

    // XOR each byte of b1 with the corresponding repeating byte of b2
    for (size_t i = 0; i < binary_input.size(); i += 8) {
        //size_t key_pos = (i / 8 * 8) % key.size();

        bitset<8> byte1(binary_input.substr(i, 8));
        bitset<8> byte2(binary_key.substr(i, 8));

        result += (byte1 ^ byte2).to_string();
    }

    return result;


}

/* AI GENERATED ONE: string xor_encrypt_binary(string &input, string &key) {

    string binary_input = ascii_to_binary(input);
    string binary_key = ascii_to_binary(key);

    string result;

    for (size_t i = 0; i < binary_input.size(); i += 8) {

        size_t key_pos = (i / 8) % key.length();

        bitset<8> byte1(binary_input.substr(i, 8));
        bitset<8> byte2(binary_key.substr(key_pos * 8, 8));

        result += (byte1 ^ byte2).to_string();
    }

    return result;
}*/


int main(){
    string input, key;
    //int rounds;
    cout<<"\nEnter your plain text: ";
    getline(cin, input);
    //cout<<input<<"\n";
    cout<<"\nEnter your key to carry out the encoding with: ";
    cin>>key;
    string binary_input= ascii_to_binary(input);
    string binary_key= ascii_to_binary(key);
    //cout<<"\nThe plaintext is: "<<binary_input<<"\n"<<"The key is: "<<binary_key;
    string binary= xor_encrypt_binary(input, key);
    //cout<<"\nthe value after encrypting: "<<binary;
    cout<<"\nHexadecimal value: "<<binary_hex(binary);
    return 0;
}