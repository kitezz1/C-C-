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
void insert(vector<int> & hape, const int value) {
	
	int star = 0;
	int holeIndex = hape.size() - 1;
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > star && hape[parent] < value) {
		hape[holeIndex] = hape[parent];
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	hape[holeIndex] = value;
}
void print(const vector<int> &heap) {
	for (auto cc : heap)
		cout << cc << " ";
	cout << endl;
}

void swap(vector<int>&heap, int cur, int parent) {
	if (cur == parent)
		return;
	int tmp = heap[cur];
	heap[cur] = heap[parent];
	heap[parent] = tmp;
}
void create(vector<int> &heap) {
	int cur;
	int parent;
	for (int i = 0; i < heap.size(); i++) {
		cur = i;
		parent = (i - 1) / 2;
		while (heap[cur] > heap[parent]) {
			swap(heap, cur, parent);
			cur = parent;
			parent = (cur - 1) / 2;
		}
	}
}
void adjust(vector<int> &heap, int size) {//size是个数 不是索引
	int cur = 0;
	int left = 2 * cur + 1;
	int right = 2 * (cur + 1);
	while (left < size) {
		int largest;
		if (right < size && heap[left] < heap[right])
			largest = right;
		else
			largest = left;
		if (heap[cur] > heap[largest]) {
			break;
		}
		swap(heap, largest, cur);
		cur = largest;
		left = 2 * cur + 1;
		right = 2 * (cur + 1);
	}
}
void merge(vector<int>&heap, int star, int mid, int end) {
	vector<int>tmp;
	int len = 0;
	int i = star;
	int j = mid+1;
	while (i<=mid && j<=end)
	{
		if (heap[i] > heap[j]) {
			tmp.push_back(heap[j++]);
		}
		else
		{
			tmp.push_back(heap[i++]);
		}
	}
	while (i <= mid)
		tmp.push_back(heap[i++]);
	while (j <= end)
		tmp.push_back(heap[j++]);
	for (auto &cc : tmp)
		heap[star++] = cc;
}
void mergesort(vector<int> &heap, int star,  int end) {
	if (star >= end)
		return;
	int mid = (star + end) / 2;
	mergesort(heap, star, mid);
	mergesort(heap, mid + 1, end);
	merge(heap, star, mid, end);
}
int find_flag(vector<int>&heap, int star, int end) {
	
	while (star < end) {
		while (heap[end] >= heap[star] && star<end)
			end--;
		swap(heap, star, end);
		while ( heap[star] <= heap[end] && star<end)
			star++;
		swap(heap, star, end);
		
		
	}
	return star;
}
void quick(vector<int>&heap,int star, int end) {
	if (star >= end)
		return;
	int mid = find_flag(heap, star, end);
	
	quick(heap, star, mid-1);
	quick(heap, mid + 1, end);

}

int main() {
	//vector<int> heap = { 68,31,65,21,24,32,26,19,16,13,50 };
	vector<int> heap = { 9,8,7,21,6,5,4,4,3,2,1 };
	print(heap);
	/*{
	create(heap);
	print(heap);
	int size = heap.size();
	while (size > 1)
	{
		size--;
		swap(heap, 0, size);
		adjust(heap, size);
	}
	print(heap); 
	}*/
	{
		mergesort(heap, 0, 10); 
		print(heap);
	}
	/*{
		quick(heap, 0, 10);
		print(heap);
	}*/
	return 0;
}
