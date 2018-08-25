#pragma once
#include"inode.h"
#include"dir.h"
#include <string>
#include<vector>
#include "consts.h"
using namespace std;
class PathRoute:public vector<string>{};
class PathHelper {
public:
	static INode * GetINodeFromPath(const Dir & curDir, const string & path);
	static void GetPathRoute(const string & path, PathRoute & route);
	static INode * MakeDir(const Dir & curDir, const string & path);
};