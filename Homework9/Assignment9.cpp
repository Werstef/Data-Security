#include <string> 
#include <iostream>
#include <fstream>
using namespace std;


string generateKey(string str, string key)
{
	key.append(str);
	return key;
}


string encrypt(string textToEncrypt, string key)
{
	string encryptedText;

	for (int i = 0; i < textToEncrypt.size(); i++)
	{
		if (textToEncrypt[i] > 96 && textToEncrypt[i] < 123) {
			textToEncrypt[i] -= 'a' - 'A';
		}
		if (textToEncrypt[i] > 64 && textToEncrypt[i] < 91) {
			char x = (textToEncrypt[i] + key[i]) % 26;
			x += 'A';
			encryptedText.push_back(x);
		}
		else {
			return "ERROR";
		}
	}
	return encryptedText;
}

string decrypt(string textToDecrypt, string key)
{
	string decryptedText;
	decryptedText.append(key);

	for (int i = 0; i < textToDecrypt.size(); i++)
	{
		if (textToDecrypt[i] > 96 && textToDecrypt[i] < 123) {
			textToDecrypt[i] -= 'a' - 'A';
		}
		if (textToDecrypt[i] > 64 && textToDecrypt[i] < 91) {
			char x = (textToDecrypt[i] - decryptedText[i] + 26) % 26;
			x += 'A';
			decryptedText.push_back(x);
		}
		else {
			return "ERROR";
		}
	}
	return decryptedText;
}


int main()
{
	ifstream fin("test9.in");
	ofstream fout("test9.out");

	string key;
	int choice;
	string word;
	string finalText;

	cout << "Tasteaza 1 pentru Decriptare sau 2 pentru Criptare\n";
	cin >> choice;
	if (choice < 1 || choice >2) {
		cout << "Wrong choice, please choose 1 or 2 next time";
		return 0;
	}

	cout << "Tasteaza cheia (MAJUSCULE): \n";
	cin >> key;
	for (int i = 0; i < key.size(); i++) {
		if (key[i] < 65 || key[i] > 90) {
			cout << "Cheie introdusa gresit, trebuie introduse doar MAJUSCULE\n";
			return 0;
		}
	}

	while (fin >> word) {
		finalText.append(word);
	}
	string keyExtended = generateKey(finalText, key);
	if (choice == 2) {
		string cipher_text = encrypt(finalText, keyExtended);
		fout << "Text Cifrat cu cheia " << key << " : " << finalText << " -> " << endl
			<< cipher_text << endl;
	}
	else if (choice == 1) {
		string decipher_text = decrypt(finalText,  key);
		fout << "Text Descifrat cu cheia " << key << " : " << finalText << " -> " << endl
			<< decipher_text << endl;
	}

	return 0;
}

