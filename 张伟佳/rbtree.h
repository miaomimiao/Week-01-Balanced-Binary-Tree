// one implementation of red-black tree
// handcrafted by njzwj
#ifndef _RBTREE_H
#define _RBTREE_H 1
#include <iostream>
#include <windows.h>
using namespace std;

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
	void Remove(E& el);
	/* 警告：该中序遍历的实现只能应用于E的类型是pair<A, B>的时候 */
	void Travelsal(RBTNode<E> *p=NULL) {
		if (p==NULL) p=root;
		if (p->left!=nil) {
			Travelsal(p->left);
		}
		cout<<p->data.second<<" color:"<<(p->black?"Black":"Red")<<" parent: "<<(p->p==nil?-1:p->p->data.second)<<endl;
		if (p->right!=nil) {
			Travelsal(p->right);
		}
	}
};

template <class E>
RBTNode<E> *RBTree<E>::Search(E& el, RBTNode<E> *ptr) {
	if (ptr==nil) return NULL;
	if (el<ptr->data) return Search(el, ptr->left);
	else if (el>ptr->data) return Search(el, ptr->right);
	else return ptr;
};

template <class E>
RBTNode<E> *RBTree<E>::Insert(E el) {
	RBTNode<E> *x=root, *y=nil, *z=new RBTNode<E>(el, false);
	while (x!=nil) {
		y=x;
		if (z->data<x->data)
			x=x->left;
		else x=x->right;
	}
	z->p=y;
	if (y==nil) {
		root=z;
		root->p=nil;
	}else if (z->data<y->data) {
		y->left=z;
	}else {
		y->right=z;
	}
	z->left=nil;
	z->right=nil;
	RBInsertFixup(z);
	//cout<<"Travelsal:"<<endl;
	//Travelsal();
	return z;
};

template <class E>
void RBTree<E>::RBInsertFixup(RBTNode<E> *z) {
	RBTNode<E> *y;
	while (z->p->black==false) {
		if (z->p==z->p->p->left) {
			y=z->p->p->right;
			if (y->black==false) {
				z->p->black=true;					// case 01
				y->black=true;
				z->p->p->black=false;
				z=z->p->p;
			}else if (z==z->p->right) {
				z=z->p;								// case 02
				RotateL(z);
			}
			if (z!=root) {
				z->p->black=true;			// case 03
				if (z->p!=root) {
					z->p->p->black=false;
					RotateR(z->p->p);
				}
			}
		}else {
			y=z->p->p->left;
			if (y->black==false) {
				z->p->black=true;					// case 01
				y->black=true;
				z->p->p->black=false;
				z=z->p->p;
			}else if (z==z->p->left) {
				z=z->p;								// case 02
				RotateR(z);
			}
			if (z!=root) {
				z->p->black=true;			// case 03
				if (z->p!=root) {
					z->p->p->black=false;
					RotateL(z->p->p);
				}
			}
		}
	}
	root->black=true;
}

template <class E>
void RBTree<E>::Remove(E& el) {

};

template <class E>
void RBTree<E>::RotateL(RBTNode<E> *x) {
	RBTNode<E> *y=x->right;
	x->right=y->left;
	if (y->left!=nil) y->left->p=x;
	y->p=x->p;
	if (x->p==nil)
		root=y;
	else if (x==x->p->left)
		x->p->left=y;
	else
		x->p->right=y;
	y->left=x;
	x->p=y;
};

template <class E>
void RBTree<E>::RotateR(RBTNode<E> *x) {
	RBTNode<E> *y=x->left;
	x->left=y->right;
	if (y->right!=nil) y->right->p=x;
	y->p=x->p;
	if (x->p==nil)
		root=y;
	else if (x==x->p->right)
		x->p->right=y;
	else
		x->p->left=y;
	y->right=x;
	x->p=y;
};

#endif /* _RBTREE_H */