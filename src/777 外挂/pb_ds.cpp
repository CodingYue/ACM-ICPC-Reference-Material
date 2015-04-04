<TeX>
使用时注意，对于G++ 4.7.0以下版本自带的libstdc++，需要用null_mapped_type，以上使用null_type，注意不支持multi系，需要自行塞个pair。所有rank值都是0开始的。

复杂度方面，pairing_heap的合并是$ O(1) $，其他方面thin_heap要好一点，注意thin_heap合并是$O(n)$，并且带tree_order_statistics的join也是$O(n)$，谨防被坑。
</TeX>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

using namespace __gnu_pbds;

// .order_of_key() 返回某个值的排名，是lower_bound的rank版。
// .find_by_order() 返回一个iterator表示某个特定排名的值。
template<typename T> using rset=tree<T, null_mapped_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T, typename U> rmap=tree<T, U, less<T>, rb_tree_tag, tree_order_statistics_node_update> supermap;

// 合并，需要保证st中所有元素的key比another_st中的小。
st.join(another_st);
// 拆分严格大于key的东西到output_st里。
st.split(key,output_st);

// tag还有pairing_heap_tag, binomal_heap_tag, rc_binomal_heap_tag.
typedef priority_queue<int, greater<int>, thin_heap_tag> hyperheap;
// .modify是修改值的操作，第一个参数是一个iterator。
// 也支持join