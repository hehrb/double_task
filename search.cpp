#include <iostream>
#include <cstdio>
#include <ctime>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

// ˳�����
void SequentialSearch(const vector<int>& v, int n, int num, vector<int>& index, int& cnt)
{
	index.clear();
	cnt = 0;
	// ��������
	for (int i = 0; i < n; ++i)
	{
		if (v[i] == num)
		{
			index.push_back(i);
			++cnt;
		}
	}
}

// ǰ��ָ�뷨����һ�˿���
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

// �ݹ���п���
void QuickSort(vector<int>& sortV, int begin, int end)
{
	if (begin >= end)
	{
		return;
	}

	int keyi = PartSort(sortV, begin, end);

	// �ݹ飬�ֳ���������ֱ��ٴν��п���
	QuickSort(sortV, begin, keyi - 1);
	QuickSort(sortV, keyi + 1, end);
}

// �۰����
void BinarySearch(const vector<int>& v, int n, int num, vector<int>& index, int& cnt)
{
	index.clear();
	cnt = 0;

	int left = 0; // ���±�
	int right = n - 1; // ���±�
	int l = 0; // ��¼����������
	int r = 0; // ��¼����������

	// ��ΪĿ��ֵ���ܴ��ڶ�������Ҫ�ҵ���������

	// ��������������
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

	// �������������ֵ����Ŀ��ֵ��˵��������Ŀ��ֵ
	if (v[left] != num)
	{
		return;
	}
	// ���ڣ���ȥ��������
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

	// cnt����Ŀ��ֵ�ĸ���
	cnt = r - l + 1;
	for (int i = l; i <= r; ++i)
	{
		index.push_back(i);
	}
}

// ���������������㷨

// �������������
struct BSTreeNode
{
	BSTreeNode* left; // ������
	BSTreeNode* right; // ������
	int key; // �ؼ�ֵ
};

// ��������������
bool BSTreeFind(BSTreeNode* root, int K)
{
	BSTreeNode* cur = root;
	while (cur)
	{
		// Ҫ���ҵ�Kֵ���ڵ�ǰ����key����������
		if (K > cur->key)
		{
			cur = cur->right;
		}
		// Ҫ���ҵ�KֵС�ڵ�ǰ����key����������
		else if (K < cur->key)
		{
			cur = cur->left;
		}
		// Ҫ���ҵ�Kֵ���ڵ�ǰ����key��˵���ҵ���
		else
		{
			return true;
		}
	}

	return false;
}

// ���������������½��
BSTreeNode* BuyBSTreeNode(int K)
{
	BSTreeNode* newnode = new BSTreeNode;
	// �ɹ�new��һ���½��
	if (newnode != nullptr)
	{
		newnode->key = K;
		newnode->left = nullptr;
		newnode->right = nullptr;

		return newnode;
	}

	// ʧ�ܷ���nullptr
	return nullptr;
}

// ��������������
void BSTreeInsert(BSTreeNode*& root, int K)
{
	if (root == nullptr)
	{
		root = BuyBSTreeNode(K);
		return;
	}

	// ����һ�������parent���Ա��������²���Ľ��
	BSTreeNode* parent = nullptr;
	BSTreeNode* cur = root;
	while (cur)
	{
		// Ҫ�����Kֵ���ڵ�ǰ����key����������
		if (K > cur->key)
		{
			parent = cur;
			cur = cur->right;
		}
		// Ҫ�����KֵС�ڵ�ǰ����key����������
		else if (K < cur->key)
		{
			parent = cur;
			cur = cur->left;
		}
		// ����һ����������������Ѿ������Ԫ�أ����ظ�Ԫ�أ�
		// ��Ͳ����ٽ��в����ˣ�ֱ�ӽ���
		else
		{
			return;
		}
	}

	// cur��ǰ����λ�þ��Ƕ��������������Kֵ��Ӧ�����λ��
	cur = BuyBSTreeNode(K);
	// ���Kֵ������parent����keyֵ�󣬾���parent���� ���Ӹý��cur
	if (K > parent->key)
	{
		parent->right = cur;
	}
	// ���Kֵ������parent����keyֵС������parent���� ���Ӹý��cur
	else
	{
		parent->left = cur;
	}
}

// ��������������
BSTreeNode* BSTreeCreate(const vector<int>& v)
{
	BSTreeNode* root = nullptr;
	for (int i = 0; i < v.size(); ++i)
	{
		BSTreeInsert(root, v[i]);
	}

	return root;
}


// ����ƽ����(AVL��)�����㷨

// ����ƽ����(AVL��)���
struct AVLTreeNode
{
	// 3����
	AVLTreeNode* left; // ������
	AVLTreeNode* right; // ������
	AVLTreeNode* parent; // ���׽��
	int key; // �ؼ�ֵ
	int bf; // ƽ������
};

// ����ƽ��������
// �����ʵ������һ��������������ͬ
bool AVLTreeFind(AVLTreeNode* root, int K)
{
	AVLTreeNode* cur = root;
	while (cur)
	{
		// Ҫ���ҵ�Kֵ���ڵ�ǰ����key����������
		if (K > cur->key)
		{
			cur = cur->right;
		}
		// Ҫ���ҵ�Kֵ���ڵ�ǰ����key����������
		else if (K < cur->key)
		{
			cur = cur->left;
		}
		// Ҫ���ҵ�Kֵ���ڵ�ǰ����key��˵���ҵ���
		else
		{
			return true;
		}
	}

	return false;
}

// ����
void RotateL(AVLTreeNode*& root, AVLTreeNode* parent)
{
	// subR: parent���Һ���
	AVLTreeNode* subR = parent->right;
	// subRL: subR������
	AVLTreeNode* subRL = subR->left;
	// ppNode: parent��parent
	AVLTreeNode* ppNode = parent->parent;

	// ��ת����µ����ӹ�ϵ
	parent->right = subRL;
	parent->parent = subR;
	// ����subRL����Ϊ�գ�Ҫ�ж�
	if (subRL)
	{
		subRL->parent = parent;
	}
	subR->left = parent;

	// parent���Ǹ���㣬ֱ����subR����µĸ����
	if (parent == root)
	{
		root = subR;
		root->parent = nullptr;
	}
	// parent���Ǹ����
	else
	{
		// �ж�ԭ����parent��ppNode�����ӻ����Һ���
		if (ppNode->left == parent)
		{
			ppNode->left = subR;
		}
		else
		{
			ppNode->right = subR;
		}

		// �����������subR��parentΪppNode
		subR->parent = ppNode;
	}

	// ����ƽ������
	subR->bf = 0;
	parent->bf = 0;
}

// �ҵ���
void RotateR(AVLTreeNode*& root, AVLTreeNode* parent)
{
	// subL: parent������
	AVLTreeNode* subL = parent->left;
	// subLR: subL���Һ���
	AVLTreeNode* subLR = subL->right;
	// ppNode: parent��parent
	AVLTreeNode* ppNode = parent->parent;

	parent->left = subLR;
	parent->parent = subL;
	// ����subLR����Ϊ�գ�Ҫ�ж�
	if (subLR)
	{
		subLR->parent = parent;
	}
	subL->right = parent;

	// parent���Ǹ���㣬ֱ����subR����µĸ����
	if (parent == root)
	{
		root = subL;
		root->parent = nullptr;
	}
	// parent���Ǹ����
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

	// ����ƽ������
	subL->bf = 0;
	parent->bf = 0;
}

// ����˫��
void RotateLR(AVLTreeNode*& root, AVLTreeNode* parent)
{
	AVLTreeNode* subL = parent->left;
	AVLTreeNode* subLR = subL->right;
	int bf = subLR->bf;

	RotateL(root, parent->left);
	RotateR(root, parent);

	// ����ƽ������(���������)
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
		// ����˵��֮ǰ��ת���������ˣ�ֱ�Ӷ��Ա���
		assert(false);
	}
}

// ����˫��
void RotateRL(AVLTreeNode*& root, AVLTreeNode* parent)
{
	AVLTreeNode* subR = parent->right;
	AVLTreeNode* subRL = subR->left;
	int bf = subRL->bf;

	RotateR(root, parent->right);
	RotateL(root, parent);

	// ����ƽ������(���������)
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
		// ����˵��֮ǰ��ת���������ˣ�ֱ�Ӷ��Ա���
		assert(false);
	}
}

// ����ƽ���������½��
AVLTreeNode* BuyAVLTreeNode(int K)
{
	AVLTreeNode* newnode = new AVLTreeNode;
	// �ɹ�new��һ���½��
	if (newnode != nullptr)
	{
		newnode->key = K;
		newnode->bf = 0;
		newnode->left = nullptr;
		newnode->right = nullptr;
		newnode->parent = nullptr;

		return newnode;
	}

	// ʧ�ܷ���nullptr
	return nullptr;
}


// ����ƽ��������
void AVLTreeInsert(AVLTreeNode*& root, int K)
{
	// ǰ�������������������ͬ
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

	// ����ƽ������
	// ��ԶҪ���µ���Ϊֹ
	while (parent)
	{
		// ��++
		if (cur == parent->right)
		{
			parent->bf++;
		}
		// ��--
		else
		{
			parent->bf--;
		}
		
		// �ж��Ƿ�Ҫ��������
		// ���bfΪ0��˵������λ���Ѿ�ƽ���ˣ�����Ҫ�����ϸ�����
		if (parent->bf == 0)
		{
			break;
		}
		// �����㵼��һ�߱����
		else if (parent->bf == 1 || parent->bf == -1)
		{
			// �����ĸ߶ȱ��ˣ��������ϸ���
			cur = cur->parent;
			parent = parent->parent;
		}
		// �����㵼�±����͸ߵ�һ���ֱ����
		else if (parent->bf == 2 || parent->bf == -2)
		{
			// ������ƽ�� -- ��Ҫ��ת����

			// ����
			if (parent->bf == 2 && cur->bf == 1)
			{
				RotateL(root, parent);
			}
			// �ҵ���
			else if (parent->bf == -2 && cur->bf == -1)
			{
				RotateR(root, parent);
			}
			// ����˫��
			else if (parent->bf == -2 && cur->bf == 1)
			{
				RotateLR(root, parent);
			}
			// ����˫��
			else if (parent->bf == 2 && cur->bf == -1)
			{
				RotateRL(root, parent);
			}
			
			break;
		}
		else
		{
			// ����˵��֮ǰ���д��󣬶��Ա���
			assert(false);
		}
	}
}

// ����ƽ��������
AVLTreeNode* AVLTreeCreate(const vector<int>& v)
{
	AVLTreeNode* root = nullptr;
	for (int i = 0; i < v.size(); ++i)
	{
		AVLTreeInsert(root, v[i]);
	}

	return root;
}

// ʹ��˳����ң�����1���������ʱ��
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

// ʹ���۰���ң�����1���������ʱ��
int BinarySTime1(const vector<int>& v, int n, vector<int>& index, int& cnt)
{
	// Ҫ�����۰���ң�Ҫ���������������۰���ҵ�ʱ��
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

// ʹ�ö������������ң�����1���������ʱ��
int BSTreeTime1(const vector<int>& v, int n)
{
	// �Ƚ�һ������������
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

// ʹ�ö���ƽ�������ң�����1���������ʱ��
int AVLTreeTime1(const vector<int>& v, int n)
{
	// �Ƚ�һ������ƽ����
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

// ʹ���۰���ң�����100���������ʱ��
int BinarySTime2(const vector<int>& v, int n, vector<int>& index, int& cnt)
{
	// Ҫ�����۰���ң�Ҫ���������������۰���ҵ�ʱ��
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

// ʹ�ö������������ң�����100���������ʱ��
int BSTreeTime2(const vector<int>& v, int n)
{
	// �Ƚ�һ������������
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

// ʹ�ö���ƽ�������ң�����100���������ʱ��
int AVLTreeTime2(const vector<int>& v, int n)
{
	// �Ƚ�һ������ƽ����
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

	cout << "��һ��ʹ�����ֲ����㷨����1���������" << endl;
	cout << "ʹ��˳�����1���������ʱ��: " << t1_1 << endl;
	cout << "ʹ���۰����1���������ʱ��: " << t1_2 << endl;
	cout << "ʹ�ö�������������1���������ʱ��: " << t1_3 << endl;
	cout << "ʹ�ö���ƽ����(AVL��)����1���������ʱ��: " << t1_4 << endl;
	cout << endl;



	cout << "�ڶ���ʹ�ó�˳���������Ĳ����㷨����100���������" << endl;
	int t2_2 = BinarySTime2(v, n, index, cnt);
	int t2_3 = BSTreeTime2(v, n);
	int t2_4 = AVLTreeTime2(v, n);

	cout << "ʹ���۰����100���������ʱ��: " << t2_2 << endl;
	cout << "ʹ�ö�������������100���������ʱ��: " << t2_3 << endl;
	cout << "ʹ�ö���ƽ����(AVL��)����100���������ʱ��: " << t2_4 << endl;
	cout << endl;
}

// ���Ҳ˵�
void menu()
{
	cout << "1. ˳�����        2. �۰����" << endl;
	cout << "3. ��������������  4. ����ƽ��������" << endl;
	cout << "5. �Ƚϲ����㷨ִ��ʱ��" << endl;
	cout << "0. �˳�" << endl;
}

int main()
{
	// �������������ʼ��
	srand((unsigned int)time(nullptr));
	int n = 10000;
	vector<int> v(10000);
	// ������ɲ�������
	for (int i = 0; i < n; ++i)
	{
		// rand() + i ʹ���ɵ��ظ����ݱ���
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
		// ���ò˵�
		menu();
		cout << "��ѡ��Ҫʹ�õĲ����㷨>:";
		cin >> input;
		// �������������ִ�в�ͬ�Ĳ���
		switch (input)
		{
		case 1:
			cout << "������Ҫ���ҵ���>:";
			cin >> num;
			SequentialSearch(v, n, num, index, cnt);
			cout << "���ִ���: " << cnt << endl;
			if (cnt != 0)
			{
				cout << "�±�����λ��: ";
				for (int i = 0; i < index.size(); ++i)
				{
					cout << index[i] << " ";
				}
				cout << endl << endl;
			}
			else
			{
				cout << "û���ҵ�����" << endl;
			}
			break;
		case 2:
			cout << "������Ҫ���ҵ���>:";
			cin >> num;
			// �����򣬲��������Ľ������sortV��
			if (flag == 0)
			{
				QuickSort(sortV, 0, n - 1);
				flag = 1;
			}
			BinarySearch(sortV, n, num, index, cnt);
			cout << "���ִ���: " << cnt << endl;
			if (cnt != 0)
			{
				cout << "��Ϊ�۰����Ҫ�����򣬹ʵ�ǰ�±�����λ�ò���ԭ�����±�λ����" << endl;
				cout << "�±�����λ��: ";
				for (int i = 0; i < index.size(); ++i)
				{
					cout << index[i] << " ";
				}
				cout << endl << endl;
			}
			else
			{
				cout << "û���ҵ�����" << endl;
			}
			break;
		case 3:
			cout << "������Ҫ���ҵ���>:";
			cin >> num;
			BStree = BSTreeCreate(v);
			if (BSTreeFind(BStree, num))
			{
				cout << "�ڶ������������ҵ��˸���" << endl;
			}
			else
			{
				cout << "û���ҵ�����" << endl;
			}
			break;
		case 4:
			cout << "������Ҫ���ҵ���>:";
			cin >> num;
			AVLtree = AVLTreeCreate(v);
			if (AVLTreeFind(AVLtree, num))
			{
				cout << "�ڶ���ƽ�������ҵ��˸���" << endl;
			}
			else
			{
				cout << "û���ҵ�����" << endl;
			}
			break;
		case 5:
			CompareTime(v, n, index, cnt);
			break;
		case 0:
			cout << "�˳�" << endl;
			break;
		default:
			cout << "�����������������" << endl;
		}
	} while (input);


	return 0;
}