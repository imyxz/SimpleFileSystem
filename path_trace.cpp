#include"path_trace.h"
#include"inode_helper.h"
#include "dir.h"
#include <sstream>
using namespace std;
void PathTrace::push(const Dir & dir, const string & name)
{
	if (dir.GetID() == INodeHelper::GetRootDir().GetID()) {
		traces.clear();
		format();
		return;
	}
	ID_T parent_id = dir.findEntry("..");
	if (parent_id == INodeHelper::GetRootDir().GetID()) {
		traces.clear();
		traces.push_back(PathTraceEntry{
			name,
			dir
			});
		format();
		return;
	}
	for (auto it = traces.begin(); it != traces.end();++it) {
		if (it->dir.GetID() == parent_id) {
			traces.erase(++it, traces.end());
			traces.push_back(PathTraceEntry{
				name,
				dir
				});
			format();
			return;
		}
	}
	//not found
	traces.clear();
	Dir curdir = dir;
	string curname;
	while (curdir.GetID() != kROOT_ID) {
		Dir parent = Dir(curdir.findEntry(".."));
		traces.push_front(PathTraceEntry{
			parent.findEntryName(curdir.GetID()),
			curdir
			});
		curdir = parent;
	}
	format();
	return;
	//throw new exception("path trace faild.");
}

void PathTrace::format()
{
	bool needFormat = false;
	for (auto & entry : traces) {
		if (entry.name == "." || entry.name == "..") {
			needFormat = true;
			break;
		}
	}
	if (needFormat) {
		Dir curDir = INodeHelper::GetRootDir();
		for (auto & entry : traces) {
			entry.name = curDir.findEntryName(entry.dir.GetID());
			curDir = entry.dir;
		}
	}
}

string PathTrace::getPath() const
{
	stringstream in;
	for (auto entry : traces) {
		in << "/"<<entry.name;
	}
	string path = in.str();
	if (path.length() == 0) {
		return "/";
	}
	else {
		return path;
	}
}

