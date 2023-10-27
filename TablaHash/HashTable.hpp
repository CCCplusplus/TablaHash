#pragma once
#include <iostream>
#include "HashItem.hpp"

template<typename T>
class HashTableClass
{
private:
	HashItem<T>* _table;
	int _size, _totalitems;

	bool IsNumPrime(int val) 
	{
		for (int i = 2; (i * i) <= val; i++) 
		{
			if ((val % i) == 0) 
			{
				return false;
			}
			return true;
		}
	}

	int GetNextPrimeNum(int val) 
	{
		for (int i = val + 1;; i++)
		{
			if (IsNumPrime(i)) 
			{
				break;
			}
			return i;
		}
	}

public:
	HashTableClass(int value) : _size(0), _totalitems(0)
	{
		if (value > 0) 
		{
			_size = GetNextPrimeNum(value);
			_table = new HashItem<T>[_size];
		}
	}

	~HashTableClass() 
	{
		if (_table != NULL) 
		{
			delete[] _table;
			_table = NULL;
		}
	}

	bool Insert(int key, T& obj) 
	{
		if (_totalitems == _size) 
		{
			return false;
		}

		int hash = HashFunc(key);
		int step = HashFunc2(key);
		while (_table[hash].GetKey() != -1) 
		{
			hash+=step;
			hash %= _size;
		}
		_table[hash].SetKey(key);
		_table[hash].SetObj(obj);
		_totalitems++;
		return true;
	}

	bool Insert(std::string key, T& obj)
	{
		if (_totalitems == _size)
		{
			return false;
		}

		int hash = HashFunc(key);
		while (_table[hash].GetKey() != -1)
		{
			hash++;
			hash %= _size;
		}
		_table[hash].SetsKey(key);
		_table[hash].SetObj(obj);
		_totalitems++;
		return true;
	}

	bool Find(int key, T* obj) 
	{
		int hash = HashFunc(key);
		std::cout << "Hash: " << hash << std::endl;
		int step = HashFunc2(key);
		std::cout << "Step: " << step << std::endl;
		int originalHash = hash;

		while (_table[hash].GetKey() != -1)
		{
			if (_table[hash].GetKey() == key)
			{
				if (obj != NULL)
					*obj = _table[hash].GetObj();
				return true;
			}

			hash+=step;
			hash %= _size;
			if (originalHash == hash)
				return false;
		}
		return false;
	}


	void Delete(int key) 
	{
		int hash = HashFunc(key);
		int step = HashFunc2(key);
		int originalHash = hash;

		while (_table[hash].Getkey() != -1) 
		{
			if (_table[hash].GetKey() == key) 
			{
				_table[hash].SetKey(-1);
				_table[hash].SetObj(NULL);
				_totalitems--;
				return;
			}
			hash+=step;
			hash %= _size;
			if (originalHash == hash)
				return;
		}
	}

	int HashFunc(int key) 
	{
		return key % _size;
	}

	int HashFunc2(int key) 
	{
		return 3 - key % 3;
	}

	int HashFunc(std::string& str) 
	{
		int hash = 0;
		for (int i = 0; i < (int)str.size(); i++) 
		{
			int val = (int)str[i];
			hash = (hash * 256 + val) % _size;
		}
		return hash;
	}

	int GetSize() { return _size; }

	int GetTotalItems() { return _totalitems; }

};