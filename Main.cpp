#include"BitWrite.h"
#include"MinHeap_Huff_Compres.h"
#include "jpeg_encoder.h"
#include <time.h>
#include <cstdio>
string str;
int q = 0;
int count2 = 0; //số bit
int count1 = 0; //số kí tự xuât hiện
int num = 254;
string codes;
char chh = char(num);
vector<pair<char, string> > charactermap;
vector<int> Huffcode; // lưu tất cả các bit 0,1		


// in cây Huffman từ các nốt 
int p;
string str1 = "";
int n = 0;


void printCodes(struct MinHeapNode* root, string str)
{

	if (!root)
		return;

	if (root->data != chh)
	{
		char ch;
		ch = char(root->data);
		//cout << "\t    " << ch << "\t\t\t  " << str << "\n";
		if (root->data == ' ')
		{
			codes = codes + "_" + " " + str + "Í";
		}
		else
			codes = codes + ch + " " + str + "Í";
		for (int i = 0; i < count2; i++)
		{

			if (charactermap[i].first == ch)
			{
				charactermap[i].second = str;
			}
		}
	}
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}
void printTree(ostream & out, struct MinHeapNode* root, int indent)
{
	if (root != NULL)
	{
		printTree(out, root->right, indent + 4);
		out << setw(indent) << " " << (char)root->data << endl;
		printTree(out, root->left, indent + 4);
	}
}
// xây dựng cây Huffman và in mã bằng cách duyệt qua cây Huffman được xây dựng

void HuffmanCodes(int data[], int freq[], int size)
{
	struct MinHeapNode *left, *right, *top;

	// tạo min heap & chèn vào các kí tự data[]


	for (int i = 0; i < size; ++i)                   //Xây dựng heap
		minHeap.push(new MinHeapNode(data[i], freq[i]));

	// lặp lại cho đến khi kích thước heap = 1
	while (minHeap.size() != 1) {

		// trích ra 2 tần số tối thiểu từ min heap
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		// tạo một nút mới bằng tổng 2 nút có tần số của cây con trái, phải 
		top = new MinHeapNode(chh, left->freq + right->freq);

		top->left = left;
		top->right = right;
		minHeap.push(top); //thêm vào đỉnh min heap mới số lượng lúc này tăng lên 1
	}

	// in cây huffman sau khi xây dựng
	printCodes(minHeap.top(), "");
}
int total_bits_written()
{
	string temp;
	int total_bits = 0;
	for (int i = 0; i < charactermap.size(); i++)
	{
		temp = charactermap[i].second;
		for (int j = 0; j < temp.length(); j++)
		{
			total_bits++;
		}
	}
	return total_bits;
}

int ct = 0;
void cal_compressionRatio()
{
	long double csize = 0;
	long double size = 0;
	long long lsize = 0;
	long long lcsize = 0;
	char ch;
	int x;
	x = count2;
	x = x - 1;
	lsize = x;
	lcsize = Huffcode.size() / 8;
	cout << "\nKich thuoc file ban dau  = " << lsize << " Bytes";
	cout << "\nKich thuoc file sau khi nen = " << lcsize << " Bytes";
}

//tính tần số từng kí tự có trong file cần đọc
void calculate_frequency(int frequency[], char filename[])
{
	char ch, ch1;
	int y;
	int f;
	int x;
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Khong the mo file !!!\n";
		cin >> y;
		exit(1);
	}
	while (fin.get(ch))
	{

		if (ch >= 32 && ch < 255)
		{
			charactermap.push_back(make_pair(ch, ""));
			count2++;
		}
		y = int(ch);
		frequency[y] = frequency[y] + 1;
	}
	ch1 = char(168);
	charactermap.push_back(make_pair(ch1, ""));
	count2++;
	fin.close();
}

void write_codes(char*filename)     // tao file luu ma huffman
{
	string Newfile = filename;
	Newfile = Newfile + ".CODE";

	fstream os;
	os.open(Newfile,ios::out);
	for (int i = 0; i < codes.size(); i++)
	{
		if (codes[i] != 'Í')
		{
			os << codes[i];

		}
		else
			os << endl;
	}
	os.close();
}
// lọc tần số các kí tự
void SeperateCharacter(int frequency[], int actual_frequency[], int ASCII_values[])
{
	int k = 0;
	int y = 0;
	for (int j = 32; j < 254; j++)   //tách các ký tự xảy ra và không xảy ra & tạo tần số những ký tự xuất hiện 
	{			             
		if (frequency[j] != 0)
		{
			actual_frequency[k] = frequency[j];
			ASCII_values[y] = j;
			y++;
			k++;
			count1++;
		}
	}

	actual_frequency[y] = 1;    //them ki ky de biet file ket thuc
	ASCII_values[k] = 168;
	count1++;
}
//chuyển bit kiểu string -> kiểu int
void Convert_StringBits_to_IntegerBits()
{
	string temp;
	for (int i = 0; i < charactermap.size(); i++)
	{
		temp = charactermap[i].second;
		for (int j = 0; j < temp.size(); j++)          //lưu trữ các chuỗi bit vào vector số nguyên
		{
			if (temp[j] == '1')
			{
				Huffcode.push_back(1);
			}
			else
			{
				Huffcode.push_back(0);
			}
		}
	}
	Huffcode.push_back(-1);
}
//in bảng tần số
void printFrequencyTable(int actual_frequency[], int ASCII_values[])
{
	char ch;
	string str = "";
	str = str + "Space";
	cout << "\n\tBang tan so cua cac ky tu\n\n";
	cout << "\t==================================\n";
	cout << "\t  Ky tu\t\t\tTan so\n";
	cout << "\t==================================\n";
	for (int i = 0; i < count1; i++)
	{
		ch = char(ASCII_values[i]);
		if (ch == ' ')
			cout << "\t    " << str << "\t\t  " << actual_frequency[i] << "\n";
		else
			cout << "\t    " << ch << "\t\t\t  " << actual_frequency[i] << "\n";
	}
}

void Menu()
{
	int frequency[256];
	int ASCII_values[256];
	int actual_frequency[256];
	char filename[50];
	/*cout << "\n\t************************************";
	cout << "\n\t*\t  Winrar Version 2         *\n";
	cout << "\n\t*\t  Press 1:Compress File.   *\n";
	cout << "\n\t*\t  Press 2:Compress Picture.   *\n";
	cout << "\t************************************";*/
	cout << "\n\nNhap FILE can nen |======>  ";
	cin >> filename;
	cout << "\nVui long doi ...";
	clock_t start = clock();
	for (int i = 0; i < 255; i++)     //cài đặt tần số và ký tự đều = 0
	{
		ASCII_values[i] = 0;
		actual_frequency[i] = 0;
		frequency[i] = 0;
	}
	calculate_frequency(frequency, filename);  	//tính tần số các ký tự có trong file

	SeperateCharacter(frequency, actual_frequency, ASCII_values);  //tần số ký tự hiện diện

	//printFrequencyTable(actual_frequency, ASCII_values);  // int bảng tần số
	/*cout << "\n\tBang ky tu Huffman \n";
	cout << "\t==================================\n";
	cout << "\t  Ky tu\t\t\tMa Huffman\n";
	cout << "\t==================================\n";*/

	HuffmanCodes(ASCII_values, actual_frequency, count1);  //xây dựng cây huffman

	Convert_StringBits_to_IntegerBits();          //chuyển đổi chuỗi bit sang int bit

	int len = strlen(filename);
	filename[len - 1] = 'V';
	filename[len - 2] = 'X';
	filename[len - 3] = 'T';
	cout << "\n";
	/*cout << "\nCay Huffman : \n";
	printTree(cout, minHeap.top(), 0);*/
	write_codes(filename);
	ofstream fout;
	fout.open(filename, ios::binary);

	cal_compressionRatio();                //tỉ lệ nén
	int temp1;
	BitWrite s(fout);
	for (int d = 0; d < Huffcode.size(); d++) {
		temp1 = Huffcode[d];
		s.writeBit(temp1);                //ghi các kí tự sau khi chuyển đổi dãy bit -> ki tự ASCII
	}
	cout << endl << "Time to Compress:" << (double)(clock() - start) / CLOCKS_PER_SEC;
	cout << "\nThanh cong !!!";
	int v;
	cout << "\nNhan phim bat ki de thoat : ";
	cin >> v;
}
int CompressPicture()
{
	cout << "Input File Name:";
	string input;
	//const char* inputFileName = "test.bmp";
	cin.ignore();
	getline(cin, input);
	const char* inputFileName = input.c_str();
	JpegEncoder encoder;
	cout << "Please wait :))";
	clock_t start = clock();
	if (!encoder.readFromBMP(inputFileName))
	{
		cout << "Cannot Read InputPicture!!! Please Input Again!!";
	}

	if (!encoder.encodeToJPG("out.jpg", 50))
	{
		cout<<"Cannot CompressPicTure!!";
	}
	

	// do sth here

	cout<<"Time to Compress:"<<(double)(clock() - start) / CLOCKS_PER_SEC;
	return 0;
	
}
int ChooseMenu()
{
	int n = 0;
	cout << "Lua chon cua ban: ";
	cin >> n;
	if (n >= 0 && n < 6)
		return n;
	else return ChooseMenu();
}
int main()
{
	cout << "\n\t************************************";
	cout << "\n\t*\t  Winrar Version 2         *\n";
	cout << "\n\t*\t  Press 1:Compress File.   *\n";
	cout << "\n\t*\t  Press 2:Compress Picture.*\n";
	cout << "\t************************************";
	cout << endl;
	int choose=1;
	while (choose)
	{
		choose = ChooseMenu();
		switch (choose)
		{
		case 0:exit;
	
			break;
		case 1:
			system("cls");
			Menu();
			break;
		case 2:
			system("cls");
			if (CompressPicture() == 0) cout << "Success!" << endl;
			break;
		}
	}
	
	return 0;
}