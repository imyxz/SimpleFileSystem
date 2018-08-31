#pragma once
#include<string>
#include "types.h"
using namespace std;
const ID_T kINODE_MAXN = 65536;
const string kINODE_MAP_NAME = "inode_map";
const ID_T kCONTENT_MAXN = 65536;
const string kCONTENT_MAP_NAME = "content_map";
const string kPATH_DELIMITER = "/";
const string kINodeDir = "inode";
const string kContentDir = "content";
const SIZE_T kDIRECTORY_ENTRY_NAME_LENGTH = 251;
const SIZE_T kUSER_ENTRY_NAME_LENGTH = 251;
const ID_T kUSER_CONTENT_ID = 1;
const ID_T kROOT_ID = 1;