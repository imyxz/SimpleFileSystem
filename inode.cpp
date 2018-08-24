#include "inode_loader.h"
#include "inode.h"
INode::INode(const ID_T & inode_id) {
	this->inode = INodeLoader::LoadINode(inode_id);
}
void INode::save() {
	INodeLoader::SaveINode(this->inode);
}