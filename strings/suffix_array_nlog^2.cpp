class suffix_array
{
	vector<int> suf, group, tmp;
	string s;

	class comp
	{
	public:
		int h;
		vector<int> *group;
		comp(int h, vector<int> &group)
		{
			this->h = h;
			this->group = &group;
		}
		bool operator()(int i, int j)
		{
			if ((*group)[i] != (*group)[j])
				return (*group)[i] < (*group)[j];
			int v1 = (i + h < (*group).size()) ? (*group)[i + h] : 0;
			int v2 = (j + h < (*group).size()) ? (*group)[j + h] : 0;
			return v1 < v2;
		}
	};

	void update_groups(int n, int h)
	{
		tmp[0] = 0;
		for (int i = 1; i < n; i++)
			tmp[i] = tmp[i - 1] + comp(h, gro	up)(suf[i - 1], suf[i]);
		for (int i = 0; i < n; i++)
			group[suf[i]] = tmp[i];
	}

public:
	suffix_array(string s)
	{
		suf = vector<int>(s.size());
		group = vector<int>(s.size());
		tmp = vector<int>(s.size());
		this->s = s;
	}

	vector<int> build_suffix_array()
	{
		int n = s.size();
		for (int i = 0; i < n; i++)
			group[i] = s[i], suf[i] = i;
		sort(suf.begin(), suf.begin() + n, comp(0, group));
		update_groups(n, 0);
		for (int h = 1; tmp[n - 1] != n - 1; h <<= 1)
		{
			sort(suf.begin(), suf.begin() + n, comp(h, group));
			update_groups(n, h);
		}
		return suf;
	}
};
