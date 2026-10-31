#include<iostream>
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

int hamming_distance(string &b1, string &b2){
    int ans=0;
    for(int i=0; i<b1.length(); i++)
        if(b1[i]!=b2[i])
            ans++;
    
    return ans;
}

int main(){
    string s1="", s2="";
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
    return 0;
}