#pragma once
#include"types.h"
#include<string>
#include<fstream>
using namespace std;
const ID_T kINODE_MAXN = 65536;
const string kINODE_MAP_NAME = "inode_map";
class INodeMap {
private:
	bool * map_array;
	void loadFromFile() {
		ifstream in;
		in.open(kINODE_MAP_NAME, ios::in | ios::binary);
		in.read((char *)map_array, kINODE_MAXN * sizeof(bool));
		in.close();
	}
	void saveToFile() {
		ofstream out;
		out.open(kINODE_MAP_NAME, ios::out | ios::binary | ios::trunc);
		out.seekp(0, out.beg);
		out.write((char *)map_array, kINODE_MAXN * sizeof(bool));
		out.close();
	}
public:
	INodeMap() {
		map_array = new bool[kINODE_MAXN];
		this->loadFromFile();
	}
	ID_T findEmptySlot() const {
		for (ID_T i = 1; i < kINODE_MAXN; i++) {
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
	~INodeMap() {
		this->saveToFile();
		delete map_array;
	}
};