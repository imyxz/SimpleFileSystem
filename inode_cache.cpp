#include"inode_cache.h"
#include "inode_loader.h"
INodeCache::INodeCache() {
	inodes = new INodeStruct*[kINODE_MAXN];
	memset(inodes, NULL, sizeof(INodeStruct *) * kINODE_MAXN);
}
INodeStruct * INodeCache::GetINode(ID_T inode_id) {
	if (inodes[inode_id] == NULL) {
		if (INodeLoader::IsNodeExist(inode_id)) {
			inodes[inode_id] = new INodeStruct(INodeLoader::LoadINode(inode_id));
		}
	}
	return inodes[inode_id];
}
INodeStruct * INodeCache::SetINode(const INodeStruct & target) {
	if (inodes[target.id] != NULL) {
		delete inodes[target.id];
	}
	inodes[target.id] = new INodeStruct(target);
	return inodes[target.id];
}
INodeCache::~INodeCache() {
	for (ID_T i = 0; i < kINODE_MAXN; i++) {
		if(inodes[i]!=NULL){
			//INodeLoader::SaveINode(*inodes[i]);
			delete inodes[i];
		}
	}
	delete [] inodes;
}
void INodeCache::SaveAll() {
	for (ID_T i = 0; i < kINODE_MAXN; i++) {
		if (inodes[i] != NULL) {
			INodeLoader::SaveINode(*inodes[i]);
		}
	}
}