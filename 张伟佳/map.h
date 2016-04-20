// one implementation of map using red-black tree
#ifndef _MAP_H
#define _MAP_H 1
#include "rbtree.h"
#include <iostream>
#include <utility>
#include <windows.h>
using namespace std;

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

#endif /* _MAP_H */