#ifndef FOREST_H
#define FOREST_H

#include <set>
#include <list>

enum class ChildType : int
{
	Child_Root,		/*!< 根节点 */
	Child_Left,		/*!< 左节点 */
	Child_Right,	/*!< 右节点 */
	Child_Mid,		/*!< 中节点 */
};

template<class T> struct MNode
{
public:
	T data;
	ChildType type;
public:
	explicit MNode(const T& value, const ChildType& tp)
		: data(value)
		, type(tp)
	{
	}
};

/*!
 * @brief 树节点
 * @date 2019-12-17
 * @author FanKaiyu
*/
template<class T> struct TNode
{
	T data;							/*!< 数据域/根节点 */
	TNode<T>* left;					/*!< 左节点 */
	TNode<T>* right;				/*!< 右节点 */
	TNode<T>* mid;					/*!< 中节点 */
	std::set<void*> parents;		/*!< 父节点指针集合 */

	explicit TNode(const T& value, TNode<T>* l = nullptr, TNode<T>* r = nullptr, TNode<T>* m = nullptr)
		: data(value)
		, left(l)
		, right(r)
		, mid(m)
	{
		if (left)
		{
			left->parents.insert(this);
		}

		if (right)
		{
			right->parents.insert(this);
		}

		if (mid)
		{
			mid->parents.insert(this);
		}
	}

	~TNode()
	{
		if (left)
		{
			left->parents.erase(left->parents.find(this));
		}

		if (right)
		{
			right->parents.erase(right->parents.find(this));
		}

		if (mid)
		{
			mid->parents.erase(mid->parents.find(this));
		}

		for (std::set<void*>::iterator it = parents.begin(); it != parents.end(); ++it)
		{
			TNode<T>* parent = reinterpret_cast<TNode<T>*>(*it);

			if (parent->left == this)
			{
				parent->left = nullptr;
			}

			if (parent->right == this)
			{
				parent->right = nullptr;
			}

			if (parent->mid == this)
			{
				parent->mid = nullptr;
			}
		}
	}

	/*!
	 * @brief 设置左节点
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param TNode<T>* 左节点指针,非空值绑定节点,空值解除绑定
	*/
	void SetLeft(TNode<T>* node)
	{
		if (node == nullptr)
		{// 指针为空

			if (left && left->parents.find(this) != left->parents.end())
			{// 解除左节点与当前节点的关系
				left->parents.erase(left->parents.find(this));
			}

			// 更改节点指针
			left = node;

			return;
		}

		// 添加节点与当前节点的关系
		if (node->parents.find(this) == node->parents.end())
		{
			node->parents.insert(this);
		}

		if (left == nullptr || left == node)
		{// 左节点为空 或者 左节点与新增节点相同

			// 更改节点指针
			left = node;

			return;
		}

		if (left->parents.find(this) != left->parents.end())
		{// 解除左节点与当前节点的关系
			left->parents.erase(left->parents.find(this));
		}

		// 更改节点指针
		left = node;

		return;
	}

	/*!
	 * @brief 设置右节点
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param TNode<T>* 右节点指针,非空值绑定节点,空值解除绑定
	*/
	void SetRight(TNode<T>* node)
	{
		if (node == nullptr)
		{
			if (right && right->parents.find(this) != right->parents.end())
			{// 解除右节点与当前节点的关系
				right->parents.erase(right->parents.find(this));
			}

			// 更改节点指针
			right = node;

			return;
		}

		if (node->parents.find(this) == node->parents.end())
		{
			node->parents.insert(this);
		}

		if (right == nullptr || right == node)
		{
			right = node;

			return;
		}

		if (right->parents.find(this) != right->parents.end())
		{
			right->parents.erase(right->parents.find(this));
		}

		right = node;

		return;
	}

	/*!
	 * @brief 设置中节点
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param TNode<T>* 中节点指针,非空值绑定节点,空值解除绑定
	*/
	void SetMid(TNode<T>* node)
	{
		if (node == nullptr)
		{
			if (mid && mid->parents.find(this) != mid->parents.end())
			{// 解除中节点与当前节点的关系
				mid->parents.erase(mid->parents.find(this));
			}

			// 更改节点指针
			mid = node;

			return;
		}

		if (node->parents.find(this) == node->parents.end())
		{
			node->parents.insert(this);
		}

		if (mid == nullptr || mid == node)
		{
			mid = node;

			return;
		}

		if (mid->parents.find(this) != mid->parents.end())
		{
			mid->parents.erase(mid->parents.find(this));
		}

		mid = node;

		return;
	}
};

/*!
 * @class Forest
 * @brief 深林
 *
 * 树节点的集合
 * @date 2019-12-17
 * @author FanKaiyu
*/
template<class T> class Forest
{
private:
	std::set<void*> nodes;		/*!< 节点指针集合 */
	std::set<void*> visited;	/*!< 访问列表 */
public:
	Forest() {}
	~Forest()
	{
		for (std::set<void*>::iterator it = nodes.begin(); it != nodes.end(); it = nodes.erase(it))
		{
			delete (*it);
		}
	}

public:
	/*!
	 * @brief 获取节点
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param const T 节点的值
	 * @return TNode<T>* 成功返回指向该节点的指针,否则返回nullptr
	*/
	TNode<T>* GetNode(const T value) const
	{
		for (std::set<void*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			TNode<T>* ptr = reinterpret_cast<TNode<T>*>(*it);

			if (ptr->data == value)
			{
				return ptr;
			}
		}

		return nullptr;
	}

	/*!
	 * @brief 删除节点
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param const T 节点的值
	*/
	void DeleteNode(const T value)
	{
		for (std::set<void*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			TNode<T>* ptr = (*it);

			if (ptr->data == value)
			{
				delete ptr;

				it = nodes.erase(it);
				return;
			}
		}

		return;
	}

	/*!
	 * @brief 创建节点
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param const T 节点的值
	 * @return TNode<T>* 创建成功返回指向该节点的指针,否则返回nullptr
	*/
	TNode<T>* CreateNode(const T value)
	{
		TNode<T>* ptr = GetNode(value);

		if (ptr == nullptr)
		{
			ptr = new TNode<T>(value);

			nodes.insert(ptr);
		}

		return ptr;
	}

	/*!
	 * @brief 创建节点
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param const T 节点的值
	 * @param const T 左节点的值
	 * @param const T 右节点的值
	 * @param const T 中节点的值
	 * @return TNode<T>* 创建成功返回指向该节点的指针,否则返回nullptr
	*/
	TNode<T>* CreateNode(const T value, const T left, const T right, const T mid)
	{
		TNode<T>* ptr = GetNode(value);

		if (ptr == nullptr)
		{
			ptr = new TNode<T>(value, GetNode(left), GetNode(right), GetNode(mid));

			nodes.insert(ptr);
		}
		else
		{
			ptr->SetLeft(GetNode(left));
			ptr->SetRight(GetNode(right));
			ptr->SetMid(GetNode(mid));
		}

		return ptr;
	}

	/*!
	 * @brief 逆向广度遍历
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param TNode<T>* 根节点指针
	 * @return std::list<MNode> 返回遍历后的结果集合
	*/
	std::list<MNode<T>> ReverseLevelTraversal(TNode<T>* root)
	{
		std::list<MNode<T>> list;

		if (root == nullptr)
		{// 根节点为空
			return list;
		}

		std::list<void*> queue;	/*!< 堆栈队列 */

		// 压入队列
		queue.push_back(root);

		list.push_back(MNode<T>(root->data, ChildType::Child_Root));

		while (queue.size() > 0)
		{// 队列不为空

			// 弹出队列
			TNode<T>* ptr = reinterpret_cast<TNode<T>*>(queue.front());

			if (visited.find(queue.front()) != visited.end())
			{// 已经访问过
				queue.pop_front();
				continue;
			}

			// 压入访问列表
			visited.insert(queue.front());

			queue.pop_front();

			if (ptr->parents.size() > 0)
			{// 节点有父节点
				for (std::set<void*>::iterator it = ptr->parents.begin(); it != ptr->parents.end(); ++it)
				{
					TNode<T>* parent = reinterpret_cast<TNode<T>*>(*it);	/*!< 父节点指针 */

					if (visited.find(parent) != visited.end())
					{// 已经访问过
						continue;
					}

					// 压入队列
					queue.push_back(*it);

					if (parent->left == ptr)
					{// 父节点连接字节的方式
						list.push_back(MNode<T>(parent->data, ChildType::Child_Left));
					}

					if (parent->right == ptr)
					{// 父节点连接字节的方式
						list.push_back(MNode<T>(parent->data, ChildType::Child_Right));
					}

					if (parent->mid == ptr)
					{// 父节点连接字节的方式
						list.push_back(MNode<T>(parent->data, ChildType::Child_Mid));
					}

				}
			}
		}

		visited.clear();

		return list;
	}

	/*!
	 * @brief 逆向深度遍历-先序遍历
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param TNode<T>* 根节点指针
	 * @return std::list<MNode> 返回遍历后的结果集合
	*/
	std::list<MNode<T>> ReversePreTraversal(TNode<T>* root)
	{
		std::list<MNode<T>> list;

		if (root == nullptr)
		{// 根节点为空
			return list;
		}

		list.push_back(MNode<T>(root->data, ChildType::Child_Root));

		std::list<MNode<T>> rel = ReversePreOrderTraversal(root);

		for (std::list<MNode<T>>::iterator it = rel.begin(); it != rel.end(); ++it)
		{
			list.push_back(*it);
		}

		visited.clear();

		return list;
	}

	/*!
	 * @brief 逆向深度遍历-后序遍历
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param TNode<T>* 根节点指针
	 * @return std::list<MNode> 返回遍历后的结果集合
	*/
	std::list<MNode<T>> ReversePostTraversal(TNode<T>* root)
	{
		std::list<MNode<T>> list;

		if (root == nullptr)
		{// 根节点为空
			return list;
		}

		list = ReversePostOrderTraversal(root);

		list.push_back(MNode<T>(root->data, ChildType::Child_Root));

		visited.clear();

		return list;
	}

private:
	/*!
	 * @brief 逆向深度遍历-先序遍历
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param TNode<T>* 根节点指针
	 * @return std::list<MNode> 返回遍历后的结果集合
	*/
	std::list<MNode<T>> ReversePreOrderTraversal(TNode<T>* root)
	{
		std::list<MNode<T>> list;

		if (root == nullptr)
		{// 根节点为空
			return list;
		}

		if (visited.find(root) != visited.end())
		{// 已经访问过
			return list;
		}

		// 压入访问列表
		visited.insert(root);

		for (std::set<void*>::iterator it = root->parents.begin(); it != root->parents.end(); ++it)
		{
			TNode<T>* parent = reinterpret_cast<TNode<T>*>(*it);	/*!< 父节点指针 */

			if (visited.find(parent) != visited.end())
			{// 已经访问过
				continue;
			}

			if (parent->left == root)
			{// 父节点连接字节的方式
				list.push_back(MNode<T>(parent->data, ChildType::Child_Left));
			}

			if (parent->right == root)
			{// 父节点连接字节的方式
				list.push_back(MNode<T>(parent->data, ChildType::Child_Right));
			}

			if (parent->mid == root)
			{// 父节点连接字节的方式
				list.push_back(MNode<T>(parent->data, ChildType::Child_Mid));
			}

			std::list<MNode<T>> rel = ReversePreOrderTraversal(parent);

			for (std::list<MNode<T>>::iterator it = rel.begin(); it != rel.end(); ++it)
			{
				list.push_back(*it);
			}
		}

		return list;
	}

	/*!
	 * @brief 逆向深度遍历-后序遍历
	 * @date 2019-12-17
	 * @author FanKaiyu
	 * @param TNode<T>* 根节点指针
	 * @return std::list<MNode> 返回遍历后的结果集合
	*/
	std::list<MNode<T>> ReversePostOrderTraversal(TNode<T>* root)
	{
		std::list<MNode<T>> list;

		if (root == nullptr)
		{// 根节点为空
			return list;
		}

		if (visited.find(root) != visited.end())
		{// 已经访问过
			return list;
		}

		// 压入访问列表
		visited.insert(root);

		for (std::set<void*>::iterator it = root->parents.begin(); it != root->parents.end(); ++it)
		{
			TNode<T>* parent = reinterpret_cast<TNode<T>*>(*it);	/*!< 父节点指针 */

			if (visited.find(parent) != visited.end())
			{// 已经访问过
				continue;
			}

			std::list<MNode<T>> rel = ReversePostOrderTraversal(parent);

			for (std::list<MNode<T>>::iterator it = rel.begin(); it != rel.end(); ++it)
			{
				list.push_back(*it);
			}

			if (parent->left == root)
			{// 父节点连接字节的方式
				list.push_back(MNode<T>(parent->data, ChildType::Child_Left));
			}

			if (parent->right == root)
			{// 父节点连接字节的方式
				list.push_back(MNode<T>(parent->data, ChildType::Child_Right));
			}

			if (parent->mid == root)
			{// 父节点连接字节的方式
				list.push_back(MNode<T>(parent->data, ChildType::Child_Mid));
			}
		}

		return list;
	}

	// 正向广度遍历
	// 正向深度遍历-先序遍历
	// 正向深度遍历-反向遍历
};

#endif // FOREST_H
