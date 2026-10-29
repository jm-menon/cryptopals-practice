#include<iostream>
#include <string>
#include <bitset>
#include <unordered_set>
#include <vector>

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

bool is_printable_text(const string& text) {
    if (text.empty()) return false;

    for (unsigned char c : text) {
        if (c < 32 || c > 126) {
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
    string hex_string;
    unordered_map<int, string>keys_texts;
    //vector<pair<int, string>> candidates; // Store key and decrypted text pairs
    vector<pair<int, double>> scores; // Store key and score pairs
    cout<<"\nEnter hex string to decrypt: ";
    cin>>hex_string;
    string hex_binary= hex_to_binary(hex_string);
    string decrypted_binary= binary_to_ascii(hex_binary); 
    cout<<"\nDecrypted text: "<<decrypted_binary;
    for(int i=0; i<256; i++){
        string potential_key= decimal_to_binary(i, 8); 
        string binary_output= xor_binary_strings(hex_binary, potential_key);
        string decrypted_text= binary_to_ascii(binary_output);
        if(is_printable_text(decrypted_text)){
            scores.push_back({i, scoreEnglish(decrypted_text)});
            keys_texts[i] = decrypted_text;
        }
        else
            {//cout<<"\nKey: "<<i<<" Decrypted text: "<<decrypted_text<<" (not printable)";
            continue;}
    }
    //sorting the scores in descending order
    sort(scores.begin(), scores.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
        return a.second > b.second;
    });

    for(int i=0; i<min(5, (int)scores.size()); i++){
        int key = scores[i].first;
        double score = scores[i].second;
        cout<<"\nKey: "<<key<<" Score: "<<score<<" Decrypted text: "<<keys_texts[key];
    }
    
    return 0;
}