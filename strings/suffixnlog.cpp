class suffix_array
{
	vector<int> group, suf, tmp_suf, tmp_group, start_group, c[21], log;
	string s;
	int n;
	class comp
	{
		vector<int> *group;
	public:
		comp(vector<int> &group)
		{
			this->group = &group;
		}
		bool operator ()(int i, int j)
		{
			return (*group)[i] < (*group)[j];
		}
	};
	vector<int> build_suffix_array()
	{
		for (int i = 0; i < n; i++)
			suf[i] = i, group[i] = s[i];
		sort(suf.begin(), suf.end(), comp(group));
		group[suf[0]] = 0, start_group[0] = 0;
		for (int i = 1; i < n; i++)
		{
			group[suf[i]] = group[suf[i - 1]] + (s[suf[i]] != s[suf[i - 1]]);
			if (group[suf[i]] != group[suf[i - 1]])
				start_group[group[suf[i]]] = i;
		}
		c[0] = group;
		for (int h = 1, p = 1; group[suf[n - 1]] != n - 1 || 2 * h <= n; h <<=
				1, p++)
		{
			if (group[n - 1] != n - 1)
			{
				for (int i = 0; i < n; i++)
					if (n - suf[i] <= h)
						tmp_suf[start_group[group[suf[i]]]++] = suf[i];
				for (int i = 0; i < n; i++)
					if (suf[i] - h >= 0)
						tmp_suf[start_group[group[suf[i] - h]]++] = suf[i] - h;
				tmp_group[0] = 0;
				for (int i = 1; i < n; i++)
				{
					tmp_group[i] = tmp_group[i - 1];
					if (group[tmp_suf[i]] != group[tmp_suf[i - 1]])
						tmp_group[i]++;
					else
					{
						int v1 =
								(tmp_suf[i - 1] + h < n) ?
										group[tmp_suf[i - 1] + h] : -1;
						int v2 =
								(tmp_suf[i] + h < n) ?
										group[tmp_suf[i] + h] : -1;
						if (v1 != v2 || (v1 == -1 && v2 == -1))
							tmp_group[i]++;
					}
				}
				start_group[0] = 0;
				for (int i = 0; i < n; i++)
				{
					suf[i] = tmp_suf[i], group[suf[i]] = tmp_group[i];
					if (i && group[suf[i]] != group[suf[i - 1]])
						start_group[group[suf[i]]] = i;
				}
			}
			c[p] = group;
		}
		return suf;
	}
public:
	suffix_array(string s)
	{
		this->s = s;
		n = s.size();
		group = suf = tmp_suf = start_group = tmp_group = vector<int>(n);
		log.resize(n + 1);
		log[1] = 0;
		for (int i = 2; i < n + 1; i++)
			log[i] = log[i / 2] + 1;
		build_suffix_array();
	}
	vector<int>& get_suffix_array()
	{
		return suf;
	}
	int lcp(int i, int j)
	{
		int ans = 0;
		for (int k = 20; k >= 0 && i < n && j < n; k--)
		{
			if (c[k].empty())
				continue;
			if (c[k][i] == c[k][j])
				ans += (1 << k), i += (1 << k), j += (1 << k);
		}
		return ans;
	}
	int compare(int l, int r, int len)
	{
		for (int k = 20; k >= 0 && len; k--)
		{
			if (c[k].empty() || (1 << k) > len)
				continue;
			if (c[k][l] == c[k][r])
				l += (1 << k), r += (1 << k), len -= (1 << k);
			else if (c[k][l] > c[k][r])
				return 1;
			else
				return -1;
		}
		assert(len == 0);
		return 0;
	}
	bool equal(int l, int r, int len)
	{
		int j = log[len];
		return c[j][l] == c[j][r]
				&& c[j][l + len - (1 << j)] == c[j][r + len - (1 << j)];
	}
};
