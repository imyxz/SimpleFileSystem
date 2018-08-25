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