#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
#include <iostream>
using namespace std;
class CmdWrite :public IRunnable {
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
				cerr << "path is not a file!";
				return -1;
			}
			if (!inode->HasPermissionRead()) {
				cerr << "permission deny" << endl;
				return -1;
			}
			File file = File(*inode);
			ofstream out;
			file.getOfStream(out);
			const int buffer_size = 4096;
			char * buffer = new char[buffer_size + 1];
			do {
				cin.get(buffer, buffer_size, '\0');
				buffer[buffer_size] = '\0';
				out << buffer;
			} while (cin.good());
			//»Ö¸´×´Ì¬
			cin.ignore();
			cin.clear();
			delete[] buffer;
			out.close();
			file.UpdateMTime();
			return 0;
		}
		else {
			return -1;
		}
	}
};