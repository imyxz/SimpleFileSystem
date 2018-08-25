#pragma once
class IRunnable {
public:
	virtual int run(int, string*) { return -1; }
};