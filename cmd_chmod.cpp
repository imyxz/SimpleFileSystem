#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
#include <iostream>
using namespace std;
class CmdChmod :public IRunnable {
public:
	int run(int argc, string* argv) override {
		if (argc >= 3) {
			int global = 0;
			int owner = 0;
			stringstream tmp (argv[0]);
			if (!(tmp >> owner)) {
				return -1;
			}
			tmp = stringstream(argv[1]);
			if (!(tmp >> global)) {
				return -1;
			}
			if (owner < 0 || owner > 7) {
				return -1;
			}
			if (global < 0 || global > 7) {
				return -1;
			}
			string filepath = argv[2];
			Dir curDir = Dir(UserContext::cur_dir_id);
			PathRoute route;
			PathHelper::GetPathRoute(filepath, route);
			INode * inode = PathHelper::GetINodeFromPath(curDir, route);
			if (inode == 0) {
				cerr << "file is not exist!" << endl;
				return -1;
			}
			if (inode->IsOwner() == false) {
				cerr << "permission deny" << endl;
				return -1;
			}
			inode->GetINode()->global_permission = global;
			inode->GetINode()->owner_permission = owner;
			return 0;
		}
		else {
			cerr << "usage: chmod OWNER_PERMISSION GLOBAL_PERMISSION FILEPATH" << endl;
			return -1;
		}
	}
};