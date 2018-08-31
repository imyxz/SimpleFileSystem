#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
#include "user_helper.h"
class CmdUsers :public IRunnable {
public:
	int run(int argc, string* argv) override {
		vector<UserEntry> users = UserHelper::GetUserList();
		for (UserEntry user : users) {
			cout << user.user_id << "\t" << user.name << endl;
		}
		return 0;
	}
};