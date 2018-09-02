#define _CRT_SECURE_NO_WARNINGS
#include "inode_helper.h"
#include "cmd_ls.cpp"
#include "cmd_mkdir.cpp"
#include "cmd_cd.cpp"
#include "cmd_exit.cpp"
#include "cmd_touch.cpp"
#include "cmd_read.cpp"
#include "cmd_write.cpp"
#include "cmd_su.cpp"
#include "cmd_adduser.cpp"
#include "cmd_users.cpp"
#include "cmd_chmod.cpp"
#include "cmd_chown.cpp"
#include "cmd_delete.cpp"
#include "cmd_rename.cpp"
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
	CmdAdduser adduser;
	CmdCd cd;
	CmdChmod chmod;
	CmdChown chown;
	CmdExit exit;
	CmdLs ls;
	CmdMkdir mkdir;
	CmdRead read;
	CmdSu su;
	CmdTouch touch;
	CmdUsers users;
	CmdWrite write;
	CmdDelete _delete;
	CmdRename rename;
	parser.addEntry("ls", ArgEntry{
		(IRunnable*)&ls,
		"列出该目录下的文件"
		});
	parser.addEntry("mkdir", ArgEntry{
		(IRunnable*)&mkdir,
		"创建目录（支持递归创建）"
		});
	parser.addEntry("cd", ArgEntry{
		(IRunnable*)&cd,
		"改变当前工作目录"
		});
	parser.addEntry("exit", ArgEntry{
		(IRunnable*)&exit,
		"退出shell"
		});
	parser.addEntry("touch", ArgEntry{
		(IRunnable*)&touch,
		"改变文件访问时间，文件不存在时则创建"
		});
	parser.addEntry("read", ArgEntry{
		(IRunnable*)&read,
		"读入文件内容"
		});
	parser.addEntry("write", ArgEntry{
		(IRunnable*)&write,
		"写入文件内容"
		});
	parser.addEntry("su", ArgEntry{
		(IRunnable*)&su,
		"切换用户"
		});
	parser.addEntry("adduser", ArgEntry{
		(IRunnable*)&adduser,
		"新建用户"
		});
	parser.addEntry("users", ArgEntry{
		(IRunnable*)&users,
		"查看用户列表"
		});
	parser.addEntry("chmod", ArgEntry{
		(IRunnable*)&chmod,
		"更改文件权限"
		});
	parser.addEntry("chown", ArgEntry{
		(IRunnable*)&chown,
		"更改文件所有者"
		});
	parser.addEntry("delete", ArgEntry{
		(IRunnable*)&_delete,
		"删除文件"
		});
	parser.addEntry("rename", ArgEntry{
		(IRunnable*)&rename,
		"重命名文件"
		});
	string input;
	cout << UserContext::user_name<<":"<< UserContext::GetCurPath() << "# ";
	while (getline(cin, input)) {
		int code = parser.run(input);
		if (code == -2) {
			break;
		}
		if (code != 0) {
			cout << code << endl;
		}
		cout << UserContext::user_name << ":" << UserContext::GetCurPath() << "# ";
	}
	INodeHelper::Save();
	
	//system("pause");
}