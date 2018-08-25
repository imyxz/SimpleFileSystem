#include "path_helper.h"
#include "inode_helper.h"
#include <string>
using namespace std;
INode * PathHelper::GetINodeFromPath(const Dir & curDir, const string & path,const bool mkdir_mode) {
	size_t last_pos = 0;// last found path delimiter plus 1
	if (path.length() == 0) {
		return NULL;
	}
	size_t pos = string::npos;
	Dir cur_dir = curDir;
	if (path.substr(0, kPATH_DELIMITER.length()) == kPATH_DELIMITER) {
		cur_dir = INodeHelper::GetRootDir();
		last_pos = kPATH_DELIMITER.length();
	}
	while ((pos = path.find(kPATH_DELIMITER, last_pos)) != string::npos) {
		if (pos == last_pos) {
			last_pos++;
			continue;
		}
		string sub_str = path.substr(last_pos, pos - last_pos);
		ID_T sub_dir_id = cur_dir.findEntry(sub_str);
		if (sub_dir_id == 0) {
			if (mkdir_mode) {
				Dir newDir = INodeHelper::CreateDir(cur_dir.GetID(), sub_str);
				sub_dir_id = newDir.GetID();
			}
			else {
				return NULL;
			}
		}
		cur_dir = Dir(sub_dir_id);
		last_pos = pos + 1;
	}
	if (last_pos >= path.length()) {
		Dir * ret = new Dir(cur_dir);
		return ret;
	}
	string filename = path.substr(last_pos);
	ID_T ret_id = cur_dir.findEntry(filename);
	if (ret_id == 0) {
		if (mkdir_mode) {
			Dir newDir = INodeHelper::CreateDir(cur_dir.GetID(), filename);
			return new Dir(newDir);
		}
		else {
			return NULL;
		}
		
	}
	INode inode = INode(ret_id);
	if (inode.GetType() == INodeType::kFILE) {
		if (mkdir_mode) {
			return NULL;
		}
		else {
			return new File(inode);
		}
	}
	else if (inode.GetType() == INodeType::kDIR) {
		return new Dir(inode);
	}
	return NULL;
}