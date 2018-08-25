#pragma once
#include "used_map.h"
#include "file.h"
#include "dir.h"
#include "inode.h"
#include "inode_loader.h"
#include "inode_cache.h"
#include <ctime>
class INodeHelper {
private:

public:
	static INodeMap inode_map;
	static ContentMap content_map;
	static INodeCache inode_cache;
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
	static INodeStruct * GetINode(ID_T inode_id){
		return inode_cache.GetINode(inode_id);
	}
	static INodeStruct * SetINode(const INodeStruct &  inode) {
		return inode_cache.SetINode(inode);
	}
	static File CreateFile();
	static Dir CreateDir(ID_T parent_inode_id, const string & name);

};
