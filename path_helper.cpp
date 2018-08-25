#include "path_helper.h"
#include "inode_helper.h"
#include <string>
using namespace std;
INode * PathHelper::GetINodeFromPath(const Dir & curDir, const string & path) {
	size_t last_pos = 0;// last found path delimiter plus 1
	if (path.length() == 0) {
		return NULL;
	}
	if (path.substr(0, kPATH_DELIMITER.length()) != kPATH_DELIMITER) {
		last_pos = kPATH_DELIMITER.length();
	}
	size_t pos = string::npos;
	Dir cur_dir = curDir;
	while ((pos = path.find(kPATH_DELIMITER, last_pos)) != string::npos) {
		if (pos == last_pos) {
			last_pos++;
			continue;
		}
		string sub_str = path.substr(last_pos, pos - last_pos);
		ID_T sub_dir_id = cur_dir.findEntry(sub_str);
		if (sub_dir_id == 0) {
			return NULL;
		}
	}
}