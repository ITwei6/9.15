#pragma once
#pragma once
#include <iostream>
using namespace std;

//红黑树，不是红色就是黑色
enum Color
{
	RED,
	BLACK
};
template <class T>
//先定义结点
struct RBtreeNode
{
	//我们也不知道数据是什么？ 是T类型
	RBtreeNode<T>* _left;
	RBtreeNode<T>* _right;
	RBtreeNode<T>* _parent;
	Color _col;
	T _data;
		
	RBtreeNode(const T& data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _col(RED)//根结点是黑色,但插入的元素是红色的
		, _data(data)
	{}

};
//只有把树里的迭代器搞完，才能搞map和set的迭代器

//迭代器提供三个模板参数，第一个控制数据类型，第二个控制解引用返回值类型，第三个控制->返回值类型
template <class T,class Ref,class Ptr>
struct _treeIterator
{
	typedef _treeIterator<T,Ref,Ptr> Self;
	typedef RBtreeNode<T> Node;


	_treeIterator( Node * node)
		:_node(node)
	{}

	Ref& operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &_node->_data;
	}
	Self& operator--()
	{
		//找孩子是父亲右的那个
		
		if (_node->_left)//如果左边存在，那么就找最大值
		{

			Node* curleft = _node->_left;
			while (curleft->_right)
			{
				curleft = curleft->_right;
			}
			_node = curleft;
		}
		else//左边不存在，就找孩子是父亲右的那个
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = cur->_parent;
			}
			//走到这里说明找到孩子是右边的了
			_node = parent;

		}
		return *this;
	}
	Self& operator++()
	{
		//如果右边存在，那么就找最小结点
		if (_node->_right)
		{
			Node* curright = _node->_right;
			while (curright->_left)
			{
				curright = curright->_left;
			}
			_node = curright;
		}
		else//右边不存在，就找孩子是父亲左边的那个祖先
		{
			Node* cur = _node;

			Node* parent = cur->_parent;

			while (parent&&cur==parent->_right)
			{
					cur = parent;
		         	parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	bool operator!=(const Self& n)
	{
		return _node != n._node;
	}
	//迭代器底层封装着结点指针
	Node* _node;
};

template <class K, class T,class keyofT>
//这里的K是find查找 key值
struct RBTree
{
	
public:

	typedef RBtreeNode<T> Node;
	typedef _treeIterator<T,T&,T*> iterator;//普通迭代器
	//红黑树的迭代器和链表的迭代器很相似都是自定义类型，里面封装着指针，因为原生指针不满足要求！
	//两个是相同的类模板，通过传不同的模板参数，实例化出不同的迭代器
	typedef _treeIterator<T, const T&, const T*> const_iterator;//const迭代器
	//通过控制传模板参数来选择是普通迭代器还是const迭代器

	iterator begin()//最左边的结点
	{
		Node* curleft = _root;
		while (curleft && curleft->_left)//还要判断一下curleft是否为空，因为root头可能为空
		{
			curleft = curleft->_left;
		}

		return iterator(curleft);
	}
	iterator end()
	{
		return iterator(nullptr);//用空表示end();
	}



	const_iterator begin()const
	{
		Node* curleft = _root;
		while (curleft && curleft->_left)//还要判断一下curleft是否为空，因为root头可能为空
		{
			curleft = curleft->_left;
		}

		return const_iterator(curleft);
	}
	const_iterator end()const
	{
		return const_iterator(nullptr);//用空表示end();
	}
	
	//用来或者数据中的key
	Node* find(const K& key)
	{
		keyofT kof;
		Node* cur = _root;
		while (cur)
		{
			if (kof(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else if (kof(cur->_data) > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;

	}
	//插入与搜索树是一致的
	pair<iterator,bool> Insert(const T& data)//现在红黑树里存的数据我们不确定，就只是T类型
	{
		//红黑树的插入就是搜索树的插入
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(iterator(_root),true);
			//插入成功说明返回的是新结点构造的迭代器封装的pair
		}

		//说明该二叉树不是空树，那么就进行比较找到位置
		Node* cur = _root;
		Node* parent = nullptr;
		keyofT kof;
		while (cur)
		{
			//这里因为树里存的数据到底是什么类型的，所以无法这样比较
			//我们想要根据K值来进行比较，但最终的数据可能是pair类型的
			//所以我们需要一个仿函数keyofT来获取K类型和pair类型的里的K值

			
			if (kof(cur->_data) < kof(data))
			{
				parent = cur;
				//记录结点的位置
				cur = cur->_right;
			}
			else if (kof(cur->_data) > kof(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return  make_pair(iterator(cur), false);
				//插入失败，返回的是已经存在结点的迭代器
			}
		}
		//走到这里表明cur为空了，表明位置已经找到了
		cur = new Node(data);
		Node* newnode = cur;
		//下面cur可能会往上走，先记录一下
		cur->_col = RED;
		//插入结点是红色的
		if (kof(data) > kof(parent->_data))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		//注意这个是三叉链，还要注意父指针
		cur->_parent = parent;


		//插入结点是红色的！然后如果父节点是黑色的那么就没有事，但如果父节点是红色那么就需要讨论！
		//可能parent不存在
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//先记录下祖父位置

			if (parent == grandfather->_left)
			{
				//说明叔叔在右边
				Node* uncle = grandfather->_right;
				//uncle存在且为红色
				if (uncle && uncle->_col == RED)
				{
					//解决方法：变色+向上调整
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;


				}
				else//uncle不存在或者uncle存在为黑色   解决方法：旋转+变色   旋转完后作为根结点就需要变黑色
				{
					if (cur == parent->_left)
					{
						//右旋
						RotateR(grandfather);
						//变色
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//双旋
						//先左旋
						RotateL(parent);
						RotateR(grandfather);

						//变色
						cur->_col = BLACK;
						grandfather->_col = RED;

					}
					break;
				}
			}
			else//parent==grandfather->_right
			{
				Node* uncle = grandfather->_left;

				//uncle存在且为红色
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle不存在或者存在且为黑色
				{
					if (cur == parent->_right)
					{
						//左旋
						RotateL(grandfather);
						//变色
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//先右旋再左旋
						RotateR(parent);
						RotateL(grandfather);
						//变色
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;

				}
			}

		}
		
		//当最后调整到根节点时，父节点不存在，如果这时根结点要是红色的那么就是要变色红色
		_root->_col = BLACK;
		return  make_pair(iterator(newnode), true);
	}
	bool CheckColour(Node* root, int blacknum, int benchmark)
	{
		if (root == nullptr)
		{
			if (blacknum != benchmark)
				return false;

			return true;
		}

		if (root->_col == BLACK)
		{
			++blacknum;
		}

		if (root->_col == RED && root->_parent && root->_parent->_col == RED)
		{
			cout << root->_kv.first << "出现连续红色节点" << endl;
			return false;
		}

		return CheckColour(root->_left, blacknum, benchmark)
			&& CheckColour(root->_right, blacknum, benchmark);
	}

	bool IsBalance()
	{
		return IsBalance(_root);
	}

	bool IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		if (root->_col != BLACK)
		{
			return false;
		}

		// 基准值
		int benchmark = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
				++benchmark;

			cur = cur->_left;
		}

		return CheckColour(root, 0, benchmark);
	}

	void RotateL(Node* parent)//左单旋
	{

		Node* cur = parent->_right;

		Node* curleft = cur->_left;
		parent->_right = curleft;
		if (curleft)
		{
			curleft->_parent = parent;
		}
		cur->_left = parent;
		Node* pp = parent->_parent;
		parent->_parent = cur;



		if (parent == _root)
		{
			//那么这样cur就是根结点了
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (pp->_left == parent)
			{
				pp->_left = cur;
			}
			else
			{
				pp->_right = cur;
			}

			cur->_parent = pp;
			//旋转后cur和parent bf都为0?
		}

	}
	void RotateR(Node* parent)//右单旋
	{
		Node* cur = parent->_left;

		Node* curright = cur->_right;

		parent->_left = curright;
		if (curright)
		{
			curright->_parent = parent;
		}
		Node* ppnode = parent->_parent;
		cur->_right = parent;
		parent->_parent = cur;

		if (ppnode == nullptr)
		{
			//说明cur就变成根节点了
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = cur;
			}
			else
			{
				ppnode->_right = cur;
			}
			cur->_parent = ppnode;
		}

	}
private:
	Node* _root = nullptr;

};