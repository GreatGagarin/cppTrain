//二叉树最长路径
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BTnode {
public:
	int data, index;
	BTnode *lchild, *rchild;

	BTnode(int x, int i = 0, BTnode *l = NULL, BTnode *r = NULL) {
		this->data = x;
		this->index = i;
		this->lchild = l;
		this->rchild = r;
	}
};

void input(int &len, vector<vector<int>> &data);
BTnode* preBuild(int len, vector<vector<int>> &data);
int MaxLengthPath(BTnode *root);

int main() {
	int len;
	vector<vector<int>> data;
	input(len, data);
	BTnode *tree = preBuild(len, data);
	int maxLength = MaxLengthPath(tree);
	cout << maxLength;
	return 0;
}

void input(int &len, vector<vector<int>> &data) {
	cin >> len;
	for (int i = 0; i < len; i += 1) {
		vector<int> temp;
		for (int i = 0; i < 3; i += 1) {
			int t;
			cin >> t;
			temp.push_back(t);
		}
		data.push_back(temp);
	}
}

void preBuild(BTnode *tree, int len, vector<vector<int>> &data) {
	int i = tree->index;
	int lindex = data[i - 1][0], rindex = data[i - 1][1];
	if (lindex > 0) {
		tree->lchild = new BTnode(data[lindex - 1][2], lindex);
	}
	if (rindex > 0) {
		tree->rchild = new BTnode(data[rindex - 1][2], rindex);
	}
	if (tree->lchild != NULL) {
		preBuild(tree->lchild, len, data);
	}
	if (tree->rchild != NULL) {
		preBuild(tree->rchild, len, data);
	}
}

BTnode* preBuild(int len, vector<vector<int>> &data) {
	BTnode *tree = new BTnode(data[0][2], 1);
	preBuild(tree, len, data);
	return tree;
}


int MaxLengthPath(BTnode *root, int &maxLength) {
	if (root == NULL) {
		return 0;
	}
	int lmax = MaxLengthPath(root->lchild, maxLength);
	int rmax = MaxLengthPath(root->rchild, maxLength);
	maxLength = max(maxLength, root->data + lmax + rmax);
	return max(lmax, rmax) + root->data;
}

int MaxLengthPath(BTnode *root) { 
	int maxLength = 0;
	MaxLengthPath(root, maxLength);
	return maxLength;
}
