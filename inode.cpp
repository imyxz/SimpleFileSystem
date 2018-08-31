#include "inode_helper.h"
#include "inode.h"
#include "user_context.h"
INode::INode(const ID_T & inode_id) {
	this->inode = INodeHelper::GetINode(inode_id);
}
void INode::save() {
	INodeLoader::SaveINode(*this->inode);
}
BOOL_T INode::HasPermissionRead() const {
	return CheckPermissionBit(UserContext::user_id, ReadBit);
}
BOOL_T INode::HasPermissionWrite() const {
	return CheckPermissionBit(UserContext::user_id, WriteBit);
}
BOOL_T INode::HasPermissionExec() const {
	return CheckPermissionBit(UserContext::user_id, ExecBit);
}
BOOL_T INode::CheckPermissionBit(ID_T login_user_id, int bit) const {
	if (login_user_id == kROOT_ID) {
		return true;
	}
	if (((inode->global_permission >> bit) & 1) == 1)
		return true;
	if (inode->owner_id == login_user_id) {
		if (((inode->owner_permission >> bit) & 1) == 1)
			return true;
	}
	return false;
}