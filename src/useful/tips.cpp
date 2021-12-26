/*
	Segment tree with 2*n of memory (require int m = (b+e+1)>>1;)
	int id(int b, int e) { --e; return (b+e) | (b!=e); }
*/

/*
	Maximum profit of binary strings of length n, such that for every consecutive substring of length k
	there are at least L and at most R bits on, every bit has a profit of leave it off or turn it on.

	Assume that all bits are off, and let f[i] = (cost of turn on bit i) - (cost of leave it off)

	Network with n nodes, source S and sink T:
	Edge from vertex i to i+1 (or T, if i+1 > n) with cost 0 and capacity R-L
	Edge from vertex i to i+k (or T, if i+k > n) with cost -f[i] and capacity 1
	Edge from vertex S to vertices (1, 2, ..., k) with cost 0 and capacity oo
	Negated minimum cost of flow of value R from S to T is the answer
*/