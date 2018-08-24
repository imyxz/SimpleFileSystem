#pragma once
#include"inode.h"
#include"types.h"
#include<sstream>
#include<string>
#include<fstream>
using namespace std;
const string kINodeDir = "inode";
const string kContentDir = "content";
class INodeLoader {
public:
	static string GetINodePath(ID_T inode_id) {
		stringstream sstream;
		sstream <<kINodeDir<<"/"<< inode_id << ".inode";
		return sstream.str();
	}
	static INodeStruct LoadINode(ID_T inode_id) {
		string filename = INodeLoader::GetINodePath(inode_id);
		ifstream in;
		in.open(filename, ios::in | ios::binary);
		in.seekg(0, in.beg);
		INodeStruct inode;
		in.read((char *)&inode, sizeof(inode));
		in.close();
		return inode;
	}
	static BOOL_T IsNodeExist(ID_T inode_id) {
		string filename = INodeLoader::GetINodePath(inode_id);
		ifstream check(filename);
		return bool(check);
	}
	static void SaveINode(INodeStruct inode) {
		string filename = INodeLoader::GetINodePath(inode.id);
		ofstream out;
		out.open(filename, ios::out | ios::binary | ios::trunc);
		out.seekp(0, out.beg);
		out.write((char *)&inode, sizeof(inode));
		out.close();
	}
};
class ContentLoader {
public:
	static string GetContentPath(ID_T content_id) {
		stringstream sstream;
		sstream << kContentDir << "/" << content_id << ".content";
		return sstream.str();
	}
	static ifstream & GetContentIfStream(ID_T content_id) {
		string filename = ContentLoader::GetContentPath(content_id);
		ifstream * in = new ifstream();
		in->open(filename, ios::in | ios::binary);
		return *in;
	}
	static ofstream & GetContentOfStream(ID_T content_id) {
		string filename = ContentLoader::GetContentPath(content_id);
		ofstream * out = new ofstream();
		out->open(filename, ios::out | ios::binary | ios::app);
		return *out;
	}
	static void CreateContentFile(ID_T content_id) {
		string filename = ContentLoader::GetContentPath(content_id);
		ofstream out;
		out.open(filename, ios::out | ios::binary | ios::trunc);
		out.close();
	}
};