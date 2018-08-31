#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
class CmdExit :public IRunnable {
public:
	int run(int argc, string* argv) override {
		return -2;
	}
};