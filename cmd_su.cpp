#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
class CmdSu :public IRunnable {
public:
	int run(int argc, string* argv) override {
		if (argc >= 1) {
			string username = argv[0];
			ID_T target = UserContext::LoginAs(username);
			if (target == 0) {
				cerr << "No such user" << endl;
				return -1;
			}
			return 0;
		}
		else {
			return -1;
		}
	}
};