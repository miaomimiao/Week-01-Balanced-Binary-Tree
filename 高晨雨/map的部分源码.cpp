//stl_Pair.h的定义
#ifndef STL_PAIR_H_INCLUDED
#define STL_PAIR_H_INCLUDED

template<class T1,class T2>
//定义结构体Pair,Pair的第一个元素被视为键值(key)，第二个元素被视为实值(value)
struct Pair
{
	typedef T1 first_type;
	typedef T2 second_type;
	T1 first;
	T2 second;
	Pair() : first(T1()),second(T2()) {}
	Pair(const T1& a,const T2& b) :first(a) ,second(b) {}
};

#endif // STL_PAIR_H_INCLUDED
/****************************************************************************/

/*********************map的STL部分源代码摘录**********************************/
/*map的底层实现机制是RB-tree,
  RB-tree是一种平衡二叉搜索树，
  自动排序效果好，
  搜索平均时间复杂度低，
  可以为map提供各种开放的操作接口
*/
//map的STL部分源代码摘录
template<class Key, class T,    //Key为键值key的型别，T为实值value的型别
		 class Compare = less<Key>,    //缺省采用递增排序
		 class Alloc = alloc>
class map{
public:
	//typedefs:
	typedef Key key_type;   //键值类型
	typedef T data_type;    //数据（实值）型别
	typedef T mapped_type;
	typedef pair<const Key, T> value_type;//元素型别（键值/实值）
	typedef Compare key_compare;  //键值比较函数

	//定义一个functor,用于调用元素比较函数
	class value_compare:
		public binary_function<value_type, value_type, bool>
		{
			friend class map<Key, T, Compare, Alloc>;
		protected:
			Compare comp;
			value_compare(Compare c) :comp(c) {}
		public:
			bool operator()(const value_type& x,const value_type&y) const{
				return comp(x.first,y.first);
			}
		} ;
		private:
			//定义表述型别（representation type)
			//以map元素型别的第一个型别（pair）作为RB-tree的节点键值型别
			typedef rb_tree<key_type,value_type,
			                selectlst<value_type>,key_compare,Alloc>rep_type;
			rep_type t;//以RB-tree表现map
		public:
			typedef typename rep_type::pointer;
			typedef typename rep_type::const_pointer const_pointer;
			typedef typename rep_type::reference reference;
			typedef typename rep_type::const_reference const_reference;
			typedef typename rep_type::iterator iterator;
			//map将iterator定义为RB-tree的const_iterator
			//iterator允许用户通过其迭代器修改元素的实值
			typedef typename rep_type::const_iterator const_iterator;
			typedef typename rep_type::reverse_iterator reverse_iterator;
			typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
			typedef typename rep_type::size_type size_type;
			typedef typename rep_type::difference_type difference_type;

			//allocation/deallocation
			//map使用底层RB-tree的insert_unique()
			map() :t(Compare()){}
			explicit map(const Compare&comp) :t(comp) {}

			template<class InputIterator>
			map(InputIterator first, InputIterator last):
				t(Compare()) {t.insert_unique(first,last);}

			template<class InputIterator>
			map(InputIterator first, InputIterator last,const Compare& comp):
				t(comp) {t.insert_unique(first,last);}

			map(const map<Key ,T ,Compare,Alloc>&x) :t(x.t) {}
			map<Key,T, Compare,Alloc>& operator=(const map<key,T,Compare,Alloc>& x)
			{
				t=x.t;
				return *this;
			}

			//accessors:

			key_compare key_comp() const{return t.key_comp();}
			value_compare value_comp() const{return value_compare(t.key_comp());}
			iterator begin() {return t.begin();}
			const_iterator bagin() const{return t.begin();}
			iterator end() {return t.end();}
			const_iterator end() const{return t.end();}
			reverse_iterator rbegin() {return t.rend();}
			const_reverse_iterator rbegin()const{return t.rbegin();}
			reverse_iterator rend() {return t.rend();}
			const_reverse_iterator() const{return t.rend();}
			bool empty() const{return t.size();}
			size_type size() const{return t.size();}
			size_type max_size() const{return t.max_size();}

            T&operator[](const key_type&k)
            {
            	return(*((insert(value_type(k,T()))).first)).second;
            }
            void swap(map<Key,T,Compare,Alloc>& x){t.swap(x.t)}

            //insert
            //此函数会将工作直接转给底层机制RB-tree的insert_unique()去执行
            //返回值型别是一个pair,由迭代器和一个bool值组成，后者表示插入成功与否，若成功前者指向被插元素
            pair<iterator,bool>insert(const value_type& x)
            {
            	return t.insert_unique(x);
            }
            iterator insert(iterator position ,const value_type& x) {
                return t.insert_unique(position, x);
            }
            template <class InputIterator>
            void insert(InputIterator first,InputIterator last)
            {
            	t.insert_unique(first,last);
            }
            void erase(iterator position){t.erase(poistion);}
            size_type erase(const key_type&x) {return t.erase(x);}
            void erase(iterator first,iterator last) {t.erase(first, last);}
            void clear() {t.clear();}
};