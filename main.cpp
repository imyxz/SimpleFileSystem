#include "inode_helper.h"
#include "cmd_ls.cpp"
#include "cmd_mkdir.cpp"
#include "cmd_cd.cpp"
#include "cmd_exit.cpp"
#include "arg_parser.h"
#include "user_context.h"
#include <iostream>
using namespace std;
void test() {
	INodeHelper::Init();
	Dir root = INodeHelper::GetRootDir();
	auto newDir = INodeHelper::CreateDir(root.GetID(), "yinyinyin");
	auto entries = root.getEntries();
	for (auto entry : entries) {
		cout << entry.name << endl;
	}
	ID_T tmp = root.findEntry("yinyinyin");
	cout << tmp << endl;
	cout << "hello world!" << endl;
}
int main(int argc, char ** argv) {
	INodeHelper::Init();
	UserContext::cur_dir_id = 1;
	ArgParser parser;
	parser.addEntry("ls", ArgEntry{
		(IRunnable*)&CmdLs(),
		"列出该目录下的文件"
		});
	parser.addEntry("mkdir", ArgEntry{
		(IRunnable*)&CmdMkdir(),
		"创建目录（支持递归创建）"
		});
	parser.addEntry("cd", ArgEntry{
		(IRunnable*)&CmdCd(),
		"改变当前工作目录"
		});
	parser.addEntry("exit", ArgEntry{
		(IRunnable*)&CmdExit(),
		"退出shell"
		});
	while (true) {
		string input;
		cout << UserContext::GetCurPath() << "# ";
		getline(cin, input);
		int code = parser.run(input);
		if (code != 0) {
			cout << code << endl;
		}
		
	}
	
	//system("pause");
}