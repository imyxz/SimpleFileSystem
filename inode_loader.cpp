#include"inode_loader.h"
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
ifstream & ContentLoader::GetContentIfStream(ID_T content_id) {
	string filename = ContentLoader::GetContentPath(content_id);
	ifstream * in = new ifstream();
	in->open(filename, ios::in | ios::binary);
	return *in;
}
ofstream & ContentLoader::GetContentOfStream(ID_T content_id) {
	string filename = ContentLoader::GetContentPath(content_id);
	ofstream * out = new ofstream();
	out->open(filename, ios::out | ios::binary | ios::app);
	return *out;
}
void ContentLoader::CreateContentFile(ID_T content_id) {
	string filename = ContentLoader::GetContentPath(content_id);
	ofstream out;
	out.open(filename, ios::out | ios::binary | ios::trunc);
	out.close();
}