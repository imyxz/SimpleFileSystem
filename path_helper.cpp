#include "path_helper.h"
#include "inode_helper.h"
#include <string>
using namespace std;
INode * PathHelper::GetINodeFromPath(const Dir & curDir, const PathRoute & route) {

	Dir cur_dir = curDir;
	if (route.startFromRoot) {
		cur_dir = INodeHelper::GetRootDir();
	}
	for (size_t i = 0; i + 1 < route.size();i++) {
		const string & name = route[i];
		ID_T sub_dir_id = cur_dir.findEntry(name);
		if (sub_dir_id == 0) {
			return NULL;
		}
		cur_dir = Dir(sub_dir_id);
	}
	if (route.size() > 0) {
		string last_file_name = route.back();
		ID_T ret_id = cur_dir.findEntry(last_file_name);
		if (ret_id == 0) {
			return NULL;
		}
		INode inode = INode(ret_id);
		if (inode.GetType() == INodeType::kFILE) {
			return new File(inode);
		}
		else if (inode.GetType() == INodeType::kDIR) {
			return new Dir(inode);
		}
		return NULL;
	}
	else {
		return new Dir(cur_dir);
	}
}
INode * PathHelper::MakeDir(const Dir & curDir, const PathRoute & route) {

	Dir cur_dir = curDir;
	if (route.startFromRoot) {
		cur_dir = INodeHelper::GetRootDir();
	}
	for (size_t i = 0; i + 1 < route.size(); i++) {
		const string & name = route[i];
		ID_T sub_dir_id = cur_dir.findEntry(name);
		if (sub_dir_id == 0) {
			Dir newDir = INodeHelper::CreateDir(cur_dir.GetID(), name);
			sub_dir_id = newDir.GetID();
		}
		cur_dir = Dir(sub_dir_id);
	}
	if (route.size() > 0) {
		string last_file_name = route.back();
		ID_T ret_id = cur_dir.findEntry(last_file_name);
		if (ret_id == 0) {
			Dir newDir = INodeHelper::CreateDir(cur_dir.GetID(), last_file_name);
			return new Dir(newDir);
		}
		INode inode = INode(ret_id);
		if (inode.GetType() == INodeType::kFILE) {
			return NULL;
		}
		else if (inode.GetType() == INodeType::kDIR) {
			return new Dir(inode);
		}
		return NULL;
	}
	else {
		return new Dir(cur_dir);
	}
}
void PathHelper::GetPathRoute(const string & path, PathRoute & route)
{
	size_t last_pos = 0;// last found path delimiter plus 1
	if (path.length() == 0) {
		return;
	}
	size_t pos = string::npos;
	if (path.substr(0, kPATH_DELIMITER.length()) == kPATH_DELIMITER) {
		last_pos = kPATH_DELIMITER.length();
		route.startFromRoot = true;
	}
	else {
		route.startFromRoot = false;
	}
	while ((pos = path.find(kPATH_DELIMITER, last_pos)) != string::npos) {
		if (pos == last_pos) {
			last_pos++;
			continue;
		}
		string sub_str = path.substr(last_pos, pos - last_pos);
		route.push_back(sub_str);
		last_pos = pos + 1;
	}
	if (last_pos >= path.length()) {
		return;
	}
	string filename = path.substr(last_pos);
	route.push_back(filename);
	return;
}
