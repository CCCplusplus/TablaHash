#pragma once
#include <vector>
#include <iostream>
#include <algorithm>    // std::find_if
#include "HashItem.hpp"

template<typename T>
class HashTable {
private:
    std::vector<HashItem> _table;
    int _size;
    int _totalItems;

    // Función hash para strings
    //borre todo lo de int por que pues no lo necesito.
    int HashFunc(const std::string& str)
    {
        int hash = 0;
        for (int i = 0; i < (int)str.size(); i++)
        {
            int val = static_cast<int>(str[i]) & 0xFF;
            hash = (hash * 256 + val) % _size;
        }
        return hash;
    }


public:
    explicit HashTable(int size) : _size(size), _totalItems(0) {
        _table.resize(size);
    }

    // Insertar una palabra en la tabla hash
    bool Insert(const std::string& key, int initial_value = 1) {
        if (_totalItems >= _size * 0.7) {  // Si la tabla está al 70% llena o más
            Resize();
        }

        int count = 0;  // Contador para manejar colisiones
        int hash = HashFunc(key);
        while (!_table[hash].empty() && _table[hash].getKey() != key) {
            hash = (hash + 1) % _size;
            count++;
            if (count >= _size) {  // Si ya revisamos toda la tabla y no encontramos un espacio, hay un problema
                std::cerr << "Error: la tabla está completamente llena." << std::endl;
                return false;
            }
        }

        if (_table[hash].empty()) {
            _table[hash].setKey(key);
            _table[hash].setValue(initial_value);
        }
        else {
            _table[hash].incrementValue();
        }
        _totalItems++;

        return true;
    }


    //Tabla dinamica
    void Resize() {
        std::vector<HashItem> oldTable = _table;
        _size *= 2;
        _table.clear();
        _table.resize(_size);
        for (const auto& item : oldTable) {
            if (!item.empty()) {
                Insert(item.getKey(), item.getValue());
            }
        }
    }



    // Mostrar las palabras más comunes
    void ShowCommonWords(int count) {
        std::vector<HashItem> items;
        for (const auto& item : _table) {
            if (!item.empty()) {
                items.push_back(item);
            }
        }

        std::sort(items.begin(), items.end(), [](const HashItem& a, const HashItem& b) {
            return a.getValue() > b.getValue();
            });

        for (int i = 0; i < count && i < items.size(); i++) {
            std::cout << "Palabra: " << items[i].getKey() << " - Frecuencia: " << items[i].getValue() << std::endl;
        }
    }
};