#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "types.h"
#include "consts.h"
struct DirectoryEntry
{
	ID_T inode_id;
	BOOL_T is_used;
	CHAR_T name[kDIRECTORY_ENTRY_NAME_LENGTH  +1];
};