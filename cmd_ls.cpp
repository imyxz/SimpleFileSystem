#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
class CmdLs:public IRunnable {
public:
	int run(int argc, string* argv) override {
		INode * inode;
		if (argc >= 1) {
			string filepath = argv[0];
			Dir curDir = Dir(UserContext::cur_dir_id);
			inode = PathHelper::GetINodeFromPath(curDir,filepath,false);
			if (inode == 0) {
				cerr << filepath << "not exist!";
				return -1;
			}
		}
		else {
			inode = new Dir(UserContext::cur_dir_id);
		}
		Dir cur = Dir(*inode);
		auto entries = cur.getEntries();
		for (auto entry : entries) {
			cout << entry.name << "\t" << entry.inode_id << endl;
		}
		delete inode;
		return 0;
	}
};