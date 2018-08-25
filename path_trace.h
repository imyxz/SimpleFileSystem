#pragma once
#include "types.h"
#include "dir.h"
#include "consts.h"
#include <list>
struct PathTraceEntry
{
	string name;
	Dir dir;
};
class PathTrace {
protected:
	list<PathTraceEntry> traces;
public:
	void push(const Dir & dir,const string & name);
	void format();
	string getPath() const;
};