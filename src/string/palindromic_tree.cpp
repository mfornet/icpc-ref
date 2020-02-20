/*
	at each step when add a character:
	suf->len is the length of longest suffix palindrome
	suf->suf is the next node with longest suffix palindrome
	Complexity: O(n)
*/

template<typename charT, typename Container>
struct palindromic_tree
{
	struct node
	{
		int slink;
		int length;
		Container next;
		node(int slink, int length) : slink(slink), length(length), next{{}} {}
		int operator[](int c) const { return next[c]; }
		int& operator[](int c) { return next[c]; }
	};

	palindromic_tree()
	{
		sink = 0;
		nodes.emplace_back(0, -1);
		nodes.emplace_back(0, 0);
	}

	int extend(const charT &c)
	{
		str.push_back(c);
		sink = get_link(sink);
		if (!nodes[sink][c])
		{
			nodes[sink][c] = nodes.size();
			int length = nodes[sink].length + 2;
			int slink = length == 1 ? 1 : nodes[get_link(nodes[sink].slink)][c];
			nodes.emplace_back(slink, length);
		}
		return sink = nodes[sink][c];
	}

	const node& operator[](int node_id) const { return nodes[node_id]; }
	int size() const { return nodes.size(); }

private:
	int sink;
	vector<node> nodes;
	vector<charT> str;

	int get_link(int v)
	{
		int n = str.size();
		while (n - nodes[v].length - 2 < 0 || str[n - 1] != str[n - nodes[v].length - 2])
			v = nodes[v].slink;
		return v;
	}
};
