#pragma once
#include<set>
#include<string>
#include <vector>
#include <map>
using namespace std;

/*

*/
struct productionRule {
	/*
		first��
	*/
	multimap<string, string> first;
	/*
		����ʽ����
	*/
	multimap<string, string> index;
	/*
		���ս��
	*/
	set<string> nonTerminal;
};

set<string> getFirst(const vector<string>&);
multimap<string, string> getIndex(const vector<string>& production);
//set<string> getNonTerminal(const vector<string>& production);
struct productionRule getNonTerminal(const vector<string>& production);