#pragma once
#include "types.h"
const SIZE_T DIRECTORY_ENTRY_NAME_LENGTH = 251;
struct DirectoryEntry
{
	ID_T inode_id;
	BOOL_T is_used;
	CHAR_T name[DIRECTORY_ENTRY_NAME_LENGTH  +1];
};