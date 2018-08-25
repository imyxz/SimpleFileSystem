#pragma once
#include<map>
#include<string>
#include<iostream>
#include <algorithm>
#include"irunnable.h"
using namespace std;
struct ArgEntry {
	IRunnable * runner;
	string description;
};
class ArgParser {
protected:
	map<string, ArgEntry> entries;
	string trim(string str) {
		size_t endpos = str.find_last_not_of(" \t");
		size_t startpos = str.find_first_not_of(" \t");
		if (std::string::npos != endpos)
		{
			str = str.substr(0, endpos + 1);
			str = str.substr(startpos);
		}
		else {
			str.erase(std::remove(std::begin(str), std::end(str), ' '), std::end(str));
		}
		return str;
	}
public:
	int run(int argc, string* argv) {
		if (argc >= 1) {
			string target = string(argv[0]);
			if (target != "help")
			{
				if (entries.count(target) > 0) {
					ArgEntry & entry = entries[target];
					return entry.runner->run(argc - 1, argv + 1);
					
				}
			}
		}
		printDescription();
		return -1;
	}
	int run(int argc, char** argv) {
		string * args = new string[argc];
		for (int i = 0; i < argc; i++) {
			args[i] = argv[i];
		}
		run(argc, args);
	}
	int run(string args){
		int last_pos = 0;
		int cur_pos = string::npos;
		int cnt = 0;
		args = trim(args);
		while ((cur_pos = args.find(' ',last_pos)) != string::npos) {
			if (last_pos == cur_pos) {
				last_pos++;
				continue;
			}
			cnt++;
			last_pos = cur_pos+1;
		}
		if (last_pos < args.length()) {
			cnt++;
		}
		string * str_array = new string[cnt];
		last_pos = 0;
		cur_pos = string::npos;
		cnt = 0;
		while ((cur_pos = args.find(' ', last_pos)) != string::npos) {
			if (last_pos == cur_pos) {
				last_pos++;
				continue;
			}
			str_array[cnt++] = args.substr(last_pos, cur_pos - last_pos);
			last_pos = cur_pos + 1;
		}
		if (last_pos < args.length()) {
			str_array[cnt++] = args.substr(last_pos);
		}
		int code = run(cnt, str_array);
		delete [] str_array;
		return code;
	}
	void printDescription() {
		for (auto entry : entries) {
			cout << entry.first << "\t" << entry.second.description << endl;
		}
	}
	void addEntry(const string & name, const ArgEntry & entry) {
		entries[name] = entry;
	}
};