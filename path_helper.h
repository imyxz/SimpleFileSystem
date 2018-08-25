#pragma once
#include"inode.h"
#include"dir.h"
#include <string>
#include "consts.h"
using namespace std;
class PathHelper {
public:
	static INode * GetINodeFromPath(const Dir & curDir, const string & path,const bool mkdir_mode);
};