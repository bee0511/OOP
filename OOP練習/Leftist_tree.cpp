#include<functional>
#ifndef LEFTIST_TREE
#define LEFTIST_TREE
template<typename T,typename _Compare=std::less<T> >
class leftist_tree{
	private:
		struct node{
			T data;
			int deep;
			node *l,*r;
			node(const T&d):data(d),deep(1),l(0),r(0){}
		}*root;
		int _size;
		_Compare cmp;
		inline int deep(node *o){return o?o->deep:0;}
		node *merge(node *a,node *b){
			if(!a||!b)return a?a:b;
			if(cmp(a->data,b->data)){
				node *t=a;a=b;b=t;
			}
			a->r=merge(a->r,b);
			if(deep(a->l)<deep(a->r)){
				node *t=a->l;a->l=a->r;a->r=t;
			}
			a->deep=deep(a->l)+1;
			return a;
		}
		void _clear(node *&o){
			if(o)_clear(o->l),_clear(o->r),delete o;
		}
	public:
		leftist_tree():root(0),_size(0){}
		~leftist_tree(){_clear(root);}
		inline void clear(){
			_clear(root);root=0;_size=0;
		}
		inline void join(leftist_tree &o){
			root=merge(root,o.root);
			o.root=0;
			_size+=o._size;
			o._size=0;
		}
		inline void swap(leftist_tree &o){
			node *t=root;
			root=o.root;
			o.root=t;
			int st=_size;
			_size=o._size;
			o._size=st;
		}
		inline void push(const T&data){
			_size++;
			root=merge(root,new node(data));
		}
		inline void pop(){
			if(_size)_size--;
			node *tmd=merge(root->l,root->r);
			delete root;
			root=tmd;
		}
		inline const T& top(){return root->data;}
		inline int size(){return _size;}
		inline bool empty(){return !_size;}
};
#endif