#pragma once
#include <iostream>

template<typename T>

class HashItem 
{
public:
	HashItem(): _key(-1) {}

	~HashItem() {}

	int GetKey() { return _key; }
	void SetKey(int k) { _key = k; }

	int GetsKey() { return _skey; }
	void SetsKey(std:: string k) { _skey = k; }

	T GetObj() { return _obj; }
	void SetObj(T value) { _obj = value; }

	bool operator == (HashItem& item) 
	{
		if (_key == item.GetKey())
			return true;

		return false;
	}

	void operator = (HashItem item) 
	{
		_key = item.GetKey();
		_obj = item.GetObj();
	}

private:
	int _key;
	std::string _skey;
	T _obj;
};