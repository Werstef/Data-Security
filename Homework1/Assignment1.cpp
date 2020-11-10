#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char x;
    int symbols[128] = { 0 };
    int distinctSymbolsInput = 0;
    int numberOfSymbols = 0;

    ifstream fin ("text1.in");
    ofstream fout ("text1.out");


    while (fin >> x) {
        if( x > 32 )
        symbols[x]++;
        numberOfSymbols++;
    }

    for (int i = 0; i < 128; i++) {
        if (symbols[i] > 0) {
            fout << "Symbol: " << (char)i << " Occurences: " << symbols[i] << " Percentage: "
                << ((double)symbols[i] / numberOfSymbols) * 100 << " % \n";
            distinctSymbolsInput++;
        }
    }

    if (distinctSymbolsInput < 1) {
        fout << "No symbols were found";
    }
    fin.close();
    fout.close();
    return 0;
}