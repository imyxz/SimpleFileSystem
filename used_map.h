#pragma once
#include"types.h"
#include<string>
#include<cstring>
#include<fstream>
#include"consts.h"
using namespace std;

class UsedMap {
protected:
	SIZE_T maxn;
	string filename;
	bool * map_array;
	void loadFromFile();
public:
	UsedMap(const SIZE_T max_slots, const string & filename);
	ID_T findEmptySlot() const;
	void useSlot(ID_T id) {
		map_array[id] = true;
	}
	void deleteSlot(ID_T id) {
		map_array[id] = false;
	}
	bool getSlot(ID_T id) {
		return map_array[id];
	}
	void saveToFile();
	~UsedMap();
};
class INodeMap:public UsedMap {
public:
	INodeMap():UsedMap(kINODE_MAXN,kINODE_MAP_NAME) {

	}
};
class ContentMap :public UsedMap {
public:
	ContentMap() :UsedMap(kCONTENT_MAXN, kCONTENT_MAP_NAME) {

	}
};