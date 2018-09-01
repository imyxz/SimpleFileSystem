#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"inode.h"
#include"dir.h"
#include <string>
#include<vector>
#include "consts.h"
using namespace std;
class PathRoute:public vector<string>{
public:
	bool startFromRoot = false;
};
class PathHelper {
public:
	static INode * GetINodeFromPath(const Dir & curDir, const PathRoute & route);
	static void GetPathRoute(const string & path, PathRoute & route);
	static INode * MakeDir(const Dir & curDir, const PathRoute & route);
};