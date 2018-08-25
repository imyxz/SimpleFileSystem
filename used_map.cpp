#include "used_map.h"
void UsedMap::loadFromFile() {
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
void UsedMap::saveToFile() {
	ofstream out;
	out.open(filename, ios::out | ios::binary | ios::trunc);
	out.seekp(0, out.beg);
	out.write((char *)map_array, maxn * sizeof(bool));
	out.close();
}
UsedMap::UsedMap(const SIZE_T max_slots, const string & filename) {
	maxn = max_slots;
	this->filename = filename;
	map_array = new bool[maxn];
	this->loadFromFile();
}
ID_T UsedMap::findEmptySlot() const {
	for (ID_T i = 1; i < maxn; i++) {
		if (map_array[i] == false) {
			return i;
		}
	}
	return 0;
}
UsedMap::~UsedMap() {
	this->saveToFile();
	delete [] map_array;
}