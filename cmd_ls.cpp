#include"inode_helper.h"
#include"path_helper.h"
#include "arg_parser.h"
#include "user_context.h"
class CmdLs:public IRunnable {
public:
	int run(int argc, string* argv) override {
		INode * inode;
		if (argc >= 1) {
			string filepath = argv[0];
			Dir curDir = Dir(UserContext::cur_dir_id);
			PathRoute route;
			PathHelper::GetPathRoute(filepath, route);
			inode = PathHelper::GetINodeFromPath(curDir, route);
			if (inode == 0) {
				cerr << filepath << "not exist!";
				return -1;
			}
		}
		else {
			inode = new Dir(UserContext::cur_dir_id);
		}
		if (inode->GetType() != INodeType::kDIR) {
			cerr << argv[0] << "is not a dir!";
			return -1;
		}
		Dir cur = Dir(*inode);
		auto entries = cur.getEntries();
		cout << "inode id\tpermission\towner\tname" << endl;
		for (auto entry : entries) {
			INode inode = INode(entry.inode_id);
			cout << entry.inode_id <<"\t"
				<<inode.GetOwnerPermission() << inode.GetGlobalPermission()<<"\t"
				<<UserHelper::FindUserByID(inode.GetINode()->owner_id)<<"\t" 
				<<entry.name << "\t" 
				 << endl;
		}
		delete inode;
		return 0;
	}
};