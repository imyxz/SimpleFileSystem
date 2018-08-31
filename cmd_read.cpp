#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
#include <iostream>
using namespace std;
class CmdRead :public IRunnable {
public:
	int run(int argc, string* argv) override {
		if (argc >= 1) {
			string filepath = argv[0];
			Dir curDir = Dir(UserContext::cur_dir_id);
			PathRoute route;
			PathHelper::GetPathRoute(filepath, route);
			INode * inode = PathHelper::GetINodeFromPath(curDir, route);
			if (inode == 0) {
				cerr << "file is not exist!" << endl;
				return -1;
			}
			if (inode->GetType() != INodeType::kFILE) {
				cerr << "path is not a file!" << endl;
				return -1;
			}
			if (!inode->HasPermissionRead()) {
				cerr << "permission deny" << endl;
				return -1;
			}
			File file = File(*inode);
			ifstream in;
			file.getIfStream(in);
			const int buffer_size = 4096;
			char * buffer = new char[buffer_size + 1];
			while (in.good()) {
				in.get(buffer, buffer_size,'\0');
				buffer[buffer_size] = '\0';
				cout << buffer;
			}
			delete[] buffer;
			in.close();
			file.UpdateATime();
			return 0;
		}
		else {
			return -1;
		}
	}
};