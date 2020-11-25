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

void search(char dictionaryMatrix[5][5], char a, char b, int arr[])
{
    int i, j;

    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    if (a == b) {
        b = 'x';
    }

    for (i = 0; i < 5; i++) {

        for (j = 0; j < 5; j++) {

            if (dictionaryMatrix[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            else if (dictionaryMatrix[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
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

string encrypt(string word, char dictionaryMatrix[5][5], int ps)
{
    int i, a[4];

    for (i = 0; i < ps; i += 2) {

        search(dictionaryMatrix, word[i], word[i + 1], a);
        //case 1 same row
        if (a[0] == a[2]) {
            word[i] = dictionaryMatrix[a[0]][(a[1] + 1) %5];
            word[i + 1] = dictionaryMatrix[a[0]][(a[3] + 1) % 5];
        }
        //case 2 same column
        else if (a[1] == a[3]) {
            word[i] = dictionaryMatrix[(a[0] + 1) % 5][a[1]];
            word[i + 1] = dictionaryMatrix[(a[2] + 1) % 5][a[1]];
        }
        // case 3 interchange columns
        else {
            word[i] = dictionaryMatrix[a[0]][a[3]];
            word[i + 1] = dictionaryMatrix[a[2]][a[1]];
        }
    }
    return word;
}

string decrypt(string cypherText, char dictionaryMatrix[5][5], int ps)
{
    int i, a[4];
    for (i = 0; i < ps; i += 2) {
        search(dictionaryMatrix, cypherText[i], cypherText[i + 1], a);
        //case 1 same row
        if (a[0] == a[2]) {
            cypherText[i] = dictionaryMatrix[a[0]][((a[1] - 1) % 5)];
            cypherText[i + 1] = dictionaryMatrix[a[0]][((a[3] - 1) % 5)];
            if (a[1] == 0) {
                cypherText[i] = dictionaryMatrix[a[0]][4];
            }
            if (a[3] == 0) {
                cypherText[i + 1] = dictionaryMatrix[a[0]][4];
            }
        }
        // case 2 same column
        else if (a[1] == a[3]) {
            cypherText[i] = dictionaryMatrix[((a[0] - 1)%5)][a[1]];
            cypherText[i + 1] = dictionaryMatrix[((a[2] - 1)%5)][a[1]];
            if (a[0] == 0) {
                cypherText[i] = dictionaryMatrix[4][a[1]];
            }
            if (a[2] == 0) {
                cypherText[i + 1] = dictionaryMatrix[4][a[1]];
            }
        }
        // case 3 change columns
        else {
            cypherText[i] = dictionaryMatrix[a[0]][a[3]];
            cypherText[i + 1] = dictionaryMatrix[a[2]][a[1]];
        }
    }
    return cypherText;
}

string encryptPlayfairCipher(string word, string key)
{
    char dictionaryMatrix[5][5];
    string finalWord;


    key = toLowerCase(key, (int)key.length());
    word = toLowerCase(word, (int)word.length());

    word = changeFinalLetter(word, (int)word.length());

    generateKeyTable(key, (int)key.length(), dictionaryMatrix);

    printKeyTable(dictionaryMatrix);

    finalWord = encrypt(word, dictionaryMatrix, (int)word.length());

    return finalWord;
}

string decryptPlayfairCipher(string cypherText, string key)
{
    char dictionaryMatrix[5][5];
    string finalCypher;
    
    key = toLowerCase(key, (int)key.length());
    cypherText = toLowerCase(cypherText, (int)cypherText.length());

    generateKeyTable(key, (int)key.length(), dictionaryMatrix);

    printKeyTable(dictionaryMatrix);

    finalCypher = decrypt(cypherText, dictionaryMatrix, (int)cypherText.length());

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
	ifstream fin("text6.in");
	ofstream fout("text6.out");

    char* usedKey, usedWord;
	string key;
	int choice;
	string word;

	cout << "Tasteaza 1 pentru Decriptare sau 2 pentru Criptare\n";
	cin >> choice;
	if (choice < 1 || choice >2) {
		cout << "Wrong choice, please choose 1 or 2 next time";
		return 0;
	}

	cout << "Tasteaza cheia : \n";
	cin >> key;

	while (fin >> word) {
        if (choice == 2) {
            string cipher_text = encryptPlayfairCipher(word, key);
            fout << "Text Cifrat cu cheia " << key << " : " << word << " -> " << endl
                << cipher_text << endl;
        }
        else if (choice == 1) {
            string decipher_text = decryptPlayfairCipher(word, key);
            fout << "Text Descifrat cu cheia " << key << " : " << word << " -> " << endl
                << resolveDecypheredText(decipher_text) << endl;
        }
	}

	

	return 0;
}

