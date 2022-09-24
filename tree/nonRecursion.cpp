//使用迭代后序遍历二叉树
#include<iostream>
#include<stack>
using namespace std;

class BTnode {
public:
	int data;
	BTnode *lchild, *rchild;
public:
	BTnode(int x, BTnode *l = NULL, BTnode *r = NULL) {
		this->data = x;
		this->lchild = l;
		this->rchild = r;
	}
};

//辅助函数：递归构造
void constcutBTnode(BTnode* root, int num[][2]) {
	int i = root->data;
	if (num[i-1][0] != 0) {
		root->lchild = new BTnode(num[i-1][0]);
	}
	if (num[i-1][1] != 0) {
		root->rchild = new BTnode(num[i-1][1]);
	}
	if (root->lchild != NULL) {
		constcutBTnode(root->lchild, num);
	}
	if (root->rchild != NULL) {
		constcutBTnode(root->rchild, num);
	}
}

//构造二叉树
BTnode* constcutBT() {
	int n;
	cin >> n;
	int num[n][2];
	for(int i = 0; i < n; i += 1) {
		cin >> num[i][0] >> num[i][1];
	}
	BTnode *root = new BTnode(1);
	constcutBTnode(root, num);
	return root;
}

//非递归后序遍历
void postorder(BTnode *tree) {
	stack<BTnode*> nodeStack; //用来存储结点的辅助栈
	BTnode *lastNode; //用来标记前一个访问的节点
	while (tree || !nodeStack.empty()) {
		if (tree) {
			nodeStack.push(tree);
			tree = tree->lchild;  //遍历左节点
		} else {
			tree = nodeStack.top(); //找到最左边的节点
			nodeStack.pop();
			if (tree->rchild && tree->rchild != lastNode) { //如果有没有遍历右孩子要先遍历右节点
				nodeStack.push(tree);
				tree = tree->rchild; //遍历右节点
			} else {
				cout << tree->data << " ";
				lastNode = tree; //遍历完后标记，防止重复遍历右节点
				tree = NULL;
			}
		}

	}
}

int main() {
	BTnode *tree = constcutBT();
	postorder(tree);
	return 0;
}
