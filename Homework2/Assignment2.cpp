#include <iostream>
#include <fstream>

using namespace std;

string encrypt(string text, int s)
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        if (isupper(text[i]))
            result += char(int(text[i] + s - 65) % 26 + 65);

        else
            result += char(int(text[i] + s - 97) % 26 + 97);
    }

    return result;
}

string decrypt(string text, int s)
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {

        if (isupper(text[i])) {
            char temp = char(int(text[i] - s - 65) % 26 + 65);
                if (temp < 'A') {
                    temp = temp + 'Z' - 'A' + 1;
                }
            result += temp;
        }
        else {
            char temp = char(int(text[i] - s - 65) % 26 + 65);
            if (temp < 'a') {
                temp = temp + 'z' - 'a' + 1;
            }
            result += temp;
        }
    }

    // Return the resulting string 
    return result;
}

int main()
{
    char x;
    int shift = 0;
    int choice;
    string word;

    ifstream fin("text2.in");
    ofstream fout("text2.out");

    cout << "Tasteaza 1 pentru Decriptare sau 2 pentru Criptare\n";
    cin >> choice;
    if (choice == 2) {
        cout << "Tasteaza parola de Criptare\n";
        cin >> shift;
    }

    string result;
    while (fin >> word) {
        if (choice == 1) {
            fout << "Decypther results for " << word << " : \n";
            for (int i = 0; i < 26; i++) {
                result = decrypt(word, i);
                fout << "For passwrod " << i << " we have the decryption: \n";
                fout << result << endl << endl;
            }
        }
        else {
            result = encrypt(word, shift);
            fout << result << endl;
        }
        
    }

    fin.close();
    fout.close();
    return 0;
}