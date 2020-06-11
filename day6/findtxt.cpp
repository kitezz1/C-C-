#include<iostream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include<sstream>
using namespace std;

class QueryResult;
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<line_no>>> wm;

};
TextQuery::TextQuery(ifstream& is):file(new vector<string>) {
	string text;
	while (getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word) {
			auto &lines = wm[word];
			if (!lines)
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}

class QueryResult {
	using line_no = std::vector<std::string>::size_type;
	friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) :sought(s), lines(p), file(f){};
private:
	string sought;
	shared_ptr<set<line_no>> lines;
	shared_ptr<vector<string>> file;

};

QueryResult TextQuery::query(const string &sought) const {
	static shared_ptr<set<line_no>>nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}
ostream &print(ostream& os, const QueryResult& qr) {
	os << qr.sought << " counts " << qr.lines->size() << " time(s)" << endl;
	for (auto num : *qr.lines)
		os << "\t (line" << num + 1 << ")" << *(qr.file->begin() + num) << endl;
	return os;
}
void runQueries(ifstream &infile) {
	TextQuery tq(infile);
	string s;
	cin >> s;
	print(cout, tq.query(s)) << endl;
}
int main() {
	ifstream txt("C:\\Users\\HASEE\\Desktop\\word.txt");
	runQueries(txt);
	system("pause");
	return 0;
}
