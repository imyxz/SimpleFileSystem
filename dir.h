#pragma once
#include "types.h"
#include "inode_type.h"
#include "inode_loader.h"
#include "directory_entry.h"
#include<vector>
#include<string>
#include<cstring>
class Dir :public INode {
public:
	Dir(const ID_T & inode_id) :INode(inode_id) {
		if (inode->type != INodeType::kDIR) {
			throw new exception("this inode is not type dir.");
		}
	}
	Dir(INodeStruct * inode_struct) :INode(inode_struct) {

	}
	Dir(INode & inode) :INode(inode) {
		if (inode.GetINode()->type != INodeType::kDIR) {
			throw new exception("this inode is not type dir.");
		}
	}
/**	Dir & operator =(INode& inode) {
		if (inode.GetType() != INodeType::kDIR) {
			throw new exception("Only can conver a dir type INode to Dir");
		}
		INodeStruct & inode_struct = inode.GetINode();
		return Dir(inode_struct);
	}**/
	vector<DirectoryEntry> getEntries() const {
		vector<DirectoryEntry> ret;
		ifstream in;
		ContentLoader::GetContentIfStream(inode->content_id, in);
		in.seekg(0, in.end);
		auto length = in.tellg();
		in.seekg(0, in.beg);
		auto item_cnt = length / sizeof(DirectoryEntry);
		for (int i = 0; i < item_cnt; i++) {
			DirectoryEntry entry;
			in.read((char*)&entry, sizeof(DirectoryEntry));
			if (entry.is_used == true) {
				ret.push_back(entry);
			}
		}
		in.close();
		return ret;
	}
	void addEntry(INode & inode_entry, const string & name) {
		//find deleted entry
		int add_position = -1;
		ifstream in;
		ContentLoader::GetContentIfStream(inode->content_id, in);
		in.seekg(0, in.end);
		auto length = in.tellg();
		in.seekg(0, in.beg);
		auto item_cnt = length / sizeof(DirectoryEntry);
		for (int i = 0; i < item_cnt; i++) {
			DirectoryEntry entry;
			in.read((char*)&entry, sizeof(DirectoryEntry));
			if (entry.is_used == false) {
				add_position = i * sizeof(DirectoryEntry);
				break;
			}
		}
		if (add_position < 0) {
			add_position = length;
		}
		in.close();
		ofstream out;
		ContentLoader::GetContentOfStream(inode->content_id,out);
		DirectoryEntry directory_entry;
		directory_entry.inode_id = inode_entry.GetID();
		directory_entry.is_used = true;
		const char * name_str = name.c_str();
		for (int i = 0; i < kDIRECTORY_ENTRY_NAME_LENGTH; i++) {
			directory_entry.name[i] = name_str[i];
			if (name_str[i] == '\0')
				break;
		}
		directory_entry.name[kDIRECTORY_ENTRY_NAME_LENGTH] = '\0';
		out.seekp(add_position);
		out.write((char*)&directory_entry, sizeof(DirectoryEntry));
		out.close();
		inode_entry.onRefer();
	}
	ID_T findEntry(const string & name) const {
		vector<DirectoryEntry> entries = this->getEntries();
		for (DirectoryEntry entry : entries) {
			if (strcmp(name.c_str(), entry.name) == 0) {
				return entry.inode_id;
			}
		}
		return 0;
	}
	string findEntryName(const ID_T & entry_id) const {
		vector<DirectoryEntry> entries = this->getEntries();
		for (DirectoryEntry entry : entries) {
			if (entry.inode_id == entry_id) {
				return entry.name;
			}
		}
		return 0;
	}
	void deleteEntry(INode & inode_entry) {
		ifstream in;
		ContentLoader::GetContentIfStream(inode->content_id,in);
		in.seekg(0, in.end);
		auto length = in.tellg();
		in.seekg(0, in.beg);
		auto item_cnt = length / sizeof(DirectoryEntry);
		for (int i = 0; i < item_cnt; i++) {
			DirectoryEntry entry;
			in.read((char*)&entry, sizeof(DirectoryEntry));
			if (entry.is_used == true && entry.inode_id == inode_entry.GetID()) {
				entry.is_used = false;
				break;
			}
		}
		in.close();
		inode_entry.onUnrefer();
	}
};