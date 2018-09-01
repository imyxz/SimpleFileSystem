#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "types.h"
#include "inode_type.h"
#include<vector>
#include<string>
#include<cstring>
#include<sstream>
#include<iomanip>

using namespace std;
const int ReadBit = 2;
const int WriteBit = 1;
const int ExecBit = 0;
struct INodeStruct {
	ID_T id;
	SIZE_T size;
	SIZE_T ref_cnt;
	INodeType type;
	ID_T content_id;
	ID_T owner_id;
	PERMISSION_T owner_permission;
	PERMISSION_T global_permission;
	time_t c_time;
	time_t m_time;
	time_t a_time;
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
	void UpdateATime() const {
		inode->a_time = time(0);
	}
	void UpdateMTime() const {
		inode->m_time = time(0);
	}
	string GetATime() const {
		return TimeToStr(inode->a_time);
	}
	string GetMTime() const {
		return TimeToStr(inode->m_time);
	}
	string GetCTime() const {
		return TimeToStr(inode->c_time);
	}
	string TimeToStr(time_t _time) const {
		stringstream ss;
		tm * t = gmtime(&_time);
		ss << std::put_time(t, "%c");
		return ss.str();
	}
	string GetOwnerPermission() const {
		stringstream ss;
		if ((inode->owner_permission >> ReadBit) & 1) {
			ss << "R";
		}
		else {
			ss << "-";
		}
		if ((inode->owner_permission >> WriteBit) & 1) {
			ss << "W";
		}
		else {
			ss << "-";
		}
		if ((inode->owner_permission >> ExecBit) & 1) {
			ss << "X";
		}
		else {
			ss << "-";
		}
		return ss.str();
	}
	string GetGlobalPermission() const {
		stringstream ss;
		if ((inode->global_permission >> ReadBit) & 1) {
			ss << "R";
		}
		else {
			ss << "-";
		}
		if ((inode->global_permission >> WriteBit) & 1) {
			ss << "W";
		}
		else {
			ss << "-";
		}
		if ((inode->global_permission >> ExecBit) & 1) {
			ss << "X";
		}
		else {
			ss << "-";
		}
		return ss.str();
	}
	BOOL_T HasPermissionRead() const;
	BOOL_T HasPermissionWrite() const;
	BOOL_T HasPermissionExec() const;
	BOOL_T IsOwner() const;
	BOOL_T CheckPermissionBit(ID_T login_user_id, int bit) const;
	void onRefer() {
		inode->ref_cnt++;
	}
	void onUnrefer() {
		inode->ref_cnt--;
	}
};

