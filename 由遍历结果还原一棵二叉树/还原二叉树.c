#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree {
	char value;
	struct Tree* left;
	struct Tree* right;
}Tree;



//创建结点
Tree* treeNode(char value) {
	Tree* node = (Tree*)malloc(sizeof(Tree));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

//先序遍历
void preOrder(Tree* root) {
	if (root == NULL) {
		return;
	}
	printf("%c  ", root->value);
	preOrder(root->left);
	preOrder(root->right);
	return;
}

//查找元素
int findValue(char mid[], int size,char value) {
	int pos = -1;
	for (int i = 0; i < size; ++i) {
		if (mid[i] == value) {
			pos = i;
		}
	}
	return pos;
}



//通过先序和中序来还原二叉树
//在中序中找根节点，中序中根节点的下标就是左子树结点的个数
//由此递归处理，直到处理完毕所有节点
Tree* recoverTree(char pre[],char mid[],int size) {
	//可用的结点数目为0
	if (size == 0) {
		return NULL;
	}
	//根节点的值,在中序遍历中找到根节点的下标
	char rootValue = pre[0];
	int leftsize = findValue(mid,size, rootValue);

	//创建根节点
	Tree* root = (Tree*)malloc(sizeof(Tree));
	root->value = rootValue;

	//创建左子树
	root->left = recoverTree(pre + 1,	//左子树先序遍历
		mid,				//左子树的中序遍历
		leftsize			//左子树的可用元素个数
		);
	//创建右子树
	root->right = recoverTree(pre + leftsize + 1,	//右子树的先序遍历
		mid + leftsize + 1,					//右子树的中序遍历
		size - 1 - leftsize			//右子树的结点个数
		);
	return root;
}

Tree* recoverTree2(char mid[], char post[], int size) {
	//没有结点可用，退出递归
	if (size == 0) {
		return NULL;
	}

	//先创建根节点
	char rootValue = post[size-1];
	Tree* root = (Tree*)malloc(sizeof(Tree));
	root->value = rootValue;
	//在中序遍历中找到根节点的下标，划分左右子树
	int leftsize = findValue(mid, size, rootValue);
	//创建左子树
	root->left = recoverTree2(mid, post, leftsize);
	//创建右子树
	root->right = recoverTree2(mid + 1 + leftsize, post + leftsize, size - 1 - leftsize);
	return root;
}



void test() {
	char pre[] = "ABDECG";
	char mid[] = "DEBAGC";
	int strsize = strlen(pre);
	Tree* root = recoverTree(pre, mid, strsize);
	preOrder(root);

	//Tree* a = treeNode('A');
	//Tree* b = treeNode('B');
	//Tree* c = treeNode('C');
	//Tree* d = treeNode('D');
	//Tree* e = treeNode('E');
	//a->left = b; a->right = c;
	//b->left = d; b->right = e;
	//preOrder(a);

}

void test2() {
	char mid[] = "DEBAGC";
	char post[] = "EDBGCA";
	int size = strlen(mid);
	Tree* root = recoverTree2(mid, post, size);
	preOrder(root);
}

int main() {
	test();
	printf("\n");
	test2();
	system("pause");
	return 0;
}