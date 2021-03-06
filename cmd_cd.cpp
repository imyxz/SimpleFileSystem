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
			PathRoute route;
			PathHelper::GetPathRoute(filepath, route);
			INode * inode = PathHelper::GetINodeFromPath(curDir, route);
			if (inode == 0) {
				cerr << filepath << "not exist!";
				return -1;
			}
			if (inode->GetType() != INodeType::kDIR) {
				cerr << filepath << "is not a dir!";
				return -1;
			}
			string name = "";
			if (route.size() > 0) {
				name = route.back();
			}
			UserContext::PushDir(Dir(*inode), name);
			return 0;
		}
		else {
			return -1;
		}
	}
};