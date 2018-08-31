#pragma once
#include "types.h"
#include "consts.h"
struct UserEntry
{
	ID_T user_id;
	BOOL_T is_used;
	CHAR_T name[kUSER_ENTRY_NAME_LENGTH + 1];
};