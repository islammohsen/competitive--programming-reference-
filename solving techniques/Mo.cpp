#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 1e5 + 5;
const int block_size = 350;

class query
{
public:
	int l, r, id;
	query(int l, int r, int id)
	{
		this->l = l;
		this->r = r;
		this->id = id;
	}
	bool operator < (const query &obj)
	{
		if(l == obj.l && r == obj.r)
			return id < obj.id;
		return make_pair(l / block_size, r) < make_pair(obj.l / block_size, obj.r);
	}
};

//datastructure
int freq[N], arr[N], sol;

void add(int pos) //add value at pos to data structure
{
}

void remove(int pos) //remove value at pos from data structure
{
}

int get_answer() //extract the current answer of the data structure
{
}

vector<int> mo_algorithm(vector<query> queries)
{
	sort(queries.begin(), queries.end());
	vector<int> answers = vector<int>(queries.size());
	int l = 0, r = -1;
	for(auto &q: queries)
	{
		int cur_l = q.l, cur_r = q.r;
		while(l > cur_l)
		{
			add(--l);
		}
		while(r < cur_r)
		{
			add(++r);
		}
		while(l < cur_l)
		{
			remove(l++);
		}
		while(r > cur_r)
		{
			remove(r--);
		}
		answers[q.id] = get_answer();
	}
	return answers;
}


int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	return 0;
}
