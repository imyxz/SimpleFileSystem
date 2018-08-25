#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
class CmdCd :public IRunnable {
public:
	int run(int argc, string* argv) override {
		if (argc >= 1) {
			string filepath = argv[0];
			Dir curDir = Dir(UserContext::cur_dir_id);
			INode * inode = PathHelper::GetINodeFromPath(curDir, filepath, false);
			if (inode == 0) {
				cerr << filepath << "not exist!";
				return -1;
			}
			else {
				UserContext::cur_dir_id = inode->GetID();
				return 0;
			}
		}
		else {
			return -1;
		}
	}
};