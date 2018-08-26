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
	File(INode & inode) :INode(inode) {
		if (inode.GetINode()->type != INodeType::kFILE) {
			throw new exception("this inode is not type file.");
		}
	}
	void getIfStream(ifstream & in) {
		return ContentLoader::GetContentIfStream(inode->content_id, in);
	}
	void getOfStream(ofstream & out) {
		return ContentLoader::GetContentOfStream(inode->content_id, out);
	}
};