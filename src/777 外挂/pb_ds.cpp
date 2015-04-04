<TeX>
use a pair to emulate multiset, rank value is 0-based.

pairing_heap::join $ O(1) $, thin_heap::join $O(n)$，join with tree_order_statistics = $O(n)$, take care.
</TeX>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

using namespace __gnu_pbds;

// .order_of_key() = find rank for a given value, .find_by_order() = find value for a given rank
template<typename T> using rset=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T, typename U> rmap=tree<T, U, less<T>, rb_tree_tag, tree_order_statistics_node_update> supermap;

// 合并，需要保证st中所有元素的key比another_st中的小。拆分是严格大于key的。
st.join(another_st); st.split(key, output_st);

// or pairing_heap_tag, binomal_heap_tag, rc_binomal_heap_tag.
typedef priority_queue<int, greater<int>, thin_heap_tag> hyperheap;
// .modify是修改值的操作，第一个参数是一个iterator。也支持join。
