/*
	For two convex polygons P and Q in the plane with m and n vertices, 
	their Minkowski sum is a convex polygon with at most m + n vertices 
	and may be computed in time O (m + n) by a very simple procedure, 
	which may be informally described as follows. 
	Assume that the edges of a polygon are given and the direction, 
	say, counterclockwise, along the polygon boundary. 
	Then it is easily seen that these edges of the convex polygon 
	are ordered by polar angle. Let us merge the ordered sequences 
	of the directed edges from P and Q into a single ordered sequence S. 
	Imagine that these edges are solid arrows which can be moved freely 
	while keeping them parallel to their original direction. 
	Assemble these arrows in the order of the sequence S by attaching 
	the tail of the next arrow to the head of the previous arrow. 
	It turns out that the resulting polygonal chain will in fact be a 
	convex polygon which is the Minkowski sum of P and Q. 


	The sum of Minkowski of two sets A and B is the set C = { a + b : a e A,b e B }. // each element in a set is a vector
	It can be proven that if A and B are convex polygons then C will also be a convex polygon.
*/

/*
    Minkowski sum of two convex polygons. O(n + m)
    Note: Polygons MUST be counterclockwise
*/
polygon minkowski(const polygon &ps, const polygon &qs)
{
	vector<point> rs;
	int i = distance(ps.begin(), min_element(ps.begin(), ps.end()));
	int j = distance(qs.begin(), min_element(qs.begin(), qs.end()));
	do
	{
		rs.emplace_back(ps[i] + qs[j]);
		int in = i + 1, jn = j + 1;
		if (in == ps.size()) in = 0;
		if (jn == qs.size()) jn = 0;
		int s = sign(cross(ps[i] - ps[in], qs[j] - qs[jn]));
		if (s >= 0) i = in;
		if (s <= 0) j = jn;
	}
	while (rs[0] != ps[i] + qs[j]);
	return rs;
}
