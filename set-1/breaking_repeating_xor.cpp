#include<iostream>
#include <fstream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<unordered_set>
#include<bitset>

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

vector<string> transpose_blocks(string &content, int keysize){
    vector<string> blocks(keysize);
    for(int i=0; i<keysize; i++){
        for(size_t j = i*8; j + 8 <= content.length(); j += keysize*8)
        blocks[i] += content.substr(j, 8);

        //cout<<"\nBlock: "<<i+1<<": "<<blocks[i];
    }
    return blocks;
}

bool is_printable_text(const string& text) {
    if (text.empty()) return false;

    for (unsigned char c : text) {
        if ((c < 32 || c > 126) &&
            c != '\n' && c != '\r' && c != '\t') {
            return false;
        }
    }

    return true;
}

string toLowerCase(string text) {
    for (char& c : text) {
        c = static_cast<char>(
            tolower(static_cast<unsigned char>(c))
        );
    }

    return text;
}

double scoreEnglish(const string& text) {

    if (text.empty()) {
        return -1000.0;
    }

    double score = 0.0;
    int letters = 0;
    int vowels = 0;
    int printable = 0;
    int spaces = 0;

    // Common English words.
    // This is deliberately a small starter dictionary.
    static const unordered_set<string> commonWords = {
        "the", "be", "to", "of", "and", "a", "in", "that",
        "have", "i", "it", "for", "not", "on", "with", "he",
        "as", "you", "do", "at", "this", "but", "his", "by",
        "from", "they", "we", "say", "her", "she", "or", "an",
        "will", "my", "one", "all", "would", "there", "their",
        "is", "are", "was", "were", "like", "cooking", "bacon"
    };

    // Common English letter sequences.
    static const vector<string> commonBigrams = {
        "th", "he", "in", "er", "an", "re", "on",
        "at", "en", "nd", "ti", "es", "or", "te",
        "of", "ed", "is", "it", "al", "ar", "st"
    };

    // Examine individual characters.
    for (unsigned char c : text) {
        if (isprint(c)) {
            printable++;
        } else {
            // Control characters are unlikely in ordinary English.
            score -= 15.0;
            continue;
        }

        if (isalpha(c)) {
            letters++;

            char lower = static_cast<char>(tolower(c));

            if (lower == 'a' || lower == 'e' ||
                lower == 'i' || lower == 'o' ||
                lower == 'u') {
                vowels++;
            }

            // English text uses these letters relatively often.
            if (lower == 'e' || lower == 't' ||
                lower == 'a' || lower == 'o' ||
                lower == 'i' || lower == 'n') {
                score += 0.5;
            }
        } else if (isspace(c)) {
            spaces++;
            score += 1.0;
        } else if (isdigit(c)) {
            // Numbers can be legitimate, but long strings of
            // random digits are less typical of ordinary prose.
            score -= 0.2;
        } else if (ispunct(c)) {
            // Ordinary punctuation is acceptable.
            score += 0.1;
        } else {
            // Penalize unusual printable symbols.
            score -= 2.0;
        }
    }

    // Strongly penalize text containing non-printable bytes.
    score -= (text.size() - printable) * 5.0;

    // Reward a reasonable proportion of letters and spaces.
    if (!text.empty()) {
        double letterRatio =
            static_cast<double>(letters) / text.size();

        double spaceRatio =
            static_cast<double>(spaces) / text.size();

        if (letterRatio > 0.45 && letterRatio < 0.90) {
            score += 5.0;
        }

        if (spaceRatio > 0.08 && spaceRatio < 0.30) {
            score += 5.0;
        }
    }

    // English text usually has vowels in roughly 30-45% of
    // its letters. This is a broad heuristic, not a strict rule.
    if (letters > 0) {
        double vowelRatio =
            static_cast<double>(vowels) / letters;

        if (vowelRatio >= 0.25 && vowelRatio <= 0.50) {
            score += 5.0;
        } else {
            score -= 3.0;
        }
    }

    // Reward common two-letter English sequences.
    string lowerText = toLowerCase(text);

    for (const string& bigram : commonBigrams) {
        size_t pos = 0;

        while ((pos = lowerText.find(bigram, pos))
               != string::npos) {
            score += 1.0;
            pos += 1;
        }
    }

    // Split the text into words and check for common words.
    string word;

    for (size_t i = 0; i <= lowerText.size(); i++) {
        // Treat non-letter characters as word boundaries.
        char c = (i < lowerText.size()) ? lowerText[i] : ' ';

        if (isalpha(static_cast<unsigned char>(c))) {
            word += c;
        } else {
            if (!word.empty()) {
                if (commonWords.count(word)) {
                    score += 5.0;
                }

                // Extremely long unbroken words are less common.
                if (word.size() > 15) {
                    score -= 2.0;
                }

                word.clear();
            }
        }
    }

    return score;
}

int main(){
    
    ifstream file("input_breaking_repeating_xor.txt");  
    if (!file.is_open()) {
        cerr << "Error: Could not open the file!\n";
        return 1;
    }
    string content((istreambuf_iterator<char>(file)),
                         istreambuf_iterator<char>());

    unordered_map<int, float> keysize_hamming_length;
    vector<float> candidate_keysizes;
    vector<pair<int, float>> keysize_hl_pairs;
    
    string bits = base64_to_bin(content);

    for(int ks = 2; ks <= 40; ks++){
        float total = 0; int pairs = 0;
        for(int b = 0; (b+2)*ks*8 <= bits.size() && b < 10; b++){
            string x = bits.substr(b*ks*8,     ks*8);
            string y = bits.substr((b+1)*ks*8, ks*8);
            total += hamming_distance(x, y) / ks;
            pairs++;
        }
        keysize_hamming_length[ks] = total / pairs;
    }

    keysize_hl_pairs= ranked(keysize_hamming_length);
    //sort(keysize_hl.begin(), keysize_hl.end());

    string binary_content= base64_to_bin(content);

    vector<string> blocks= transpose_blocks(binary_content, keysize_hl_pairs[0].first);
    cout<<"\nKeysize: "<<keysize_hl_pairs[0].first;

    //the best key for each block
    string best_key="";
    int problematic_blocks=0;
    for(int i=0; i<blocks.size(); i++){
        unordered_map<int, string>keys_texts;
        vector<pair<int, double>> scores;
        bool all_blocks_printable=false;
        string decrypted_binary= binary_to_ascii(blocks[i]);

        for(int k=0; k<256; k++){
        string potential_key= decimal_to_binary(k, 8); 
        string binary_output= xor_binary_strings(blocks[i], potential_key);
        string decrypted_text= binary_to_ascii(binary_output);

        if(is_printable_text(decrypted_text)){
            //cout<<"\nKey: "<<k<<" Decrypted text: "<<decrypted_text<<" for block: "<<i+1;
            scores.push_back({k, scoreEnglish(decrypted_text)});
            keys_texts[k] = decrypted_text;
            all_blocks_printable=true;
        }
        else{
            //cout<<"\nBlock number: "<<i<<" the key was not printable!!!!!!!!!!";
            continue;
        }
        }
        sort(scores.begin(), scores.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
        return a.second > b.second;
            });
       
        //best_key+= keys_texts[scores[0].first];
        best_key += (char)scores[0].first;
        cout<<"\n\n\nBest key for block "<<i+1<<": "<<scores[0].first<<" Key so far: "<<best_key;
        if(!all_blocks_printable){
            cout<<"\n\n\nBlock number: "<<i<<" the key was not printable!!!!!!!!!!";
            problematic_blocks++;
        }

    }
    cout<<"\nNumber of problematic blocks: "<<problematic_blocks;
    cout<<"\nKey size finally: "<<best_key.length()<<" Key: "<<best_key;

    //actual decryption:
    string plaintext;
for(size_t j = 0, idx = 0; j + 8 <= binary_content.size(); j += 8, idx++){
    int byte = stoi(binary_content.substr(j, 8), nullptr, 2);
    plaintext += (char)(byte ^ (unsigned char)best_key[idx % best_key.size()]);
}
cout <<"\n\n-----------------------------\n\n"<< plaintext << "\n";

    return 0;
}