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
		"�г���Ŀ¼�µ��ļ�"
		});
	parser.addEntry("mkdir", ArgEntry{
		(IRunnable*)&CmdMkdir(),
		"����Ŀ¼��֧�ֵݹ鴴����"
		});
	parser.addEntry("cd", ArgEntry{
		(IRunnable*)&CmdCd(),
		"�ı䵱ǰ����Ŀ¼"
		});
	parser.addEntry("exit", ArgEntry{
		(IRunnable*)&CmdExit(),
		"�˳�shell"
		});
	parser.addEntry("touch", ArgEntry{
		(IRunnable*)&CmdTouch(),
		"�ı��ļ�����ʱ�䣬�ļ�������ʱ�򴴽�"
		});
	parser.addEntry("read", ArgEntry{
		(IRunnable*)&CmdRead(),
		"�����ļ�����"
		});
	parser.addEntry("write", ArgEntry{
		(IRunnable*)&CmdWrite(),
		"д���ļ�����"
		});
	parser.addEntry("su", ArgEntry{
		(IRunnable*)&CmdSu(),
		"�л��û�"
		});
	parser.addEntry("adduser", ArgEntry{
		(IRunnable*)&CmdAdduser(),
		"�½��û�"
		});
	parser.addEntry("users", ArgEntry{
		(IRunnable*)&CmdUsers(),
		"�鿴�û��б�"
		});
	parser.addEntry("chmod", ArgEntry{
		(IRunnable*)&CmdChmod(),
		"�����ļ�Ȩ��"
		});
	parser.addEntry("chown", ArgEntry{
		(IRunnable*)&CmdChown(),
		"�����ļ�������"
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