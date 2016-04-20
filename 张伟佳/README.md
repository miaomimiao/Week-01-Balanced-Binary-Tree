##Red-Black Tree简单实现和基于RBTree的map的简单实现

* Red-Black Tree 功能
    * 插入元素
    * 查找元素
* Red-Black Tree __没有__实现的功能
    * 删除元素
    * 迭代器
    * 等等
* map 功能
    * 插入/修改元素
    * 重载了[]运算符
* map __没有__实现的功能
    * 删除元素
    * 迭代器
    * 等等

###RBTree声明
 ```CPP
template <class E>
struct RBTNode {
    bool black;
	E data;
	RBTNode<E> *left, *right, *p;
	RBTNode():black(false), left(NULL), right(NULL), p(NULL) {}
	RBTNode(E el, bool bl, RBTNode<E> *l=NULL, RBTNode<E> *r=NULL, RBTNode<E> *pa=NULL):data(el), black(bl), left(l), right(r), p(pa){}
};
template <class E>
class RBTree {
private:
	RBTNode<E> *root, *nil;
	void RotateL(RBTNode<E> *x);
	void RotateR(RBTNode<E> *x);
	void RBInsertFixup(RBTNode<E> *z);
	void RBRemoveFixup(RBTNode<E> *z);
	RBTNode<E> *Search(E& el, RBTNode<E> *ptr);
public:
	RBTree() {
		nil=new RBTNode<E>(E(), true);
		nil->p=nil;
		root=nil;
		root->p=nil;
		root->left=nil;
		root->right=nil;
	}
	RBTNode<E> *Search(E el) { return Search(el, root); };
	RBTNode<E> *Insert(E el);
};
 ```
###Map声明
 ```CPP
template <class K, class E>
class MapPair:public pair<K, E> {
public:
    MapPair() {}
	MapPair(K x, E el):pair<K, E>(x, el) {}
	bool operator<(const MapPair<K, E> &rhs) const {
		return this->first<rhs.first;
	}
	bool operator>(const MapPair<K, E> &rhs) const {
		return this->first>rhs.first;
	}
};

template<class K, class E>
class Map {
public:
	Map() {}
	~Map() {}
	void Insert(K x, E el) {
		MapPair<K, E> p=MapPair<K, E>(x, el);
		RBTNode<MapPair<K, E> >* ret=rbt.Search(p);
		if (ret==NULL) {
			rbt.Insert(p);
		}
	}
	E Search(K x) {
		MapPair<K, E> p=MapPair<K, E>(x, E());
		RBTNode<MapPair<K, E> >* ret=rbt.Search(p);
		if (ret!=NULL) {
			return ret->data.second;
		}else {
			return -1;
		}
	}
	E& operator[](const K& x) {
		MapPair<K, E> p=MapPair<K, E>(x, E());
		RBTNode<MapPair<K, E> >* ret=rbt.Search(p);
		if (ret!=NULL) {
			return ret->data.second;
		}else {
			return rbt.Insert(p)->data.second;
		}
	}
private:
	RBTree<MapPair<K, E> > rbt;
};
 ```