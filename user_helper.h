#pragma once
#include "types.h"
#include "user_entry.h"
#include "inode_loader.h"
#include <string>
#include <vector>
using namespace std;
class UserHelper {
public:
	static vector<UserEntry> GetUserList() {
		ifstream in;
		ContentLoader::GetContentIfStream(kUSER_CONTENT_ID, in);
		vector<UserEntry> ret;
		in.seekg(0, in.end);
		auto length = in.tellg();
		in.seekg(0, in.beg);
		int item_cnt = length / sizeof(UserEntry);
		for (int i = 0; i < item_cnt; i++) {
			UserEntry entry;
			in.read((char*)&entry, sizeof(UserEntry));
			if (entry.is_used == true) {
				ret.push_back(entry);
			}
		}
		in.close();
		return ret;
	}
	static ID_T FindUser(string name) {
		vector<UserEntry> entries = GetUserList();
		for (UserEntry entry : entries) {
			if (strcmp(name.c_str(), entry.name) == 0) {
				return entry.user_id;
			}
		}
		return 0;
	}
	static string FindUserByID(ID_T id) {
		vector<UserEntry> entries = GetUserList();
		for (UserEntry entry : entries) {
			if (entry.user_id == id) {
				return entry.name;
			}
		}
		return "";
	}
	static ID_T AddUser(string name) {
		ofstream out;
		ContentLoader::GetContentOfStream(kUSER_CONTENT_ID, out);
		out.seekp(0, out.end);
		auto length = out.tellp();
		out.seekp(0, out.beg);
	    auto add_position = length;

		UserEntry user_entry;
		ID_T id = length / sizeof(UserEntry) + 1;
		user_entry.user_id = id;
		user_entry.is_used = true;
		const char * name_str = name.c_str();
		for (int i = 0; i < kUSER_ENTRY_NAME_LENGTH; i++) {
			user_entry.name[i] = name_str[i];
			if (name_str[i] == '\0')
				break;
		}
		user_entry.name[kUSER_ENTRY_NAME_LENGTH] = '\0';
		out.seekp(add_position);
		out.write((char*)&user_entry, sizeof(UserEntry));
		out.close();
		return id;
	}
};