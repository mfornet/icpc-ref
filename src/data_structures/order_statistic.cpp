/*
	pb_ds_tree allowing:
		order_of_key(x) number of keys less that x
		find_by_order(k) find the k-th key
		all standars function of set

	Notes: Duplicated keys are not allowed, use pair<key, int> instead

	Complexity: O(log n) all operations
*/

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_update

using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


// #include <ext/pb_ds/priority_queue.hpp>
// // Some heaps allowing opertation such as merging and update key
// // binary_heap, binomial_heap, pairing_heap, rc_binomial_heap, thin_heap
// template<typename _Tv, typename Cmp_Fn = std::less<_Tv>, typename Tag = pairing_heap_tag>
// using heap = priority_queue<_Tv, Cmp_Fn, Tag>;
// using binary_heap_tag;
// using binomial_heap_tag;
// using pairing_heap_tag;
// using rc_binomial_heap_tag;
// using thin_heap_tag;
