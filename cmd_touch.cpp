#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
class CmdTouch :public IRunnable {
public:
	int run(int argc, string* argv) override {
		string filepath = argv[0];
		Dir curDir = Dir(UserContext::cur_dir_id);
		PathRoute route;
		PathHelper::GetPathRoute(filepath, route);
		INode * inode = PathHelper::GetINodeFromPath(curDir, route);
		if (inode == 0) {
			cerr << filepath << "not exist!";
			return -1;
		}
		else {
			UserContext::cur_dir_id = inode->GetID();
			return 0;
		}
	}
};