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
		"�г���Ŀ¼�µ��ļ�"
		});
	parser.addEntry("mkdir", ArgEntry{
		(IRunnable*)&mkdir,
		"����Ŀ¼��֧�ֵݹ鴴����"
		});
	parser.addEntry("cd", ArgEntry{
		(IRunnable*)&cd,
		"�ı䵱ǰ����Ŀ¼"
		});
	parser.addEntry("exit", ArgEntry{
		(IRunnable*)&exit,
		"�˳�shell"
		});
	parser.addEntry("touch", ArgEntry{
		(IRunnable*)&touch,
		"�ı��ļ�����ʱ�䣬�ļ�������ʱ�򴴽�"
		});
	parser.addEntry("read", ArgEntry{
		(IRunnable*)&read,
		"�����ļ�����"
		});
	parser.addEntry("write", ArgEntry{
		(IRunnable*)&write,
		"д���ļ�����"
		});
	parser.addEntry("su", ArgEntry{
		(IRunnable*)&su,
		"�л��û�"
		});
	parser.addEntry("adduser", ArgEntry{
		(IRunnable*)&adduser,
		"�½��û�"
		});
	parser.addEntry("users", ArgEntry{
		(IRunnable*)&users,
		"�鿴�û��б�"
		});
	parser.addEntry("chmod", ArgEntry{
		(IRunnable*)&chmod,
		"�����ļ�Ȩ��"
		});
	parser.addEntry("chown", ArgEntry{
		(IRunnable*)&chown,
		"�����ļ�������"
		});
	parser.addEntry("delete", ArgEntry{
		(IRunnable*)&_delete,
		"ɾ���ļ�"
		});
	parser.addEntry("rename", ArgEntry{
		(IRunnable*)&rename,
		"�������ļ�"
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