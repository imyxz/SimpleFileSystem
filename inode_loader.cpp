#include"inode_loader.h"
#include<cstdio>
string INodeLoader::GetINodePath(ID_T inode_id) {
	stringstream sstream;
	sstream << kINodeDir << "/" << inode_id << ".inode";
	return sstream.str();
}
INodeStruct INodeLoader::LoadINode(ID_T inode_id) {
	string filename = INodeLoader::GetINodePath(inode_id);
	ifstream in;
	in.open(filename, ios::in | ios::binary);
	in.seekg(0, in.beg);
	INodeStruct inode;
	in.read((char *)&inode, sizeof(inode));
	in.close();
	return inode;
}
BOOL_T INodeLoader::IsNodeExist(ID_T inode_id) {
	string filename = INodeLoader::GetINodePath(inode_id);
	ifstream check(filename);
	return bool(check);
}
void INodeLoader::SaveINode(const INodeStruct & inode) {
	string filename = INodeLoader::GetINodePath(inode.id);
	ofstream out;
	out.open(filename, ios::out | ios::binary | ios::trunc);
	out.seekp(0, out.beg);
	out.write((char *)&inode, sizeof(inode));
	out.close();
}
string ContentLoader::GetContentPath(ID_T content_id) {
	stringstream sstream;
	sstream << kContentDir << "/" << content_id << ".content";
	return sstream.str();
}
void ContentLoader::GetContentIfStream(ID_T content_id, ifstream & in) {
	string filename = ContentLoader::GetContentPath(content_id);
	in.open(filename, ios::in | ios::binary);
}
void ContentLoader::GetContentOfStream(ID_T content_id, ofstream & out) {
	string filename = ContentLoader::GetContentPath(content_id);
	out.open(filename, fstream::binary | fstream::out | fstream::in);
}
void ContentLoader::CreateContentFile(ID_T content_id) {
	string filename = ContentLoader::GetContentPath(content_id);
	ofstream out;
	out.open(filename, ios::out | ios::binary | ios::trunc);
	out.close();
}
void ContentLoader::EmptyContentFile(ID_T content_id) {
	string filename = ContentLoader::GetContentPath(content_id);
	remove(filename.c_str());
	ContentLoader::CreateContentFile(content_id);
}