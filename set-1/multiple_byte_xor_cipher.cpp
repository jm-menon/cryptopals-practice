#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

int hex_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

string hex_to_bytes(const string& hex) {
    if (hex.size() % 2 != 0) {
        throw invalid_argument("Hex input must have an even length");
    }

    string bytes;

    for (size_t i = 0; i < hex.size(); i += 2) {
        int high = hex_value(hex[i]);
        int low = hex_value(hex[i + 1]);

        if (high == -1 || low == -1) {
            throw invalid_argument("Invalid hexadecimal character");
        }

        bytes += static_cast<char>((high << 4) | low);
    }

    return bytes;
}

string xor_with_byte_key(const string& ciphertext,
                         unsigned char key) {
    string result;

    for (unsigned char c : ciphertext) {
        result += static_cast<char>(c ^ key);
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

int main() {
    string hex_string;
    int input_number = 0;
    cout << "Enter hex strings to decrypt (enter 0 to stop):\n";
    while (cin >> hex_string) {
        if (hex_string == "0") {
            break;
        }

        try {
            string ciphertext = hex_to_bytes(hex_string);
            bool found = false;
            //cout<<"\ncheck1\n";
            for (int key = 0; key < 256; ++key) {
                //cout<<static_cast<unsigned char>(key);
                //return 0;
                //cout<<"\ncheck2\n";
                string plaintext = xor_with_byte_key(
                    ciphertext, static_cast<unsigned char>(key)
                );
                //cout<<"\ncheck3\n";
                if (is_printable_text(plaintext)) {
                    cout << "\nInput " << hex_string<< "no: " << input_number
                         << " | Key: " << key
                         << " | Plaintext: " << plaintext << '\n';

                    found = true;
                }
                //cout<<"\ncheck4\n";
            }
            //cout<<"\ncheck5\n";
            ++input_number;
            if (!found) {
                continue;
                cout << "\nInput " << hex_string
                     << ": No fully printable candidates found.\n";
            }

        } catch (const invalid_argument& e) {
            //continue;
            cerr << "\nSkipping invalid input: " << e.what() << '\n';
        }
    }

    cout << "\nProcessed " << input_number << " input(s).\n";
    return 0;
}