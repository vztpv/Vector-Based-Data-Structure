﻿
#ifndef ARR_RBTREE_H
#define ARR_RBTREE_H

#include <vector>

namespace wiz 
{
	typedef enum _Color { RED = 0, BLACK = 1 } Color;
	
	template < class T >
	class RB_Node // no REMOVE method!
	{
	public:
		long long id = 0; // NULL value? id == -1 ?
		T key;
		long long  left = 0;
		long long  right = 0;
		long long  p = 0; // parent
		Color color;
	public:
		explicit RB_Node(const T& key = T()) : key(key), color(BLACK) { }

	public:
		bool operator==(const RB_Node<T>& other)const {
			return this->id == other.id && other.id != -1;
		}
	};

	template < class T, class COMP = ASC<T>, class COMP2 = EQ<T> >
	class RB_Tree
	{
	private:
		bool IsNULL(RB_Node<T>& x)const
		{
			return x.id <= 0 || x.id > arr.size();
		}
		void Clear()
		{
			arr.clear();
			arr.push_back(RB_Node<T>());
			root = 0;
			count = 0;
		}
	private:
		std::vector<RB_Node<T>> arr = { RB_Node<T>() };
		long long root = 0;
		int count = 0;
	public:
		explicit RB_Tree() {  }
		virtual ~RB_Tree() {
			//
		}
	private:// LEFT ROTATE Tree x
		void LEFT_ROTATE(RB_Tree<T, COMP>* tree, RB_Node<T>*  x) {
			//if( x !=NIL<T>::Get() || tree.root != NIL<T>::Get() ) { return; }
			RB_Node <T>*   y;
			// y = right[x]
			y = &(tree->arr[x->right]);
			// right[x] = left[y]
			x->right = y->left;
			// if(left[y] != nil[T]
			if (!IsNULL(tree->arr[y->left])) {
				//    then p[left[y]] = x
				tree->arr[y->left].p = x->id;
			}
			// p[y] = p[x]
			y->p = x->p;
			// if( p[x] = nil[T]
			if (IsNULL(tree->arr[x->p])) {
				//  then root[T] = y
				tree->root = y->id;
			}
			//  else if x = left[p[x]]
			else if (x == &(tree->arr[tree->arr[x->p].left])) {
				//      then left[p[x]] = y
				tree->arr[x->p].left = y->id;
			}
			//  else right[p[x]] = y
			else { tree->arr[x->p].right = y->id; }
			// left[y] = x
			y->left = x->id;
			// p[x] = y
			x->p = y->id;
		}
		// Right ROTATE Tree x // left <> right
		void RIGHT_ROTATE(RB_Tree<T, COMP>* tree, RB_Node<T>*  x) {
			//if( x !=NIL<T>::Get() || tree.root != NIL<T>::Get() ) { return; }

			RB_Node <T>*  y;
			// y = right[x]
			y = &(tree->arr[x->left]);
			// right[x] = left[y]
			x->left = y->right;
			// if(left[y] != nil[T]
			if (!IsNULL(tree->arr[y->right])) {
				//    then p[left[y]] = x
				tree->arr[y->right].p = x->id;
			}
			// p[y] = p[x]
			y->p = x->p;
			// if( p[x] = nil[T]
			if (IsNULL(tree->arr[x->p])) {
				//  then root[T] = y
				tree->root = y->id;
			}
			//  else if x = left[p[x]]
			else if (x == &(tree->arr[tree->arr[x->p].right])) {
				//      then left[p[x]] = y
				tree->arr[x->p].right = y->id;
			}
			//  else right[p[x]] = y
			else { tree->arr[x->p].left = y->id; }
			// left[y] = x
			y->right = x->id;
			// p[x] = y
			x->p = y->id;
		}
		RB_Node <T>*  SEARCH(RB_Node <T>*   x, const T& k) 
		{
			COMP comp;

			while (!IsNULL(*x) && k != x->key) { // != nil
				if (comp(k, x->key)) { // k < x.key
					x = &arr[x->left];
				}
				else {
					x = &arr[x->right];
				}
			}
			return x;
		}
		void INSERT_FIXUP(RB_Tree<T, COMP>* tree, RB_Node<T>*  z) /// google ..
		{
			RB_Node <T>*   y;
			while (tree->arr[z->p].color == RED) {
				if (z->p == tree->arr[tree->arr[z->p].p].left) {
					y = &(tree->arr[tree->arr[tree->arr[z->p].p].right]);
					if (y->color == RED) {
						tree->arr[z->p].color = BLACK;
						y->color = BLACK;
						tree->arr[tree->arr[z->p].p].color = RED;
						z = &(tree->arr[tree->arr[z->p].p]);
					}
					else
					{
						if (z == &(tree->arr[tree->arr[z->p].right])) {
							z = &(tree->arr[z->p]);
							LEFT_ROTATE(tree, z);
						}
						tree->arr[z->p].color = BLACK;
						tree->arr[tree->arr[z->p].p].color = RED;
						RIGHT_ROTATE(tree, &(tree->arr[tree->arr[z->p].p]));
					}
				}
				else {
					y = &(tree->arr[arr[tree->arr[z->p].p].left]);
					if (y->color == RED) {
						tree->arr[z->p].color = BLACK;
						y->color = BLACK;
						tree->arr[tree->arr[z->p].p].color = RED;
						z = &(tree->arr[tree->arr[z->p].p]);
					}
					else {
						if (z == &(tree->arr[tree->arr[z->p].left])) {
							z = &(tree->arr[z->p]);
							RIGHT_ROTATE(tree, z);
						}
						tree->arr[z->p].color = BLACK;
						tree->arr[tree->arr[z->p].p].color = RED;
						LEFT_ROTATE(tree, &(tree->arr[tree->arr[z->p].p]));
					}
				}
			}
			tree->arr[tree->root].color = BLACK;
		}
		void INSERT(RB_Tree<T, COMP>* tree, const T& key)
		{
			COMP comp;
			COMP2 eq;

			// y= nil<T>?
			//RB_Node <T>*   y = &arr[0]; 
			//RB_Node <T>*   x = &arr[tree->root];
			long long y_idx = 0;
			long long x_idx = tree->root;

			while (!IsNULL(tree->arr[x_idx]))
			{
				y_idx = x_idx;
				// if( z.key < x.key )
				if (eq(key, tree->arr[x_idx].key)) {
					tree->arr[x_idx].key = key;
					return;
				}
				else if (comp(key, tree->arr[x_idx].key))
				{
					x_idx = tree->arr[x_idx].left;
				}
				else {
					x_idx = tree->arr[x_idx].right;
				}
			}

			long long now = arr.size();
			arr.push_back(RB_Node<T>());
			arr.back().id = now;
			arr.back().key = key;
			RB_Node<T>* z = &arr.back();
			
			
			z->p = tree->arr[y_idx].id;

			if (IsNULL(tree->arr[y_idx])) {
				tree->root = 1;
			}
			else if (comp(z->key, tree->arr[y_idx].key)) {
				tree->arr[y_idx].left = z->id;//
			}
			else {
				tree->arr[y_idx].right = z->id;//
			}

			z->left = 0; // = nil
			z->right = 0;
			z->color = RED; // = RED

			// insert fixup
			INSERT_FIXUP(tree, z);

			count++;
		}

	public:
		// insert, search, remove.
		void Insert(const T& key)
		{
			INSERT(this, key);
		}
		bool IsExist(const T& key)
		{
			// NULL != ~
			return !IsNULL(*SEARCH(&arr[root], key));
		}

		T* Search(const T& key) {
			return &(SEARCH(&arr[root], key)->key);
		}

		bool IsEmpty() const
		{
			return 0 == count;
		}
		bool empty() const { return IsEmpty(); }
		int GetCount() const
		{
			return count;
		}
		int size() const { return count; }
		void clear() {
			Clear();
		}
	};
}


#endif

