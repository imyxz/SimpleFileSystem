#pragma once
#include "consts.h"
#include "inode.h"
#include "inode_loader.h"
#include <cstring>
class INodeCache {
private:
	INodeStruct ** inodes;
public:
	INodeCache();
	INodeStruct * GetINode(ID_T inode_id);
	INodeStruct * SetINode(const INodeStruct & target);
	void SaveAll();
	~INodeCache();
};