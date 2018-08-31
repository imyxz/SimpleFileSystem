#pragma once
#include "used_map.h"
#include "file.h"
#include "dir.h"
#include "inode.h"
#include "inode_loader.h"
#include "inode_cache.h"
#include "user_helper.h"
#include "user_context.h"
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
			content_map.useSlot(kUSER_CONTENT_ID);
			ContentLoader::EmptyContentFile(kUSER_CONTENT_ID);
			Dir root = INodeHelper::CreateDir(0, "/");
			root.GetINode()->owner_id = kROOT_ID;
			root.GetINode()->global_permission = 7;
			UserHelper::AddUser("root");
		}
		UserContext::LoginAs("root");
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
	static void Save() {
		inode_map.saveToFile();
		content_map.saveToFile();
		inode_cache.SaveAll();
	}
};
