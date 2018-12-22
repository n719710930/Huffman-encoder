#pragma once
#include <stdio.h>  
#include <stdlib.h>  
#include <string>  
#include <iostream>  
#include <bitset>  
#include <fstream>  
#include <time.h>  

#define CharCount 256  

using namespace std;

CStringA strFilename = "0";
/*Huffman Tree's Node*/
struct TreeNode {
	int value;
	int alpha;
	string code;
	TreeNode * lChild;
	TreeNode * rChild;
	TreeNode() { 
		value = 0; 
		alpha = 0;  
		lChild = rChild = NULL; 
		code = ""; } //���캯��  
};

/*�����㣬��������Huffman��*/
struct ListNode {
	TreeNode huffNode;
	ListNode * child;
	ListNode() { child = NULL; } //���캯��         
};

//���������ļ���ͳ����Ϣ��hash��  
struct hashTable {
	int value;
	int alpha;
	hashTable() { alpha = 0; value = 0; }
}Ascii[CharCount];


//qsort��������  
int Comp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

TreeNode * CreateHuffmanTree(hashTable ascii[])
{
	ListNode * root = new ListNode;
	ListNode * next = root;     //rootָ���һ���ڵ㣬�˽ڵ�����Ϣ  

	for (int i = 0; /*i<127*/; i++)
	{
		if (ascii[i].value == 0)
			continue;

		next->huffNode.value = ascii[i].value;
		next->huffNode.alpha = ascii[i].alpha;

		if (i == CharCount - 1) //��ֹ�ཨһ�����õĽڵ�  
			break;

		next->child = new ListNode;
		next = next->child;
	}

	//���ɭ���е���>1���ͼ�������ֱ��ɭ�֣�������ֻ��һ��������ʱHuffman��Ҳ�ѽ���  
	while (root->child != NULL)
	{
		ListNode * p = new ListNode;
		/*���½���Ȩֵ��Ϊ��С��������Ȩֵ֮��*/
		p->huffNode.value = root->huffNode.value + root->child->huffNode.value;

		/*���½���е�Huffman�ڵ��е�������������Ϊ������С�ڵ��е�Huffman�ڵ�*/
		p->huffNode.lChild = &(root->huffNode);
		p->huffNode.rChild = &(root->child->huffNode);

		/*��������ɾ����С��������㣬�����ڴ治���ͷţ���Ϊ��Ҫ����Щ�ڵ㹹��Huffman��*/
		root = root->child->child;

		/*�������������򣬼����½�����������뵽���ʵ�λ�ã�ʹ��������򲻱��ƻ�*/
		next = root;
		ListNode * parent = NULL;
		while (next != NULL  && p->huffNode.value >= next->huffNode.value)
		{
			parent = next;
			next = next->child;
		}// find location  

		 //insert  
		if (parent == NULL) // Insert into start.  
		{
			p->child = next;
			root = p;
		}
		else // Insert into middle or end.  
		{
			p->child = next;
			parent->child = p;
		}
	}
	return &(root->huffNode);
}

/*�ַ�-Huffman���*/
string charHuffmanTable[CharCount];

/*�ַ���ջ�������ڱ���Huffman��ʱ�õ�Huffman����*/
string stack;

/*����ǰ�����*/
void preorder(TreeNode * root)
{
	if (root->lChild == NULL && root->rChild == NULL)
	{
		charHuffmanTable[root->alpha] = stack;
		stack.erase(stack.length() - 1);
		return;
	}
	stack.append("0");
	preorder(root->lChild);

	stack.append("1");
	preorder(root->rChild);

	//cout << stack.length() << endl;  
	if (!stack.empty())
		stack.erase(stack.length() - 1);
	//  }  
}


//������һ��"10101001"���ַ���������һ����Ӧ��ASCII�ַ�  
unsigned char StrToBin(string str)
{
	int a = atoi(str.c_str());
	int b = 1;
	int ans = 0;
	while (a != 0)
	{
		ans += a % 10 * b;
		b *= 2;
		a /= 10;
	}
	return (unsigned char)ans;
}

//��unsigned char����ת��Ϊ2�����ַ���  
string BinToStr(unsigned char c)
{
	string ans;
	while (c != 0)
	{
		ans.insert(ans.begin(), unsigned char(c % 2 + '0'));
		c /= 2;
	}

	if (ans.length() < 8)
	{
		ans.insert(ans.begin(), 8 - ans.length(), '0');
	}
	return ans;
}


char decode(TreeNode * root, string & code)
{
	int i = 0;
	for (i = 0; i<code.length(); i++)
	{
		if (root->alpha == 0)
			root = (code[i] - '0') ? root->rChild : root->lChild;
		else
		{
			code.erase(0, i);
			return root->alpha;
		}
	}

	if (root->alpha != 0)
	{
		code.erase(0, i);
		return root->alpha;
	}
	code.erase();
	return '\0';
}