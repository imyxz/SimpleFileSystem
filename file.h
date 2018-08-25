#pragma once
#include "types.h"
#include "inode_type.h"
#include "inode_loader.h"
#include<vector>
#include<string>
#include<cstring>
class File :public INode {
public:
	File(ID_T inode_id) :INode(inode_id) {
		if (inode->type != INodeType::kFILE) {
			throw new exception("this inode is not type file.");
		}
	}
	File(INodeStruct * inode_struct) :INode(inode_struct) {

	}
	ifstream & getIfStream() {
		return ContentLoader::GetContentIfStream(inode->content_id);
	}
	ofstream & getOfStream() {
		return ContentLoader::GetContentOfStream(inode->content_id);
	}
};