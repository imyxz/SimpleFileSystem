#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
#include "user_helper.h"
class CmdAdduser :public IRunnable {
public:
	int run(int argc, string* argv) override {
		if (argc >= 1) {
			string username = argv[0];
			ID_T target = UserHelper::FindUser(username);
			if (target != 0) {
				cerr << "user already exist" << endl;
				return -1;
			}
			target = UserHelper::AddUser(username);
			cout << "Successfully add user. user id:" << target << endl;
			return 0;
		}
		else {
			return -1;
		}
	}
};