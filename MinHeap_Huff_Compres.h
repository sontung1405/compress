#include<iostream>
using namespace std;
#include<queue>
#include<string>
#include<vector>
#include<iomanip>


// xây dụng cấu trúc min heap
struct MinHeapNode {

	// ký tự đầu vào
	int data;

	// tần số ký tự đó
	int freq;

	MinHeapNode *left, *right;

	MinHeapNode(int data, int freq)
	{

		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

// so sánh hai nút heap (cần trong heap tối thiểu)
struct compare {

	bool operator()(MinHeapNode* l, MinHeapNode* r) // thực hiện từ trái sang phải l -> r

	{
		return (l->freq > r->freq); // trả về true nếu 2 l.freq > r.freq , sai trả về false
	}
};

void printCodes(struct MinHeapNode* root, string str);
void printTree(ostream & out, struct MinHeapNode* root, int indent);
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
void HuffmanCodes(int data[], int freq[], int size);
int total_bits_written();
void cal_compressionRatio();
void write_codes(char*filename);
void calculate_frequency(int frequency[], char filename[]);
void SeperateCharacter(int frequency[], int actual_frequency[], int ASCII_values[]);
void Convert_StringBits_to_IntegerBits();
void printFrequencyTable(int actual_frequency[], int ASCII_values[]);