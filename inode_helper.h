#pragma once
#include "used_map.h"
#include "file.h"
#include "dir.h"
#include "inode.h"
#include "user_context.h"
#include "inode_loader.h"
#include <ctime>
class INodeHelper {
private:

public:
	static INodeMap inode_map;
	static ContentMap content_map;
	static const ID_T kROOT_ID = 1;
	static void Init() {
		if (inode_map.getSlot(kROOT_ID) == false) {
			INodeHelper::CreateDir(0, "/");
		}
	}
	static Dir GetRootDir() {
		return Dir(kROOT_ID);
	}
	static INodeMap & GetINodeMap(){
		return INodeHelper::inode_map;
	}
	static ContentMap & GetContentMap() {
		return INodeHelper::content_map;
	}
	static File CreateFile() {
		ID_T new_id = inode_map.findEmptySlot();
		ID_T new_content_id = content_map.findEmptySlot();
		inode_map.useSlot(new_id);
		content_map.useSlot(new_content_id);
		INodeStruct inode_struct;
		inode_struct.id = new_id;
		inode_struct.size = 0;
		inode_struct.ref_cnt = 0;
		inode_struct.type = INodeType::kFILE;
		inode_struct.content_id = new_content_id;
		inode_struct.owner_id = UserContext::user_id;
		inode_struct.owner_permission = 7;
		inode_struct.global_permission = 5;
		inode_struct.a_time = time(0);
		inode_struct.c_time = time(0);
		inode_struct.m_time = time(0);
		File file = File(inode_struct);
		ContentLoader::CreateContentFile(new_content_id);
		file.save();
		return file;
	}
	static Dir CreateDir(ID_T parent_inode_id,const string & name) {
		ID_T new_id = inode_map.findEmptySlot();
		ID_T new_content_id = content_map.findEmptySlot();
		inode_map.useSlot(new_id);
		content_map.useSlot(new_content_id);
		INodeStruct inode_struct;
		inode_struct.id = new_id;
		inode_struct.size = 0;
		inode_struct.ref_cnt = 1;
		inode_struct.type = INodeType::kDIR;
		inode_struct.content_id = new_content_id;
		inode_struct.owner_id = UserContext::user_id;
		inode_struct.owner_permission = 7;
		inode_struct.global_permission = 5;
		inode_struct.a_time = time(0);
		inode_struct.c_time = time(0);
		inode_struct.m_time = time(0);
		Dir dir = Dir(inode_struct);
		ContentLoader::CreateContentFile(new_content_id);
		dir.save();
		dir.addEntry(dir, ".");
		if (parent_inode_id == 0) {
			dir.addEntry(dir, "..");
		}
		else {
			Dir parent_inode = Dir(parent_inode_id);
			dir.addEntry(parent_inode, "..");
			parent_inode.addEntry(dir, name);
		}
		return dir;
		
	}
};
INodeMap INodeHelper::inode_map;
ContentMap INodeHelper::content_map;