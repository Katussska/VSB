#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Funkce pro načtení výškové mapy ze souboru
vector<vector<int>> nactiVyskovouMapu(const string &nazevSouboru) {
    ifstream soubor(nazevSouboru);
    if (!soubor.is_open()) {
        cerr << "Nelze otevřít soubor." << endl;
        exit(EXIT_FAILURE);
    }

    int m, n;
    soubor >> m >> n; // Načtení rozměrů mapy

    vector<vector<int>> vyskovaMapa(m, vector<int>(n, 0)); // Inicializace matice výškové mapy

    // Načtení prvků výškové mapy ze souboru
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            soubor >> vyskovaMapa[i][j];
        }
    }

    soubor.close(); // Uzavření souboru
    return vyskovaMapa;
}

int main() {
    string nazevSouboru = "HeightMap4"; // Změňte na název vašeho vstupního souboru
    vector<vector<int>> vyskovaMapa = nactiVyskovouMapu(nazevSouboru + ".txt");

    int pocetSten = spocitejSteny(vyskovaMapa);

    // Výstup počtu stěn
    cout << nazevSouboru << endl;
    cout << "Stěn: " << pocetSten << endl;

    return 0;
}
