#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
class CmdTouch :public IRunnable {
public:
	int run(int argc, string* argv) override {
		if (argc >= 1) {
			string filepath = argv[0];
			Dir curDir = Dir(UserContext::cur_dir_id);
			PathRoute route;
			PathHelper::GetPathRoute(filepath, route);
			if (route.size() == 0) {
				return -1;
			}
			string filename = route.back();
			route.pop_back();
			INode * inode = PathHelper::GetINodeFromPath(curDir, route);
			if (inode == 0) {
				cerr << "path is not exist!" << endl;
				return -1;
			}
			if (inode->GetType() != INodeType::kDIR) {
				cerr << "path is not a dir!";
				return -1;
			}
			Dir parentDir = Dir(*inode);
			if (!parentDir.HasPermissionWrite()) {
				cerr << "permission deny" << endl;
				return -1;
			}
			ID_T cur_id = parentDir.findEntry(filename);
			if (cur_id != 0) {
				INode inode = INode(cur_id);
				inode.UpdateATime();
				cout << "access file success! inode id:" << cur_id << endl;
			}
			else {
				File file = INodeHelper::CreateFile();
				parentDir.addEntry(file, filename);
				cout << "create file success! inode id:" << file.GetID() << endl;
			}

			return 0;
		}
		else {
			return -1;
		}
	}
};