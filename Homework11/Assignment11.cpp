#include <string> 
#include <iostream>
#include <fstream>
using namespace std;




string toLowerCase(string plainText, int length)
{
    for (int i = 0; i < length; i++) {
        if (plainText[i] > 64 && plainText[i] < 91)
            plainText[i] += 32;
    }
    return plainText;
}

void printKeyTable(char dictionaryMatrix[5][5]) {
    cout << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << dictionaryMatrix[i][j] << " ";
        }
        cout << endl;
    }
}


void generateKeyTable(string key, int keyLength, char dictionaryMatrix[5][5])
{
    int flag = 0, * dicty;

    // a 26 character hashmap 
    // to store count of the alphabet 
    dicty = (int*)calloc(26, sizeof(int));
    for (int i = 0; i < keyLength; i++) {
        if (key[i] != 'j')
            dicty[key[i] - 97] = 2;
    }

    dicty['j' - 97] = 1;

    int i = 0;
    int j = 0;

    for (int k = 0; k < keyLength; k++) {
        if (dicty[key[k] - 97] == 2) {
            dicty[key[k] - 97] -= 1;
            dictionaryMatrix[i][j] = key[k];
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }

    for (int k = 0; k < 26; k++) {
        if (dicty[k] == 0) {
            dictionaryMatrix[i][j] = (char)(k + 97);
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}

void search(char dictionaryMatrix[5][5], char a, int arr[])
{
    int i, j;

    if (a == 'j')
        a = 'i';

    for (i = 0; i < 5; i++) {

        for (j = 0; j < 5; j++) {

            if (dictionaryMatrix[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
        }
    }
}

string changeFinalLetter(string text, int length)
{
    if (length % 2 != 0) {
        text.push_back('x');
    }
    return text;
}

string encrypt(string word, char lower[5][5], char upper[5][5], int ps)
{
    int i, a[2], b[2];

    for (i = 0; i < ps; i += 2) {

        search(upper, word[i], a);
        search(lower, word[i + 1], b);


        word[i] = upper[a[0]][b[1]];
        word[i + 1] = lower[b[0]][a[1]];

    }
    return word;
}

string decrypt(string cypherText, char lower[5][5], char upper[5][5], int ps)
{
    int i, a[2], b[2];

    for (i = 0; i < ps; i += 2) {

        search(upper, cypherText[i], a);
        search(lower, cypherText[i + 1], b);

        cypherText[i] = upper[a[0]][b[1]];
        cypherText[i + 1] = lower[b[0]][a[1]];

    }
    return cypherText;
}

string encryptTwoSquare(string word, string key1, string key2)
{
    char upper[5][5];
    char lower[5][5];
    string finalWord;


    key1 = toLowerCase(key1, (int)key1.length());
    key2 = toLowerCase(key2, (int)key2.length());
    word = toLowerCase(word, (int)word.length());

    word = changeFinalLetter(word, (int)word.length());

    generateKeyTable(key1, (int)key1.length(), upper);
    generateKeyTable(key2, (int)key2.length(), lower);

    printKeyTable(upper);
    printKeyTable(lower);

    finalWord = encrypt(word, lower, upper, (int)word.length());

    return finalWord;
}

string decryptTwoSquare(string cypherText, string key1, string key2)
{
    char upper[5][5];
    char lower[5][5];
    string finalCypher;


    key1 = toLowerCase(key1, (int)key1.length());
    key2 = toLowerCase(key2, (int)key2.length());
    cypherText = toLowerCase(cypherText, (int)cypherText.length());

    generateKeyTable(key1, (int)key1.length(), upper);
    generateKeyTable(key2, (int)key2.length(), lower);

    printKeyTable(upper);
    printKeyTable(lower);


    finalCypher = decrypt(cypherText, lower, upper, (int)cypherText.length());

    return finalCypher;
}


string resolveDecypheredText(string txt) {
    string newText;
    for (int i = 0; i < (txt.size() / 2); i++) {
        char character1 = txt[i * 2];
        char character2 = txt[i * 2 + 1];

        newText += character1;
        if (character2 == 'x') {
            if ((i * 2 + 1) == (txt.size() - 1)) {
            }
            else {
                newText += character1 - 32;
            }
        }
        else {
            newText += character2;
        }
    }
    return newText;
}



int main()
{
    ifstream fin("test11.in");
    ofstream fout("test11.out");

    char* usedKey, usedWord;
    string key1, key2;
    int choice;
    string word;

    cout << "Tasteaza 1 pentru Decriptare sau 2 pentru Criptare\n";
    cin >> choice;
    if (choice < 1 || choice >2) {
        cout << "Wrong choice, please choose 1 or 2 next time";
        return 0;
    }

    cout << "Tasteaza cheia 1: \n";
    cin >> key1;

    cout << "Tasteaza cheia 2: \n";
    cin >> key2;

    /*cout << key1 << endl;
    cout << key2 << endl;*/

    while (fin >> word) {
        if (choice == 2) {
            string cipher_text = encryptTwoSquare(word, key1, key2);
            fout << "Text Cifrat cu cheia " << key1 << " si cu cheia " << key2 << " : " << word << " -> " << endl
                << cipher_text << endl;
        }
        else if (choice == 1) {
            string decipher_text = decryptTwoSquare(word, key1, key2);
            fout << "Text Cifrat cu cheia " << key1 << " si cu cheia " << key2 << " : " << word << " -> " << endl
                << resolveDecypheredText(decipher_text) << endl;
        }
    }



    return 0;
}

