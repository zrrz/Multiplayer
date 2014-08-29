#include <iostream>

#pragma once

const int STRMAXSIZE = 100;

class string
{
	//friend std::istream& operator>>(std::istream& in, string& str);
public:
	string()
	{
		memset(contents, 0, STRMAXSIZE);
	}
	string(char contents[])
	{
		memset(this->contents, 0, STRMAXSIZE);
		strcpy_s(this->contents, contents);
	}

	~string() {}

	string operator=(char contents[])
	{
		strcpy_s(this->contents, contents);
		return *this;
	}
	string operator=(string str)
	{
		strcpy_s(this->contents, str.contents);
		return *this;
	}

	bool operator==(char str[])
	{
		if ( strcmp(contents, str) == 0 )
			return true;
		return false;
	}
	bool operator==(string str)
	{
		if ( strcmp(contents, str.contents) == 0 )
			return true;
		return false;
	}

	bool operator+=(char str[])
	{
		int size = strlen(contents);
		strcpy(this->contents+size, str);
	}
	bool operator+=(string str)
	{
		int size = strlen(contents);
		strcpy(contents+size, str.contents);
	}

	char& operator[](int index)
	{
		return contents[index];
	}

private:
	char contents[STRMAXSIZE];
};
/*
std::istream& operator>>(std::istream& in, string& str)
{
	in.getline(str.contents, STRMAXSIZE, ' ');
	return in;
}
*/
