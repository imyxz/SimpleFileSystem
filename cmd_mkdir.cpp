#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
class CmdMkdir :public IRunnable {
public:
	int run(int argc, string* argv) override {
		if (argc >= 1) {
			string filepath = argv[0];
			Dir curDir = Dir(UserContext::cur_dir_id);
			PathRoute route;
			PathHelper::GetPathRoute(filepath, route);
			INode * inode = PathHelper::MakeDir(curDir, route);
			if (inode == 0) {
				cerr << "create dir faild! May be do not has permission"<<endl;
				return -1;
			}
			else {
				cout << "create dir success! inode id:" << inode->GetID() << endl;
				return 0;
			}
		}
		else {
			return -1;
		}
	}
};