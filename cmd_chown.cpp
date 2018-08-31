#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
#include <iostream>
using namespace std;
class CmdChown :public IRunnable {
public:
	int run(int argc, string* argv) override {
		if (argc >= 2) {
			string target = argv[0];
			string filepath = argv[1];
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
			ID_T user_id = UserHelper::FindUser(target);
			if (user_id == 0) {
				cerr << "user not exist" << endl;
				return -1;
			}
			inode->GetINode()->owner_id = user_id;
			return 0;
		}
		else {
			cerr << "usage: chown USER FILEPATH" << endl;
			return -1;
		}
	}
};