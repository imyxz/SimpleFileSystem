#pragma once
#include "types.h"
#include "inode_type.h"
#include<vector>
#include<string>
#include<cstring>
struct INodeStruct {
	ID_T id;
	SIZE_T size;
	SIZE_T ref_cnt;
	INodeType type;
	ID_T content_id;
	ID_T owner_id;
	PERMISSION_T owner_permission;
	PERMISSION_T global_permission;
	TIME_T c_time;
	TIME_T m_time;
	TIME_T a_time;
};
class INode {
protected:
	INodeStruct * inode;
public:
	INode(const ID_T & inode_id);
	INode(INodeStruct * inode) {
		this->inode = inode;
	}
	void save();
	ID_T GetID() const {
		return inode->id;
	}
	INodeStruct * GetINode() {
		return inode;
	}
	INodeType GetType() const{
		return inode->type;
	}
	void onRefer() {
		inode->ref_cnt++;
	}
	void onUnrefer() {
		inode->ref_cnt--;
	}
};

