#pragma once
#include"inode.h"
#include"types.h"
#include<sstream>
#include<string>
#include<fstream>
#include"consts.h"
using namespace std;
class INodeLoader {
public:
	static string GetINodePath(ID_T inode_id);
	static INodeStruct LoadINode(ID_T inode_id);
	static BOOL_T IsNodeExist(ID_T inode_id);
	static void SaveINode(const INodeStruct & inode);
};
class ContentLoader {
public:
	static string GetContentPath(ID_T content_id);
	static ifstream & GetContentIfStream(ID_T content_id);
	static ofstream & GetContentOfStream(ID_T content_id);
	static void CreateContentFile(ID_T content_id);
};