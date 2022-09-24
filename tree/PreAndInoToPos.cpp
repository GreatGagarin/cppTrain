//通过二叉树的前序遍历与中序遍历生成后序遍历
#include <iostream>
#include <vector>

using namespace std;

class BTnode {
public:
	int data;
	BTnode *lchild, *rchild;

	BTnode(int x, BTnode *l = NULL, BTnode *r = NULL) {
		this->data = x;
		this->lchild = l;
		this->rchild = r;
	}
};

void input(int &len, vector<int> &preOrder, vector<int> &inOrder);
void postOrder(BTnode *tree);
BTnode* preBuild(vector<int> &pre, vector<int> &in, int &preIndex, int begin, int end); 

int main() {
	int len;
	vector<int> preOrder; //前序遍历数组
	vector<int> inOrder; //中序遍历数组
	input(len, preOrder, inOrder);
	int preIndex = 0; //当前处理的数据在前序遍历中的位置
	int begin = 0, end = len - 1; //迭代中树后续遍历的开始与结束位置

	BTnode *tree = preBuild(preOrder, inOrder, preIndex, begin, end);
	postOrder(tree);
	return 0;
}

void input(int &len, vector<int> &preOrder, vector<int> &inOrder) {
	cin >> len;
	for (int i = 0; i < len * 2; i += 1) {
		int temp;
		cin >> temp;
		if (i < len) {
			preOrder.push_back(temp);
		} else {
			inOrder.push_back(temp);
		}
	}
}

void postOrder(BTnode *tree) {
	if (tree == NULL) {
		return;
	}
	postOrder(tree->lchild);
	postOrder(tree->rchild);
	cout << tree->data << " ";
}

BTnode* preBuild(vector<int> &pre, vector<int> &in, int &preIndex, int begin, int end) {
	int currentItem = pre[preIndex];
	preIndex += 1;
	BTnode *root = new BTnode(currentItem);
	int currentIndex = begin; //当前处理数据在后续遍历中的位置
	while (in[currentIndex] != currentItem) {
		currentIndex += 1;
	}
	if (currentIndex > begin) {
		root->lchild = preBuild(pre, in, preIndex, begin, currentIndex - 1);
	}
	if (currentIndex < end) {
		root->rchild = preBuild(pre, in, preIndex, currentIndex + 1, end);
	}
	return root;
}
