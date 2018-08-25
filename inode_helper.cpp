#include"inode_helper.h"
#include"user_context.h"
File INodeHelper::CreateFile() {
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
	inode_struct.id = new_id;
	INodeStruct * inode_struct_p = SetINode(inode_struct);
	File file = File(inode_struct_p);
	ContentLoader::CreateContentFile(new_content_id);
	file.save();
	return file;
}
Dir INodeHelper::CreateDir(ID_T parent_inode_id, const string & name) {
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
	INodeStruct * inode_struct_p = SetINode( inode_struct);
	Dir dir = Dir(inode_struct_p);
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
INodeMap INodeHelper::inode_map;
ContentMap INodeHelper::content_map;
INodeCache INodeHelper::inode_cache;