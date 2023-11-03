#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "HashTable.hpp" 

int main() {
    HashTable<std::string> table(10); //tamaño incial nada más para que no marque error.
    std::string filename = "text.txt"; // Use las primeras 300 palabras de game of thrones.
    std::string word;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    while (inputFile >> word) {
        // Ignorar mayusculas y convertir todas a minusculas
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Adios espacios y Saltos
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) { return !std::isalpha(c); }), word.end());

        // Mete la palabra
        table.Insert(word);
    }
    inputFile.close();

    // Top 10 baby
    table.ShowCommonWords(10);

    return 0;
}

