#include<iostream>
#include <fstream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

string decimal_to_binary(int decimal, int length){
    string binary="";
    for(int i=length-1; i>=0; i--){
        binary+= ((decimal>>i) & 1) ? '1' : '0';
    }
    return binary;
}

string string_to_binary(string &s){
    string binary="";
    for(int i=0; i<s.length(); i++){
        binary+= decimal_to_binary(static_cast<int>(s[i]), 8);
    }
    return binary;
}

float hamming_distance(string &b1, string &b2){
    int ans=0;
    for(int i=0; i<b1.length(); i++)
        if(b1[i]!=b2[i])
            ans++;
    
    return ans;
}

string hex_to_bin(string &hex){
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


vector<pair<int, float>> ranked(unordered_map<int, float> &keysize_hamming_length){
    vector<pair<int, float>> keysize_hl_pairs;
    for(auto var: keysize_hamming_length){
        keysize_hl_pairs.push_back({var.first, var.second});
    }
    sort(keysize_hl_pairs.begin(), keysize_hl_pairs.end(), [](const pair<int, float> &a, const pair<int, float> &b) {
        return a.second < b.second; // Sort in ascending order based on the second element (value)
    });
    return keysize_hl_pairs;
}

int main(){
    /*string s1="", s2="";
    cout<<"\nSentance 1: ";
    getline(cin, s1);
    //cin>>s1;
    cout<<"\nSentance 2: ";
    //cin>>s2;
    getline(cin, s2);
    string b1=string_to_binary(s1), b2= string_to_binary(s2);
    cout<<"\nFor string: "<<s1<<"\nbinary equivalent is "<<b1;
    cout<<"\nFor string: "<<s2<<"\nbinary equivalent is "<<b2;
    cout<<"\nThe hamming distance: "<<hamming_distance(b1, b2);
    string ans;
    cout<<"\nEnter the string please: ";
    getline(cin, ans);
    cout<<ans.length();*/
    
    ifstream file("input_breaking_repeating_xor.txt");  
    if (!file.is_open()) {
        cerr << "Error: Could not open the file!\n";
        return 1;
    }
    string content((istreambuf_iterator<char>(file)),
                         istreambuf_iterator<char>());

    //cout << "File content:\n" << content << endl;

    unordered_map<int, float> keysize_hamming_length;
    vector<float> keysize_hl, candidate_keysizes;
    vector<pair<int, float>> keysize_hl_pairs;
    
    for(int keysize=2; keysize<=100; keysize++){
        //1byte is 2 hexadecimal digits
        string block1= content.substr(0, keysize*2), block2= content.substr(keysize*2, 2*keysize);
        //cout<<"\nvalue of b1: "<<block1<<" , "<<" value of b2: "<<block2;
        string binary1= hex_to_bin(block1), binary2= hex_to_bin(block2);
        float value= hamming_distance(binary1, binary2)/keysize;
        keysize_hamming_length[keysize]= value;
        keysize_hl.push_back(value);
    }

    keysize_hl_pairs= ranked(keysize_hamming_length);

    sort(keysize_hl.begin(), keysize_hl.end());

    int top=3;
    for(auto var: keysize_hl_pairs){
        //if(top<0)
            //break;
        cout<<"\nThe keys with the shortest hamming length: "<<var.first<<" with length "<<var.second;
        if(top>0){
        candidate_keysizes.push_back(var.first);
        top--;}
            //cout<<"\nThe keys with the shortest hamming length: "<<var.first<<" with length "<<var.second;
        }
    cout<<"\nSELECTED KEY CANDIDATE SIZES FOR RUPTURE.....";
    for(int i=0; i<candidate_keysizes.size(); i++)
        cout<<"\n"<<candidate_keysizes[i];

    return 0;
}