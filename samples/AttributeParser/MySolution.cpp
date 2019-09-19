#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

struct Tag
{
	map<string, Tag*> children;
	map<string, string> attributes;
	~Tag();
	// prase the string starting from 'start'
	// return the end pos
	int parse(const string& data, int start = 0);
	string getAtribute(const string& att);
};

Tag::~Tag()
{
	for (auto tag : children)
		delete tag.second;
}

int Tag::parse(const string& data, int start)
{
	while (start < (int)data.size())
	{
		start = data.find('<', start) + 1;
		if (data[start] == '/')
			return data.find('>', start) + 1;

		auto sp = data.find(' ', start);
		auto closing = data.find('>', start);
		if (sp == string::npos || sp > closing)
			sp = closing;
		auto Name = data.substr(start, sp - start);
		Tag* child = new Tag();
		// parse attributes		
		start = sp + 1;

		do
		{
			auto split = data.find(" = ", start);
			if (split > closing || split == string::npos)
				break;
			auto att_name = data.substr(start, split - start);
			start = split + 4;
			auto att_close = data.find('"', start);
			child->attributes[att_name] = data.substr(start, att_close - start);
			start = att_close + 1;
			if (data[start] == ' ')
				start++;


		} while (start < (int)closing);
		// recursion
		children[Name] = child;
		start = child->parse(data, closing + 1);

	}
	return start;
}

string Tag::getAtribute(const string& att)
{
	int search_pos = 0;
	Tag* tag = this;
	while (tag)
	{
		// extract name
		auto fpos = att.find('.', search_pos);
		if (fpos != string::npos)
		{
			auto node = tag->children.find(att.substr(search_pos, fpos - search_pos));
			if (node == tag->children.end())
				return "Not Found!";
			search_pos = fpos + 1;
			tag = node->second;

		}
		else
		{
			auto fpos = att.find('~', search_pos);
			if (fpos == string::npos)
				return "Not Found!";
			auto node = tag->children.find(att.substr(search_pos, fpos - search_pos));
			if (node == tag->children.end())
				return "Not Found!";
			search_pos = fpos + 1;
			tag = node->second;

			auto att_name = att.substr(search_pos, att.size() - search_pos);
			auto att = tag->attributes.find(att_name);
			if (att != tag->attributes.end())
				return att->second;
			return "Not Found!";
		}
	}

	return "Not Found!";
}

int solve() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int N, Q; // number of lines, num of queries
	cin >> N >> Q;
	string HRML;
	string s;
	cin.ignore();
	for (int line = 0; line < N; ++line)
	{
		std::getline(std::cin, s);
		HRML += s;
	}
	auto root = new Tag();
	root->parse(HRML);

	for (int q = 0; q < Q; ++q)
	{
		string s;
		cin >> s;
		cout << root->getAtribute(s) << endl;
	}

	delete root;

	return 0;
}