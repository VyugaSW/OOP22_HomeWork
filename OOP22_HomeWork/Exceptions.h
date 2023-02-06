
#include <iostream>
#include <Windows.h>

using namespace std;

// Base class of exception classes
class BaseException {
protected:
	string explanation; // Explanation to error
public:
	virtual string show() = 0;
};



class NegativeIndex final : public BaseException {
public:
	NegativeIndex(string text = "ERROR. Negative Index\n") {
		explanation = text;
	}
	string show() { return explanation; }
};

class OutsideIndex final : public BaseException {
public:
	OutsideIndex(string text = "ERROR. Index outside array\n") {
		explanation = text;
	}

	string show() { return explanation; }
};

class NotOpenFile final : public BaseException {
public:
	NotOpenFile(string text = "ERROR. File wasn' open.\n Maybe the path is wrong\n") {
		explanation = text;
	}

	string show() { return explanation; }
};