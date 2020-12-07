#include "FirstAndFollow.h"



/*****************************************************************************
* @Name : getIndex
* @Brief : Get index from production rules
* @Inparam : 
* @Outparam : 
*****************************************************************************/
multimap<string, string> getIndex(const vector<string>& production) {
	multimap<string, string> index;

	size_t productionSize = production.size();
	for (int i = 0; i < productionSize; i++) {
		
	}

	return index;
}




struct productionRule getNonTerminal(const vector<string>& production) {
	/// <summary>
	/// ����ֵ
	/// </summary>
	productionRule rule;
	/// <summary>
	/// ���ű�
	/// </summary>
	set<string> symbol;
	bool continueScann=true;
	/// <summary>
	/// First��
	/// </summary>
	map<string, set<string>> first;
	/// <summary>
	/// �ս��
	/// </summary>
	set<string> terminal;
	/// <summary>
	/// ���ս��
	/// </summary>
	set<string> nonTerminal;
	/// <summary>
	/// ���ս������ʽ����
	/// </summary>
	map<string, set<string>> index;
	string nowProduction,nowRecordString;
	size_t productionSize = production.size();
	//��ȡ���ս��������ʽ����
	for (int i = 0; i < productionSize; i++) {
		nowProduction = production[i];
		bool readString=false;
		string::size_type subScript = nowProduction.find_first_of(" ");

		if(subScript==nowProduction.npos){
			throw "Grammar analyze wrong!";
		}
		string 	nowNonTerminal = nowProduction.substr(0, subScript);
		nonTerminal.insert(nowNonTerminal);
		symbol.insert(nowNonTerminal);
		subScript = nowProduction.find_first_of("->");
		if (subScript == nowProduction.npos) {
			throw "Grammar analyze wrong!";
		}
		for (size_t j = subScript+2; j < nowProduction.size(); j++) {
			if (nowProduction.at(j) == '|')
				continue;
			else if (nowProduction.at(j) !=' '&&readString==false) {
				readString = true;
				nowRecordString = nowProduction.at(j);
			}
			else if (nowProduction.at(j) != ' '&&readString == true) {
				string appendStr(1,nowProduction.at(j));
				nowRecordString.append(appendStr);
			}
			else if ((nowProduction.at(j) == ' ')&&readString == true) {
				readString = false;
				symbol.insert(nowRecordString);
				terminal.insert(nowRecordString);
				map<string, set<string>>::iterator iter = index.find(nowNonTerminal);
				if(iter==index.end())
					index.insert(pair<string,set<string>>(nowNonTerminal,set<string>{nowRecordString}));
				else {
					set<string> productionSet = iter->second;
					productionSet.insert(nowRecordString);
					index.insert(pair<string, set<string>>(nowNonTerminal, productionSet));
				}
			}

		}
	}
	for (const auto& deleteString:nonTerminal) {
		terminal.erase(deleteString);
	}

	while (continueScann) {
		continueScann = false;
		//����һ����ű�
		for (const auto& nowSymbol : symbol) {
			//������ս����FIRST(X)={X}
			if (terminal.find(nowSymbol) != terminal.end()) {
				
				map<string, set<string>>::iterator iter = first.find(nowSymbol);
				//first����û��
				if (iter == first.end()) {
					first.insert(pair<string, set<string>>(nowSymbol, set<string>{nowRecordString}));
					continueScann = true;
				}
			}
			//����Ƿ��ս��
			else if (nonTerminal.find(nowSymbol) != nonTerminal.end()) {
				size_t size;
				//Ѱ�ҹ���
				map<string, set<string>>::iterator indexIter = index.find(nowSymbol);
				if(indexIter==index.end())
					throw "Grammar analyze wrong!";
				else {
					//vector<string> nowNonTerminalFirst = indexIter->second;
					//�ҵ��Ҳ�
					set<string> nowFirst;
					map<string, set<string>>::iterator firstIter = first.find(nowSymbol);
					//���ڵ��Ҳ��ǿ�
					if (firstIter == index.end())
						size=0;
					else {
						nowFirst = firstIter->second;
						size = nowFirst.size();
					}
					set<string> rightSection = indexIter->second;
					for (auto nowSection : rightSection) {
						nowFirst.insert(nowSection);
						//Y�Ƿ��ս��
						if (nonTerminal.find(nowSection) != nonTerminal.end()) {
							set<string> YFirst= first.find(nowSection)->second;
							for (auto nowYSection : YFirst) {
								if(nowYSection!="~")
									nowFirst.insert(nowYSection);
							}
						}
					}
					if (size != nowFirst.size())
						continueScann = true;

					first.insert(pair<string, set<string>>(nowSymbol,nowFirst));
				}
			}
			else throw "Grammar analyze wrong!";
		}

		
	}
	

	return rule;
}



set<string> getFirst(const vector<string>& production) {
	set<string> first;
	bool flag = true;
	multimap<string, string> mul;
	return first;
}

