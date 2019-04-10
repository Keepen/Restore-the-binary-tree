#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree {
	char value;
	struct Tree* left;
	struct Tree* right;
}Tree;



//�������
Tree* treeNode(char value) {
	Tree* node = (Tree*)malloc(sizeof(Tree));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

//�������
void preOrder(Tree* root) {
	if (root == NULL) {
		return;
	}
	printf("%c  ", root->value);
	preOrder(root->left);
	preOrder(root->right);
	return;
}

//����Ԫ��
int findValue(char mid[], int size,char value) {
	int pos = -1;
	for (int i = 0; i < size; ++i) {
		if (mid[i] == value) {
			pos = i;
		}
	}
	return pos;
}



//ͨ���������������ԭ������
//���������Ҹ��ڵ㣬�����и��ڵ���±�������������ĸ���
//�ɴ˵ݹ鴦��ֱ������������нڵ�
Tree* recoverTree(char pre[],char mid[],int size) {
	//���õĽ����ĿΪ0
	if (size == 0) {
		return NULL;
	}
	//���ڵ��ֵ,������������ҵ����ڵ���±�
	char rootValue = pre[0];
	int leftsize = findValue(mid,size, rootValue);

	//�������ڵ�
	Tree* root = (Tree*)malloc(sizeof(Tree));
	root->value = rootValue;

	//����������
	root->left = recoverTree(pre + 1,	//�������������
		mid,				//���������������
		leftsize			//�������Ŀ���Ԫ�ظ���
		);
	//����������
	root->right = recoverTree(pre + leftsize + 1,	//���������������
		mid + leftsize + 1,					//���������������
		size - 1 - leftsize			//�������Ľ�����
		);
	return root;
}

Tree* recoverTree2(char mid[], char post[], int size) {
	//û�н����ã��˳��ݹ�
	if (size == 0) {
		return NULL;
	}

	//�ȴ������ڵ�
	char rootValue = post[size-1];
	Tree* root = (Tree*)malloc(sizeof(Tree));
	root->value = rootValue;
	//������������ҵ����ڵ���±꣬������������
	int leftsize = findValue(mid, size, rootValue);
	//����������
	root->left = recoverTree2(mid, post, leftsize);
	//����������
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