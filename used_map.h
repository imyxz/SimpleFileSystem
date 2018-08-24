#pragma once
#include"types.h"
#include<string>
#include<cstring>
#include<fstream>
using namespace std;
const ID_T kINODE_MAXN = 65536;
const string kINODE_MAP_NAME = "inode_map";
const ID_T kCONTENT_MAXN = 65536;
const string kCONTENT_MAP_NAME = "content_map";
class UsedMap {
protected:
	SIZE_T maxn;
	string filename;
	bool * map_array;
	void loadFromFile() {
		ifstream in;
		in.open(filename, ios::in | ios::binary);
		if (in.is_open()) {
			in.read((char *)map_array, maxn * sizeof(bool));
		}
		else {
			memset(map_array, 0, maxn * sizeof(bool));
		}
		in.close();
	}
	void saveToFile() {
		ofstream out;
		out.open(filename, ios::out | ios::binary | ios::trunc);
		out.seekp(0, out.beg);
		out.write((char *)map_array, maxn * sizeof(bool));
		out.close();
	}
public:
	UsedMap(const SIZE_T max_slots, const string & filename) {
		maxn = max_slots;
		this->filename = filename;
		map_array = new bool[maxn];
		this->loadFromFile();
	}
	ID_T findEmptySlot() const {
		for (ID_T i = 1; i < maxn; i++) {
			if (map_array[i] == false) {
				return i;
			}
		}
		return 0;
	}
	void useSlot(ID_T id) {
		map_array[id] = true;
	}
	void deleteSlot(ID_T id) {
		map_array[id] = false;
	}
	bool getSlot(ID_T id) {
		return map_array[id];
	}
	~UsedMap() {
		this->saveToFile();
		delete map_array;
	}
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