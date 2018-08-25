#include "inode_helper.h"
#include "inode.h"
INode::INode(const ID_T & inode_id) {
	this->inode = INodeHelper::GetINode(inode_id);
}
void INode::save() {
	INodeLoader::SaveINode(*this->inode);
}