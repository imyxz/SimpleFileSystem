#pragma once
#include "types.h"
#include "dir.h"
#include "path_trace.h"
#include "user_helper.h"
class UserContext {
public:
	static ID_T user_id;
	static ID_T cur_dir_id;
	static PathTrace path_trace;
	static string user_name;
	static void PushDir(const Dir & dir, const string & name) {
		cur_dir_id = dir.GetID();
		path_trace.push(dir, name);
	}
	static string GetCurPath() {
		return path_trace.getPath();
	}
	static ID_T LoginAs(string name) {
		ID_T target = UserHelper::FindUser(name);
		if (target == 0) {
			return 0;
		}
		user_id = target;
		user_name = name;
		return target;
	}
};