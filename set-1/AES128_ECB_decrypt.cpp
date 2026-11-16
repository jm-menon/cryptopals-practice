#include<iostream>
#include<fstream>

using namespace std;

string decimal_to_binary(int decimal, int length){
    string binary="";
    for(int i=length-1; i>=0; i--){
        binary+= ((decimal>>i) & 1) ? '1' : '0';
    }
    return binary;
}

string base64_to_bin(string &base64){
    unordered_map<char, int>dec_base64 = {
        {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5},
        {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11},
        {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17},
        {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23},
        {'Y', 24}, {'Z', 25}, {'a', 26}, {'b', 27}, {'c', 28}, {'d', 29},
        {'e', 30}, {'f', 31}, {'g', 32}, {'h', 33}, {'i', 34}, {'j', 35},
        {'k', 36}, {'l', 37}, {'m', 38}, {'n', 39}, {'o', 40}, {'p', 41},
        {'q', 42}, {'r', 43}, {'s', 44}, {'t', 45}, {'u', 46}, {'v', 47},
        {'w', 48}, {'x', 49}, {'y', 50}, {'z', 51},{'0',52},{'1',53},{'2',54},
        {'3',55},{'4',56},{'5',57},{'6',58},{'7',59},{'8',60},{'9',61},{'+',62},{'/',63}
    };
    cout<<dec_base64['A']<<"\n";
    string ans="";
    for(char c: base64){
        if(dec_base64.find(c) == dec_base64.end())
            continue;
        ans+=decimal_to_binary(dec_base64[c], 6);
    }
    if(base64[base64.length()-1]=='=')
        ans= ans.substr(0, ans.length()-2);
    if(base64[base64.length()-2]=='=')
        ans= ans.substr(0, ans.length()-4);
    return ans;
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

string block_aes_128_ecb(string &binary_input, string &binary_key){
    // Implement AES-128 ECB encryption here
    // This is a placeholder function and needs to be implemented
    return "";
}

string s_box_substitution(string &binary_input){
    // Implement S-box substitution for AES here
    // This is a placeholder function and needs to be implemented
    return "";
}

string key_expansion(string &binary_key, string &previous_round_key){
    // Implement key expansion for AES-128 here
    // This is a placeholder function and needs to be implemented
    return "";
}

int main(){
    ifstream file("AES128_ECB_cipher.txt");
    if(!file.is_open()){
        cerr<<"Error: Could not open the file!\n";
        return 1;
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    //file.close();
    cout << "Base64 content: " << content << endl;
    string binary_cipher = base64_to_bin(content);
    cout << "Binary representation: " << binary_cipher << endl;

    string key;
    cout << "Enter the key (16 characters for AES-128): ";
    cin >> key;
    string binary_key;
    for(int i=0; i<key.length(); i++){
       binary_key+= decimal_to_binary(static_cast<int>(key[i]), 8);
    }
    //string binary_key= decimal_to_binary(static_cast<int>(key[0]), 8); // Convert the first character of the key to binary
    cout << "\nBinary representation of the key: " << binary_key << endl;

    string binary_input= base64_to_bin(content);
    cout << "\nBinary representation of the input: " << binary_input << endl;
    cout<<"\nLength of the bits: "<<binary_input.length()<<"\nNumber of bytes is: "<<binary_input.length()/8<<"\n";

    float is_16bytes=(binary_input.length()/8.0)/16.0;
    cout<<"\nIs the input a multiple of 16 bytes? "<<is_16bytes<<"\n";

    //since the is_16bytes is not a whole number, we need to pad the input with extra 10 bytes (80 bits) to make it a multiple of 16 bytes
    //just going with this specific case for now:
    for(int i=0; i<16; i++)
        binary_input+= "00010000";
    

        string final_encryption="";
    //cutting into 16byte blocks:
    for(int i=0; i<binary_input.length(); i+=128){
        //cout<<"\nBlock "<<i/128+1<<": "<<binary_input.substr(i, 128)<<"\n";
        string block_to_encrypt= binary_input.substr(i, 128);
        string round_key= "";
        if(i==0)
            round_key= key_expansion(binary_key, binary_key);
        else
            round_key= key_expansion(binary_key, round_key);

        final_encryption+= block_aes_128_ecb(block_to_encrypt, round_key);

    }
    cout << "Final encrypted output (in binary): " << final_encryption << endl;


    //AES 128 ECB encryption
    //convert the hexadecimal plaintext into a binary byte split (done)
    //xor function is also needed (done)
    //padding the plaintext with extra 10 bytes (done)

    return 0;
}