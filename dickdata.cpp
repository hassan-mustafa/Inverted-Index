#include<set>
#include<cmath>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<numeric>
#include <string.h>
#include <dirent.h>
#include <ctime>
using namespace std;
const int MAX_CHAR = 26;
struct trie {
	trie* child[MAX_CHAR];
	bool isLeaf;
	int id = -1;
	set <int> ids;
	set <int> t;
	trie() {
		memset(child, 0, sizeof(child));
		isLeaf = 0;
	}
	void insert(char *str, int z) {
		if (*str == '\0')
		{
			isLeaf = 1;
			id = z;
			ids.insert(id);
		}
		else {
			int cur = *str - 'a';
			if (child[cur] == 0)
				child[cur] = new trie();
			child[cur]->insert(str + 1, z);
		}
	}
	set <int> wordExist(char* str) {
		if (*str == '\0')
			return ids;
		int cur = *str - 'a';
		if (child[cur] == 0)
			return t;	// such path don't exist
		return child[cur]->wordExist(str + 1);
	}
};
void loaddir(trie &b,vector<string> &test){
	DIR *dir;
	struct dirent *ent;
	int count = 0;
	int id = 0;
	clock_t start = clock();
	if ((dir = opendir("C:\\Users\\Hassan Mustafa\\Documents\\questions")) != NULL) {
		/* print all the files and directories within directory */
	
		while ((ent = readdir(dir)) != NULL) {
			if (count > 1)
			{ 
				test.push_back(ent->d_name);
			}
			count++;
		}
		ifstream file;
		string word;
		char *z = new char[MAX_CHAR];
		for (int j = 0; j < test.size(); j++)
		{
			file.open("C:\\Users\\Hassan Mustafa\\Documents\\questions\\" + test[j]);
			while (file >> word)
			{
				int q = 0;
				for (int i = 0; i < word.length(); i++)
				{
					if ((word[i] >= 65 && word[i] <= 90)
						|| (word[i] >= 97 && word[i] <= 122))
					{
						if (word[i] >= 65 && word[i] <= 92)
							word[i] += 32;
						z[q] = word[i];
						q++;
					}
				}
				z[q] = '\0';
				if (q != 0)
					b.insert(z, j);
			}
			file.close();
			cout << j << endl;
		}		
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("");
		return;
	}
	clock_t end = clock();
	cout << "Time consumed = " << ((double)end - start) / CLOCKS_PER_SEC << " seconds" << endl;
}
void find_word(set<int> &t, string q, trie b)
{
	clock_t start = clock();
	char *z = new char[MAX_CHAR];
	for (int i = 0; i < q.length(); i++)
	{
		if (q[i] >= 65 && q[i] <= 92) q[i] += 32;
		z[i] = q[i];
	}
	z[q.length()] = '\0';
	t = b.wordExist(z);
	clock_t end = clock();
	cout << "Time consumed = " << ((double)end - start) / CLOCKS_PER_SEC << " seconds" << endl;
}
void openfolders(vector<string> t,int open)
{
	ifstream tick;
	cout << t[open] << endl;
	tick.open("C:\\Users\\Hassan Mustafa\\documents\\questions\\" + t[open]);
	string word;
	while (tick >> word)
	{
		cout << word << endl;
	}
	tick.close();
}
int main()
{
	trie root;
	set<int> index;
	vector <string> t;
	loaddir(root,t);
	string search;
	cout << "search: " << endl;
	getline(cin, search);
	find_word(index, search, root);
	cout << "exists in:" << endl;
	for (int x : index) {
		cout << "document id:" << x << endl;
	}
	cout << "choose to open document:"<<endl;
	int openfolder;
	cin >> openfolder;
	openfolders(t,openfolder);
}