#include <iostream>
#include "HashTable.hpp"

int main()
{
	HashTableClass<int> _table(5);

	int item = 0;
	item = 321;
	_table.Insert(123, item);
	item = 345;
	_table.Insert(543, item);
	item = 987;

	std::string str("cats");
	int stringHash = _table.HashFunc(str);

	std::cout << "String to hash " << stringHash << std::endl;

	if (_table.Find(123, &item))
		std::cout << item << std::endl;
	else
		std::cout << "Not Found" << std::endl;

	std::cout << _table.GetSize() << std::endl;
}