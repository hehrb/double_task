#include <iostream>
#include <cstdio>
#include <ctime>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

// 顺序查找
void SequentialSearch(const vector<int>& v, int n, int num, vector<int>& index, int& cnt)
{
	index.clear();
	cnt = 0;
	// 遍历查找
	for (int i = 0; i < n; ++i)
	{
		if (v[i] == num)
		{
			index.push_back(i);
			++cnt;
		}
	}
}

// 前后指针法进行一趟快排
int PartSort(vector<int>& sortV, int left, int right)
{
	int keyi = left;
	int prev = left, cur = left + 1;
	while (cur <= right)
	{
		if (sortV[cur] < sortV[keyi] && sortV[++prev] != sortV[cur])
		{
			swap(sortV[prev], sortV[cur]);
		}

		++cur;
	}
	swap(sortV[keyi], sortV[prev]);

	return prev;
}

// 递归进行快排
void QuickSort(vector<int>& sortV, int begin, int end)
{
	if (begin >= end)
	{
		return;
	}

	int keyi = PartSort(sortV, begin, end);

	// 递归，分成两个区间分别再次进行快排
	QuickSort(sortV, begin, keyi - 1);
	QuickSort(sortV, keyi + 1, end);
}

// 折半查找
void BinarySearch(const vector<int>& v, int n, int num, vector<int>& index, int& cnt)
{
	index.clear();
	cnt = 0;

	int left = 0; // 左下标
	int right = n - 1; // 右下标
	int l = 0; // 记录数的左区间
	int r = 0; // 记录数的右区间

	// 因为目标值可能存在多个，因此要找到左右区间

	// 先找数的左区间
	while (left < right)
	{
		int mid = left + right >> 1;
		if (v[mid] >= num)
		{
			right = mid;
		}
		else
		{
			left = mid + 1;
		}
	}

	// 如果最后左区间的值不是目标值，说明不存在目标值
	if (v[left] != num)
	{
		return;
	}
	// 存在，就去找右区间
	else
	{
		l = left;

		int left = 0, right = n - 1;
		while (left < right)
		{
			int mid = left + right + 1 >> 1;
			if (v[mid] <= num)
			{
				left = mid;
			}
			else
			{
				right = mid - 1;
			}
		}

		r = right;
	}

	// cnt就是目标值的个数
	cnt = r - l + 1;
	for (int i = l; i <= r; ++i)
	{
		index.push_back(i);
	}
}

// 二叉排序树查找算法

// 二叉排序树结点
struct BSTreeNode
{
	BSTreeNode* left; // 左子树
	BSTreeNode* right; // 右子树
	int key; // 关键值
};

// 二叉排序树查找
bool BSTreeFind(BSTreeNode* root, int K)
{
	BSTreeNode* cur = root;
	while (cur)
	{
		// 要查找的K值大于当前结点的key，就往右走
		if (K > cur->key)
		{
			cur = cur->right;
		}
		// 要查找的K值小于当前结点的key，就往左走
		else if (K < cur->key)
		{
			cur = cur->left;
		}
		// 要查找的K值等于当前结点的key，说明找到了
		else
		{
			return true;
		}
	}

	return false;
}

// 二叉排序树创建新结点
BSTreeNode* BuyBSTreeNode(int K)
{
	BSTreeNode* newnode = new BSTreeNode;
	// 成功new了一个新结点
	if (newnode != nullptr)
	{
		newnode->key = K;
		newnode->left = nullptr;
		newnode->right = nullptr;

		return newnode;
	}

	// 失败返回nullptr
	return nullptr;
}

// 二叉排序树插入
void BSTreeInsert(BSTreeNode*& root, int K)
{
	if (root == nullptr)
	{
		root = BuyBSTreeNode(K);
		return;
	}

	// 定义一个父结点parent，以便于链接新插入的结点
	BSTreeNode* parent = nullptr;
	BSTreeNode* cur = root;
	while (cur)
	{
		// 要插入的K值大于当前结点的key，就往右走
		if (K > cur->key)
		{
			parent = cur;
			cur = cur->right;
		}
		// 要插入的K值小于当前结点的key，就往左走
		else if (K < cur->key)
		{
			parent = cur;
			cur = cur->left;
		}
		// 还有一种情况，就是遇到已经插入的元素（即重复元素）
		// 这就不能再进行插入了，直接结束
		else
		{
			return;
		}
	}

	// cur当前所处位置就是二叉排序树中这个K值所应插入的位置
	cur = BuyBSTreeNode(K);
	// 如果K值比它的parent结点的key值大，就让parent的右 链接该结点cur
	if (K > parent->key)
	{
		parent->right = cur;
	}
	// 如果K值比它的parent结点的key值小，就让parent的左 链接该结点cur
	else
	{
		parent->left = cur;
	}
}

// 二叉排序树创建
BSTreeNode* BSTreeCreate(const vector<int>& v)
{
	BSTreeNode* root = nullptr;
	for (int i = 0; i < v.size(); ++i)
	{
		BSTreeInsert(root, v[i]);
	}

	return root;
}


// 二叉平衡树(AVL树)查找算法

// 二叉平衡树(AVL树)结点
struct AVLTreeNode
{
	// 3叉链
	AVLTreeNode* left; // 左子树
	AVLTreeNode* right; // 右子树
	AVLTreeNode* parent; // 父亲结点
	int key; // 关键值
	int bf; // 平衡因子
};

// 二叉平衡树查找
// 这个的实现与上一个二叉排序树相同
bool AVLTreeFind(AVLTreeNode* root, int K)
{
	AVLTreeNode* cur = root;
	while (cur)
	{
		// 要查找的K值大于当前结点的key，就往右走
		if (K > cur->key)
		{
			cur = cur->right;
		}
		// 要查找的K值大于当前结点的key，就往左走
		else if (K < cur->key)
		{
			cur = cur->left;
		}
		// 要查找的K值等于当前结点的key，说明找到了
		else
		{
			return true;
		}
	}

	return false;
}

// 左单旋
void RotateL(AVLTreeNode*& root, AVLTreeNode* parent)
{
	// subR: parent的右孩子
	AVLTreeNode* subR = parent->right;
	// subRL: subR的左孩子
	AVLTreeNode* subRL = subR->left;
	// ppNode: parent的parent
	AVLTreeNode* ppNode = parent->parent;

	// 旋转后的新的链接关系
	parent->right = subRL;
	parent->parent = subR;
	// 这里subRL可能为空，要判断
	if (subRL)
	{
		subRL->parent = parent;
	}
	subR->left = parent;

	// parent就是根结点，直接让subR变成新的根结点
	if (parent == root)
	{
		root = subR;
		root->parent = nullptr;
	}
	// parent不是根结点
	else
	{
		// 判断原来的parent是ppNode的左孩子还是右孩子
		if (ppNode->left == parent)
		{
			ppNode->left = subR;
		}
		else
		{
			ppNode->right = subR;
		}

		// 最后再链接上subR的parent为ppNode
		subR->parent = ppNode;
	}

	// 更新平衡因子
	subR->bf = 0;
	parent->bf = 0;
}

// 右单旋
void RotateR(AVLTreeNode*& root, AVLTreeNode* parent)
{
	// subL: parent的左孩子
	AVLTreeNode* subL = parent->left;
	// subLR: subL的右孩子
	AVLTreeNode* subLR = subL->right;
	// ppNode: parent的parent
	AVLTreeNode* ppNode = parent->parent;

	parent->left = subLR;
	parent->parent = subL;
	// 这里subLR可能为空，要判断
	if (subLR)
	{
		subLR->parent = parent;
	}
	subL->right = parent;

	// parent就是根结点，直接让subR变成新的根结点
	if (parent == root)
	{
		root = subL;
		root->parent = nullptr;
	}
	// parent不是根结点
	else
	{
		if (ppNode->left == parent)
		{
			ppNode->left = subL;
		}
		else
		{
			ppNode->right = subL;
		}

		subL->parent = ppNode;
	}

	// 更新平衡因子
	subL->bf = 0;
	parent->bf = 0;
}

// 左右双旋
void RotateLR(AVLTreeNode*& root, AVLTreeNode* parent)
{
	AVLTreeNode* subL = parent->left;
	AVLTreeNode* subLR = subL->right;
	int bf = subLR->bf;

	RotateL(root, parent->left);
	RotateR(root, parent);

	// 更新平衡因子(分三种情况)
	if (bf == 0)
	{
		parent->bf = 0;
		subL->bf = 0;
		subLR->bf = 0;
	}
	else if (bf == 1)
	{
		parent->bf = 0;
		subL->bf = -1;
		subLR->bf = 0;
	}
	else if (bf == -1)
	{
		parent->bf = 1;
		subL->bf = 0;
		subLR->bf = 0;
	}
	else
	{
		// 到这说明之前旋转就有问题了，直接断言报错
		assert(false);
	}
}

// 右左双旋
void RotateRL(AVLTreeNode*& root, AVLTreeNode* parent)
{
	AVLTreeNode* subR = parent->right;
	AVLTreeNode* subRL = subR->left;
	int bf = subRL->bf;

	RotateR(root, parent->right);
	RotateL(root, parent);

	// 更新平衡因子(分三种情况)
	if (bf == 0)
	{
		parent->bf = 0;
		subR->bf = 0;
		subRL->bf = 0;
	}
	else if (bf == 1)
	{
		parent->bf = -1;
		subR->bf = 0;
		subRL->bf = 0;
	}
	else if (bf == -1)
	{
		parent->bf = 0;
		subR->bf = 1;
		subRL->bf = 0;
	}
	else
	{
		// 到这说明之前旋转就有问题了，直接断言报错
		assert(false);
	}
}

// 二叉平衡树创建新结点
AVLTreeNode* BuyAVLTreeNode(int K)
{
	AVLTreeNode* newnode = new AVLTreeNode;
	// 成功new了一个新结点
	if (newnode != nullptr)
	{
		newnode->key = K;
		newnode->bf = 0;
		newnode->left = nullptr;
		newnode->right = nullptr;
		newnode->parent = nullptr;

		return newnode;
	}

	// 失败返回nullptr
	return nullptr;
}


// 二叉平衡树插入
void AVLTreeInsert(AVLTreeNode*& root, int K)
{
	// 前面与二叉排序树基本相同
	if (root == nullptr)
	{
		root = BuyAVLTreeNode(K);
		return;
	}

	AVLTreeNode* parent = nullptr;
	AVLTreeNode* cur = root;
	while (cur)
	{
		if (K > cur->key)
		{
			parent = cur;
			cur = cur->right;
		}
		else if (K < cur->key)
		{
			parent = cur;
			cur = cur->left;
		}
		else
		{
			return;
		}
	}

	cur = BuyAVLTreeNode(K);
	if (K > parent->key)
	{
		parent->right = cur;
	}
	else
	{
		parent->left = cur;
	}

	cur->parent = parent;

	// 更新平衡因子
	// 最远要更新到根为止
	while (parent)
	{
		// 右++
		if (cur == parent->right)
		{
			parent->bf++;
		}
		// 左--
		else
		{
			parent->bf--;
		}
		
		// 判断是否要继续更新
		// 如果bf为0，说明到该位置已经平衡了，不需要再往上更新了
		if (parent->bf == 0)
		{
			break;
		}
		// 插入结点导致一边变高了
		else if (parent->bf == 1 || parent->bf == -1)
		{
			// 子树的高度变了，继续往上更新
			cur = cur->parent;
			parent = parent->parent;
		}
		// 插入结点导致本来就高的一边又变高了
		else if (parent->bf == 2 || parent->bf == -2)
		{
			// 子树不平衡 -- 需要旋转处理

			// 左单旋
			if (parent->bf == 2 && cur->bf == 1)
			{
				RotateL(root, parent);
			}
			// 右单旋
			else if (parent->bf == -2 && cur->bf == -1)
			{
				RotateR(root, parent);
			}
			// 左右双旋
			else if (parent->bf == -2 && cur->bf == 1)
			{
				RotateLR(root, parent);
			}
			// 右左双旋
			else if (parent->bf == 2 && cur->bf == -1)
			{
				RotateRL(root, parent);
			}
			
			break;
		}
		else
		{
			// 到这说明之前的有错误，断言报错
			assert(false);
		}
	}
}

// 二叉平衡树创建
AVLTreeNode* AVLTreeCreate(const vector<int>& v)
{
	AVLTreeNode* root = nullptr;
	for (int i = 0; i < v.size(); ++i)
	{
		AVLTreeInsert(root, v[i]);
	}

	return root;
}

// 使用顺序查找，查找1万个数所用时间
int SequentialSTime1(const vector<int>& v, int n, vector<int>& index, int& cnt)
{
	int begin = clock();
	for (int i = 1; i <= 10000; ++i)
	{
		SequentialSearch(v, n, i, index, cnt);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用折半查找，查找1万个数所用时间
int BinarySTime1(const vector<int>& v, int n, vector<int>& index, int& cnt)
{
	// 要进行折半查找，要先排序，排序不能算折半查找的时间
	vector<int> sortV(v.begin(), v.end());
	QuickSort(sortV, 0, n - 1);

	int begin = clock();
	for (int i = 1; i <= 10000; ++i)
	{
		BinarySearch(v, n, i, index, cnt);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用二叉排序树查找，查找1万个数所用时间
int BSTreeTime1(const vector<int>& v, int n)
{
	// 先建一个二叉排序树
	BSTreeNode * BStree = BSTreeCreate(v);

	int begin = clock();
	for (int i = 1; i <= 10000; ++i)
	{
		BSTreeFind(BStree, i);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用二叉平衡树查找，查找1万个数所用时间
int AVLTreeTime1(const vector<int>& v, int n)
{
	// 先建一个二叉平衡树
	AVLTreeNode* AVLtree = AVLTreeCreate(v);

	int begin = clock();
	for (int i = 1; i <= 10000; ++i)
	{
		AVLTreeFind(AVLtree, i);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用折半查找，查找100万个数所用时间
int BinarySTime2(const vector<int>& v, int n, vector<int>& index, int& cnt)
{
	// 要进行折半查找，要先排序，排序不能算折半查找的时间
	vector<int> sortV(v.begin(), v.end());
	QuickSort(sortV, 0, n - 1);

	int begin = clock();
	for (int i = 1; i <= 1000000; ++i)
	{
		BinarySearch(v, n, i % 10000, index, cnt);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用二叉排序树查找，查找100万个数所用时间
int BSTreeTime2(const vector<int>& v, int n)
{
	// 先建一个二叉排序树
	BSTreeNode* BStree = BSTreeCreate(v);

	int begin = clock();
	for (int i = 1; i <= 1000000; ++i)
	{
		BSTreeFind(BStree, i % 10000);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用二叉平衡树查找，查找100万个数所用时间
int AVLTreeTime2(const vector<int>& v, int n)
{
	// 先建一个二叉平衡树
	AVLTreeNode* AVLtree = AVLTreeCreate(v);

	int begin = clock();
	for (int i = 1; i <= 1000000; ++i)
	{
		AVLTreeFind(AVLtree, i % 10000);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

void CompareTime(const vector<int>& v, int n, vector<int>& index, int& cnt)
{
	int t1_1 = SequentialSTime1(v, n, index, cnt);
	int t1_2 = BinarySTime1(v, n, index, cnt);
	int t1_3 = BSTreeTime1(v, n);
	int t1_4 = AVLTreeTime1(v, n);

	cout << "第一次使用四种查找算法查找1万个数测试" << endl;
	cout << "使用顺序查找1万个数所需时间: " << t1_1 << endl;
	cout << "使用折半查找1万个数所需时间: " << t1_2 << endl;
	cout << "使用二叉排序树查找1万个数所需时间: " << t1_3 << endl;
	cout << "使用二叉平衡树(AVL树)查找1万个数所需时间: " << t1_4 << endl;
	cout << endl;



	cout << "第二次使用除顺序查找以外的查找算法查找100万个数测试" << endl;
	int t2_2 = BinarySTime2(v, n, index, cnt);
	int t2_3 = BSTreeTime2(v, n);
	int t2_4 = AVLTreeTime2(v, n);

	cout << "使用折半查找100万个数所需时间: " << t2_2 << endl;
	cout << "使用二叉排序树查找100万个数所需时间: " << t2_3 << endl;
	cout << "使用二叉平衡树(AVL树)查找100万个数所需时间: " << t2_4 << endl;
	cout << endl;
}

// 查找菜单
void menu()
{
	cout << "1. 顺序查找        2. 折半查找" << endl;
	cout << "3. 二叉排序树查找  4. 二叉平衡树查找" << endl;
	cout << "5. 比较查找算法执行时间" << endl;
	cout << "0. 退出" << endl;
}

int main()
{
	// 随机数发生器初始化
	srand((unsigned int)time(nullptr));
	int n = 10000;
	vector<int> v(10000);
	// 随机生成查找数据
	for (int i = 0; i < n; ++i)
	{
		// rand() + i 使生成的重复数据变少
		v[i] = (rand() + i) % 10000;
	}

	int input = 0;
	int num = 0;
	int cnt = 0;
	int flag = 0;
	vector<int> sortV(v.begin(), v.end());
	vector<int> index;
	BSTreeNode* BStree;
	AVLTreeNode* AVLtree;

	do
	{
		// 调用菜单
		menu();
		cout << "请选择要使用的查找算法>:";
		cin >> input;
		// 根据输入的数，执行不同的操作
		switch (input)
		{
		case 1:
			cout << "请输入要查找的数>:";
			cin >> num;
			SequentialSearch(v, n, num, index, cnt);
			cout << "出现次数: " << cnt << endl;
			if (cnt != 0)
			{
				cout << "下标所在位置: ";
				for (int i = 0; i < index.size(); ++i)
				{
					cout << index[i] << " ";
				}
				cout << endl << endl;
			}
			else
			{
				cout << "没有找到该数" << endl;
			}
			break;
		case 2:
			cout << "请输入要查找的数>:";
			cin >> num;
			// 先排序，并将排序后的结果放入sortV中
			if (flag == 0)
			{
				QuickSort(sortV, 0, n - 1);
				flag = 1;
			}
			BinarySearch(sortV, n, num, index, cnt);
			cout << "出现次数: " << cnt << endl;
			if (cnt != 0)
			{
				cout << "因为折半查找要先排序，故当前下标所在位置不是原来的下标位置了" << endl;
				cout << "下标所在位置: ";
				for (int i = 0; i < index.size(); ++i)
				{
					cout << index[i] << " ";
				}
				cout << endl << endl;
			}
			else
			{
				cout << "没有找到该数" << endl;
			}
			break;
		case 3:
			cout << "请输入要查找的数>:";
			cin >> num;
			BStree = BSTreeCreate(v);
			if (BSTreeFind(BStree, num))
			{
				cout << "在二叉排序树中找到了该数" << endl;
			}
			else
			{
				cout << "没有找到该数" << endl;
			}
			break;
		case 4:
			cout << "请输入要查找的数>:";
			cin >> num;
			AVLtree = AVLTreeCreate(v);
			if (AVLTreeFind(AVLtree, num))
			{
				cout << "在二叉平衡树中找到了该数" << endl;
			}
			else
			{
				cout << "没有找到该数" << endl;
			}
			break;
		case 5:
			CompareTime(v, n, index, cnt);
			break;
		case 0:
			cout << "退出" << endl;
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
		}
	} while (input);


	return 0;
}