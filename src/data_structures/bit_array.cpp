/*
	Custom multi-dimensional array with numbers of l bits

	Notes: td is the numbers of dimensions, l is the number of bits of each number,
	       the constructor recieve the size of each dimension
	       ** be careful with overflow, negative numbers are not supported **

	Example: bitarray<2, 20> b({ 10, 5 }) = array[10][5] with numbers of 20 bits

	Complexity: O(1) all operations
*/
template<const int td, const int l>
struct bit_array
{
	typedef unsigned long long ull; typedef const array<int, td> idx;
	#define addr int p = inner_product(c.begin(), c.end(), e.begin(), 0) * l, i = p >> 6, f = p & mask[6], w = f+l-64
	#define _get ull r = b[i] >> f & mask[l]; if (w > 0) r |= (b[i+1] & mask[w]) << (l-w)
	#define _set b[i] = (b[i] & ~(mask[l] << f)) | (x << f); if (w > 0) b[i+1] = (b[i+1] & ~mask[w]) | (x >> (l-w))

	bit_array(vector<int> d) : c(td), b(accumulate(d.begin(), d.end(), l, multiplies<int>()) / 64 + 1), mask(64)
	{
		for (int i = td-1, s = 1; i >= 0; c[i] = s, s *= d[i], --i);
		for (int i = 1; i < 64; mask[i] = (1LL<<i)-1, ++i);
	}

	inline ull get(idx &e) { addr; _get; return r; }
	inline ull set(idx &e, ull x) { addr; _set; return x; }
	inline ull add(idx &e, ull x) { return apply(e, x, plus<ull>()); }
	inline ull sub(idx &e, ull x) { return apply(e, x, minus<ull>()); }
	inline ull mul(idx &e, ull x) { return apply(e, x, multiplies<ull>()); }
	inline ull div(idx &e, ull x) { return apply(e, x, divides<ull>()); }
	inline ull mod(idx &e, ull x) { return apply(e, x, modulus<ull>()); }

private:
	template<typename bin_op>
	inline ull apply(idx &e, ull x, bin_op op)
					{ addr; _get; x = op(r, x); _set; return x; }

	vector<int> c; vector<ull> b, mask;
};
