#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <math.h>

/////////////////////
// ���� ������
/////////////////////
HWND hwnd; // ������ ȭ��(�ܺ�, ������)
HDC hdc; // ������ ȭ��(����, ����)

FILE* rfp, * wfp;
char fileName[200];
int inH = 0, inW = 0, outH = 0, outW = 0, tmpH = 0, tmpW = 0;
// �޸� Ȯ��
unsigned char** inImage = NULL, ** outImage = NULL;
unsigned char** dataImage = NULL, ** tmpImage = NULL;

/////////////////////
// �Լ� �����
/////////////////////
void printMenu(); void loadImage(); void saveImage(); void printImage(); int getIntValue(); double getDoubleValue(); void makeDataImage(); int compare(const unsigned char* a, const unsigned char* b);
void freeInputMemory(); void mallocInputMemory(); void freeOutputMemory(); void mallocOutputMemory(); void freeDataMemory(); void mallocDataMemory();
void freeDoubleMemory(double**, int); double** mallocDoubleMemory(int, int); void freeTmpMemory();  void mallocTmpMemory();
void equalImage(); void addImage(); void subImage(); void mulImage(); void divImage(); void andImage(); void orImage(); void xorImage(); void reverseImage();
void gammaImage(); void parabolaImage(); void histoStretch(); void endIn(); void histoEqual(); void posterizing(); void stressImage(); void morphing();
void bwImage(); void bwAvgImage(); void bwMedImage(); void zoomIn1(); void zoomIn2(); void zoomInBilinear(); void zoomOut(); void zoomOutAvg(); void zoomOutMed();
void mirrorVer(); void mirrorHor(); void rotate(); void rotate2(); void rotateZoomIn(); void rotateZoomInBilinear(); void move();
void emboss(); void blur(); void blur2(); void sharp(); void sharpHf(); void sharpLf(); void gaussian(); 
void edgeVer(); void edgeHor(); void edgeHomogen(); void edgeDiff(); void edgeRoberts(); void edgePrewitt(); void edgeSobel(); void edgeLaplacian(); void edgeLoG(); void edgeDog();

void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL); // Windows 10 : hwnd

	char inKey = 0, inKey2 = 0;

	while (inKey != '9') {
		printMenu();
		inKey = _getch();
		//system("cls");

		switch (inKey) {
		case '0': loadImage(); break;
		case '1': saveImage(); break;
		case '9':break;
		case 'a': case 'A': equalImage(); break;
		case 'b': case 'B':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': addImage(); break;
			case '2': subImage(); break;
			case '3': mulImage(); break;
			case '4': divImage(); break;
			}

			break;
		case 'c': case 'C':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': andImage(); break;
			case '2': orImage(); break;
			case '3': xorImage(); break;
			case '4': reverseImage(); break;
			}

			break;
		case 'd': case 'D': gammaImage(); break;
		case 'e': case 'E': parabolaImage(); break;
		case 'f': case 'F':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': histoStretch(); break;
			case '2': endIn(); break;
			case '3': histoEqual(); break;
			}

			break;
		case 'g': case 'G': posterizing(); break;
		case 'h': case 'H': stressImage(); break;
		case 'i': case 'I': morphing(); break;
			break;
		case 'j': case 'J':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': bwImage(); break;
			case '2': bwAvgImage(); break;
			case '3': bwMedImage(); break;
			}

			break;
		case 'k': case 'K':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': zoomIn1(); break;
			case '2': zoomIn2(); break;
			case '3': zoomInBilinear(); break;
			}

			break;
		case 'l': case 'L':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': zoomOut(); break;
			case '2': zoomOutAvg(); break;
			case '3': zoomOutMed(); break;
			}

			break;
		case 'm': case 'M':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': mirrorVer(); break;
			case '2': mirrorHor(); break;
			}

			break;
		case 'n': case 'N':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': rotate(); break;
			case '2': rotate2(); break;
			case '3': rotateZoomIn(); break;
			case '4': rotateZoomInBilinear(); break;
				break;
			}

			break;
		case 'o': case 'O': move(); break;
		case 'p': case 'P':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': emboss(); break;
			case '2': blur(); break;
			case '3': blur2(); break;
			case '4': sharp(); break;
			case '5': sharpHf(); break;
			case '6': sharpLf(); break;
			case '7': gaussian(); break;
			}

			break;
		case 'q': case 'Q':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': edgeVer(); break;
			case '2': edgeHor(); break;
			case '3': edgeHomogen(); break;
			case '4': edgeDiff(); break;
			}

			break;
		case 'r': case 'R':
			inKey2 = _getch();

			switch (inKey2) {
			case '1': edgeRoberts(); break;
			case '2': edgePrewitt(); break;
			case '3': edgeSobel(); break;
			case '4': edgeLaplacian(); break;
			case '5': edgeLoG(); break;
			case '6': edgeDog(); break;
			}

			break;
		}
	}

	freeInputMemory();
	freeOutputMemory();
	freeDataMemory();
	freeTmpMemory();
}

/////////////////////
// �Լ� ���Ǻ�
/////////////////////
/// ���� �Լ�
//////////////
void printMenu() {
	puts("\n ## GrayScale Image Processing (Version 1.0) ##\n");
	puts("\t     0.���� 1.���� 9.����");
	puts("\n+----------------------------------------------+\n");
	puts("A.����(Null) B1.���(����) B2.��Ӱ�(����) B3.���� B4.������");
	puts("C1.AND C2.OR C3.XOR C4.NOT(����) D.���� E.�Ķ󺼶�");
	puts("F1.������׷� - ��Ʈ��Ī(��� - ��� - ��Ʈ��Ī) F2.endIn F3.��Ȱȭ");
	puts("G.�����Ͷ���¡ H.����(����) I.����");
	puts("J1.��� J2.���(��հ�) J3.���(�߾Ӱ�)\n");
	puts("K1.Ȯ��(������) K2.Ȯ��(�����) K3.Ȯ��(�缱�� ����)");
	puts("L1.��� L2.���(��հ�) L3.���(�߾Ӱ�)");
	puts("M1.�̷���(����) M2.�̷���(�¿�)");
	puts("N1.ȸ��(�⺻) N2.ȸ��(�߾� + �����) N3.ȸ��(Ȯ��) N4.ȸ��(Ȯ�� + �缱��) O.�̵�\n");
	puts("P1.������ P2.����(3x3) P3.����(9x9) P4.������ P5.������(������) P6.������(������) P7.����þ�");
	puts("Q1.��輱(����) Q2.��輱(����) Q3.��輱(����-������) Q4.��輱(��-������)");
	puts("R1.��輱(�ι���) R2.��輱(������) R3.��輱(�Һ�) R4.��輱(���ö�þ�) R5.��輱(LoG) R6.��輱(DoG)\n\n");
}

void loadImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];

	printf("���� �� ���ϸ�-->"); // flower512, LENA256
	scanf("%s", tmpName);

	// fileName �ʱ�ȭ
	memset(fileName, '\0', 200);

	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcat(fileName, fullName);

	// (�߿�!) �̹����� ���� ���̸� ����
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	long long fsize = ftell(rfp); // ��������� 262, 144 --> 512
	fclose(rfp);
	// �޸� ����
	freeInputMemory();
	// ����, �� ���ϱ�
	inH = inW = (int)sqrt(fsize);
	// �޸� �Ҵ�
	mallocInputMemory();

	// ���� --> �޸�
	rfp = fopen(fileName, "rb");

	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);

	fclose(rfp);

	equalImage();
}

void saveImage() {
	if (outH == 0 || outW == 0) {
		system("cls");
		printf(" ** ������ �̹����� �������� ���� **\n\n");
		return;
	}

	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];

	printf("������ ���ϸ�-->"); // out01, out02, ...
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// �޸� -> ���� (�� �྿)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);

	fclose(wfp);
	//MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
	system("cls");
	printf(" [���� �Ϸ�]\n\n");
}

void printImage() {
	if (outH == 0 || outW == 0) {
		system("cls");
		printf(" ** ���� �ִ� �̹����� �������� ���� **\n\n");
		return;
	}

	system("cls");

	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			int px = outImage[i][j];
			SetPixel(hdc, j + 50, i + 250, RGB(px, px, px));
		}
	}
}

int getIntValue() {
	int retValue;
	printf("������-->");
	scanf("%d", &retValue);
	return retValue;
}

double getDoubleValue() {
	double retValue;

	printf("�Ǽ���-->");
	scanf("%lf", &retValue);

	return retValue;
}

void makeDataImage() {
	// �޸� ����
	freeDataMemory();

	// �޸� �Ҵ�
	mallocDataMemory();

	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			dataImage[i][j] = 0;

	int num = 1, size = inH / 4;

	for (int i = inH / 2 - size; i < inH / 2; i++) {
		for (int j = inW / 2 - num; j < inW / 2 + num; j++)
			dataImage[i][j] = 255;

		num++;
	}

	num--;

	for (int i = inH / 2; i < inH / 2 + size; i++) {
		for (int j = inW / 2 - num; j < inW / 2 + num; j++)
			dataImage[i][j] = 255;

		num--;
	}
}

int compare(const unsigned char* a, const unsigned char* b) {
	if (b < a)
		return 1;
	else
		return -1;
}

void freeInputMemory() {
	if (inImage == NULL)
		return;

	for (int i = 0; i < inH; i++)
		free(inImage[i]);

	free(inImage);

	inImage = NULL;
}

void mallocInputMemory() {
	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);

	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
}

void freeOutputMemory() {
	if (outImage == NULL)
		return;

	for (int i = 0; i < outH; i++)
		free(outImage[i]);

	free(outImage);

	outImage = NULL;
}

void mallocOutputMemory() {
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * outH);

	for (int i = 0; i < outH; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);
}

void freeDataMemory() {
	if (dataImage == NULL)
		return;

	for (int i = 0; i < inH; i++)
		free(dataImage[i]);

	free(dataImage);

	dataImage = NULL;
}

void mallocDataMemory() {
	dataImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);

	for (int i = 0; i < inH; i++)
		dataImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
}

void freeDoubleMemory(double** memory, int h) {
	if (memory == NULL)
		return;

	for (int i = 0; i < h; i++)
		free(memory[i]);

	free(memory);

	memory = NULL;
}

double** mallocDoubleMemory(int h, int w) {
	double** retMemory;

	retMemory = (double**)malloc(sizeof(double*) * h);

	for (int i = 0; i < h; i++)
		retMemory[i] = (double*)malloc(sizeof(double) * w);

	return retMemory;
}

void freeTmpMemory() {
	if (tmpImage == NULL)
		return;

	for (int i = 0; i < tmpH; i++)
		free(tmpImage[i]);

	free(tmpImage);

	tmpImage = NULL;
}

void mallocTmpMemory() {
	tmpImage = (unsigned char**)malloc(sizeof(unsigned char*) * tmpH);

	for (int i = 0; i < tmpH; i++)
		tmpImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * tmpW);
}

//////////////////
//  ����ó�� �Լ�
////////////////////
void equalImage() { // ���Ͽ��� �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = inImage[i][j];
		}
	}

	printImage();
}

void addImage() { // ���ϱ� �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	int val = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void subImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	int val = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (0 <= inImage[i][j] - val)
				outImage[i][j] = inImage[i][j] - val;
			else
				outImage[i][j] = 0;
		}
	}

	printImage();
}

void mulImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	int val = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (inImage[i][j] * val < 0)
				outImage[i][j] = 0;
			else if (255 < inImage[i][j] * val)
				outImage[i][j] = 255;
			else
				outImage[i][j] = inImage[i][j] * val;
		}
	}

	printImage();
}

void divImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	int val = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (inImage[i][j] / val < 0)
				outImage[i][j] = 0;
			else if (255 < inImage[i][j] / val)
				outImage[i][j] = 255;
			else
				outImage[i][j] = inImage[i][j] / val;
		}
	}

	printImage();
}

void reverseImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++)
			outImage[i][j] = 255 - inImage[i][j];
	}

	printImage();
}

void bwImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (inImage[i][j] < 128)
				outImage[i][j] = 0;
			else
				outImage[i][j] = 255;
		}
	}

	printImage();
}

void gammaImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	double gamma, x;

	gamma = getDoubleValue();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			x = inImage[i][j];
			outImage[i][j] = 255.0 * pow(x / 255.0, gamma);
		}
	}

	printImage();
}

void parabolaImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	double x;
	// cap
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			x = inImage[i][j];
			outImage[i][j] = -255.0 * pow(x / 127.0 - 1.0, 2) + 255.0;
		}
	}

	printImage();

	//cup
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			x = inImage[i][j];
			outImage[i][j] = 255.0 * pow(x / 127.0 - 1.0, 2);
		}
	}

	printImage();
}

void bwAvgImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	int avg = 0;

	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			avg += inImage[i][j];

	avg /= inH * inW;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (inImage[i][j] < avg)
				outImage[i][j] = 0;
			else
				outImage[i][j] = 255;
		}
	}

	printImage();
}

void bwMedImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	int med, cnt = 0;
	unsigned char* arr = (unsigned char*)malloc(sizeof(unsigned char) * inH * inW); //arr[height * width];

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			arr[cnt] = inImage[i][j];
			cnt++;
		}
	}

	qsort(arr, cnt, sizeof(unsigned char), compare);

	med = arr[inH * inW / 2];

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (inImage[i][j] < med)
				outImage[i][j] = 0;
			else
				outImage[i][j] = 255;
		}
	}

	free(arr);

	printImage();
}

void andImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	makeDataImage();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if ((inImage[i][j] & dataImage[i][j]) < 0)
				outImage[i][j] = 0;
			else if (255 < (inImage[i][j] & dataImage[i][j]))
				outImage[i][j] = 255;
			else
				outImage[i][j] = inImage[i][j] & dataImage[i][j];
		}
	}

	printImage();
}

void orImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	makeDataImage();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if ((inImage[i][j] | dataImage[i][j]) < 0)
				outImage[i][j] = 0;
			else if (255 < (inImage[i][j] | dataImage[i][j]))
				outImage[i][j] = 255;
			else
				outImage[i][j] = inImage[i][j] | dataImage[i][j];
		}
	}

	printImage();
}

void xorImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	makeDataImage();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if ((inImage[i][j] ^ dataImage[i][j]) < 0)
				outImage[i][j] = 0;
			else if (255 < (inImage[i][j] ^ dataImage[i][j]))
				outImage[i][j] = 255;
			else
				outImage[i][j] = inImage[i][j] ^ dataImage[i][j];
		}
	}

	printImage();
}

void stressImage() {
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	printf("���� ���� ");
	int val1 = getIntValue();

	printf("������ ���� ");
	int val2 = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (val1 <= inImage[i][j] && inImage[i][j] <= val2)
				outImage[i][j] = 255;
			else
				outImage[i][j] = inImage[i][j];
		}
	}

	printImage();
}

void morphing() { // ���� �˰���
	// �޸� ����
	freeOutputMemory();
	freeTmpMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = tmpH = inH;
	outW = tmpW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();
	mallocTmpMemory();

	// �ٸ� �̹��� �ҷ����� (���� �̹����� ũ�⿡ ���� �ڸ�
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];

	printf("������ �ٸ� ���ϸ�-->"); // flower512, LENA256
	scanf("%s", tmpName);

	// fileName �ʱ�ȭ
	memset(fileName, '\0', 200);

	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcat(fileName, fullName);

	// (�߿�!) �̹����� ���� ���̸� ����
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	fclose(rfp);

	// ���� --> �޸�
	rfp = fopen(fileName, "rb");

	for (int i = 0; i < tmpH; i++)
		fread(tmpImage[i], sizeof(unsigned char), tmpW, rfp);

	fclose(rfp);
	/////////////////////////////////

	// �Է� �迭 --> ��� �迭
	int tmp;
	double u;
	
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			u = ((i * inH) + (j + 1.0)) / (inH * inW);
			tmp = (int)((1.0 - u) * inImage[i][j] + u * tmpImage[i][j]);
			
			if (255 < tmp)
				outImage[i][j] = 255;
			else if (tmp < 0)
				outImage[i][j] = 0;
			else
				outImage[i][j] = (unsigned char) tmp;
		}
	}

	printImage();
}

void zoomOut() { // ��� �˰��� + ������
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH / scale;
	outW = inW / scale;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++)
			outImage[(int)(i / scale)][(int)(j / scale)] = inImage[i][j];
	}

	printImage();
}

void zoomIn1() { // Ȯ�� �˰��� + ������
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH * scale;
	outW = inW * scale;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++)
			outImage[(int)(i * scale)][(int)(j * scale)] = inImage[i][j];
	}

	printImage();
}

void zoomIn2() { // Ȯ�� �˰��� + �����
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH * scale;
	outW = inW * scale;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++)
			outImage[i][j] = inImage[(int)(i / scale)][(int)(j / scale)];
	}

	printImage();
}

void rotate() { // ȸ�� �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			outImage[i][j] = 0;

	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			int xs = i;
			int ys = j;

			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}

	printImage();
}

void rotate2() { // ȸ�� �˰��� + �߾�/�����
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			outImage[i][j] = 0;

	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	int cx = inH / 2;
	int cy = inW / 2;

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			int xd = i;
			int yd = j;

			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));

			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < outH) && (0 <= ys && ys <= outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}

	printImage();
}

void rotateZoomIn() { // ȸ��(Ȯ��) �˰���
	printf("Ȯ�� ���� ");
	int scale = getIntValue();

	printf("ȸ�� ���� ");
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// �޸� ����
	freeOutputMemory();
	freeTmpMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = tmpH = inH * scale;
	outW = tmpW = inW * scale;

	// �޸� �Ҵ�
	mallocOutputMemory();
	mallocTmpMemory();

	// Ȯ��
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++)
			tmpImage[i][j] = inImage[(int)(i / scale)][(int)(j / scale)];
	}

	// ȸ��
	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			outImage[i][j] = 0;

	int cx = tmpH / 2;
	int cy = tmpW / 2;

	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			int xd = i;
			int yd = j;

			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));

			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < outH) && (0 <= ys && ys <= outW))
				outImage[xd][yd] = tmpImage[xs][ys];
		}
	}

	printImage();
}

void rotateZoomInBilinear() { // ȸ�� �˰��� + Ȯ��/�缱��
	printf("Ȯ�� ���� ");
	int scale = getIntValue();

	printf("ȸ�� ���� ");
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// �޸� ����
	freeOutputMemory();
	freeTmpMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = tmpH = inH * scale;
	outW = tmpW = inW * scale;

	// �޸� �Ҵ�
	mallocOutputMemory();
	mallocTmpMemory();

	// Ȯ��(�缱�� ����)
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			double rH = (double)i / scale;
			double rW = (double)j / scale;

			int iH = (int)floor(rH);
			int iW = (int)floor(rW);

			double sH = rH - iH;
			double sW = rW - iW;

			if (iH < 0 || inH - 1 <= iH || iW < 0 || inW - 1 <= iW)
				tmpImage[i][j] = 255;
			else {
				double C1 = (double)inImage[iH][iW];
				double C2 = (double)inImage[iH][iW + 1];
				double C3 = (double)inImage[iH + 1][iW + 1];
				double C4 = (double)inImage[iH + 1][iW];

				tmpImage[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);
			}
		}
	}

	// ȸ��
	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			outImage[i][j] = 0;

	int cx = tmpH / 2;
	int cy = tmpW / 2;

	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			int xd = i;
			int yd = j;

			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));

			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < outH) && (0 <= ys && ys <= outW))
				outImage[xd][yd] = tmpImage[xs][ys];
		}
	}

	printImage();
}

void move() { // �̵� �˰���
	printf("�̵��� Height ");
	int posH = getIntValue();
	printf("�̵��� Width ");
	int posW = getIntValue();

	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			outImage[i][j] = 0;

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH - posH; i++) {
		for (int j = 0; j < inW - posW; j++) {
			int nx = i + posH;
			int ny = j + posW;

			if ((0 <= nx && nx < outH) && (0 <= ny && ny < outW))
				outImage[nx][ny] = inImage[i][j];
		}
	}

	printImage();
}

void mirrorVer() { // ���� �̷���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = inImage[inH - 1 - i][j];
		}
	}

	printImage();
}

void mirrorHor() { // �¿� �̷���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = inImage[i][inH - 1 - j];
		}
	}

	printImage();
}

void zoomOutAvg() { // ��� �˰��� + ��հ�
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH / scale;
	outW = inW / scale;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i += scale) {
		for (int j = 0; j < inW; j += scale) {
			long long avg = 0;

			for (int n = 0; n < scale; n++)
				for (int m = 0; m < scale; m++)
					avg += inImage[i + n][j + m];

			outImage[(int)(i / scale)][(int)(j / scale)] = avg / (scale * scale);
		}
	}

	printImage();
}

void zoomOutMed() { // ��� �˰��� + �߾Ӱ�
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH / scale;
	outW = inW / scale;

	// �޸� �Ҵ�
	mallocOutputMemory();

	unsigned char* arr = (unsigned char*)malloc(sizeof(unsigned char) * scale * scale);

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i += scale) {
		for (int j = 0; j < inW; j += scale) {
			int med, cnt = 0;

			for (int n = 0; n < scale; n++) {
				for (int m = 0; m < scale; m++) {
					arr[cnt] = inImage[i + n][j + m];
					cnt++;
				}
			}

			qsort(arr, cnt, sizeof(unsigned char), compare);
			med = arr[scale * scale / 2];
			outImage[(int)(i / scale)][(int)(j / scale)] = med;
		}
	}

	free(arr);

	printImage();
}

void zoomInBilinear() { // Ȯ�� �˰��� + �缱�� ����
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH * scale;
	outW = inW * scale;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			double rH = (double)i / scale;
			double rW = (double)j / scale;

			int iH = (int)floor(rH);
			int iW = (int)floor(rW);

			double sH = rH - iH;
			double sW = rW - iW;

			if (iH < 0 || inH - 1 <= iH || iW < 0 || inW - 1 <= iW)
				outImage[i][j] = 255;
			else {
				double C1 = (double)inImage[iH][iW];
				double C2 = (double)inImage[iH][iW + 1];
				double C3 = (double)inImage[iH + 1][iW + 1];
				double C4 = (double)inImage[iH + 1][iW];

				outImage[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);
			}
		}
	}

	printImage();
}

void histoStretch() { // ������׷� ��Ʈ��Ī �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	// new = (old - low) / (high - low) * 255.0
	int high = inImage[0][0], low = inImage[0][0];

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (inImage[i][j] < low)
				low = inImage[i][j];

			if (high < inImage[i][j])
				high = inImage[i][j];
		}
	}

	int old, new;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			old = inImage[i][j];
			new = (int)((double)(old - low) / (double)(high - low) * 255.0);

			if (new < 0)
				new = 0;

			if (255 < new)
				new = 255;

			outImage[i][j] = new;
		}
	}

	printImage();
}

void endIn() { // �ص� �� Ž�� �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	int high = inImage[0][0], low = inImage[0][0];

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (inImage[i][j] < low)
				low = inImage[i][j];
			if (inImage[i][j] > high)
				high = inImage[i][j];
		}
	}

	high -= 50;
	low += 50;

	int old, new;
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			old = inImage[i][j];

			new = (int)((double)(old - low) / (double)(high - low) * 255.0);

			if (new > 255)
				new = 255;

			if (new < 0)
				new = 0;

			outImage[i][j] = new;
		}
	}
	printImage();

}

void histoEqual() { // ������׷� ��Ȱȭ �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// 1�ܰ� : �� �� ���� (=������׷�) histo[256]
	int histo[256] = { 0 };

	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			histo[inImage[i][j]]++;

	// 2�ܰ� : ���� ������׷� ����
	int sumHisto[256] = { 0 };
	sumHisto[0] = histo[0];

	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];

	// 3�ܰ� : ����ȭ�� ������׷� ���� normalHisto = sumHisto * (1.0 / (inH * inW)) * 255.0
	double normalHisto[256] = { 0 };

	for (int i = 0; i < 256; i++)
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = (unsigned char)normalHisto[inImage[i][j]];
		}
	}

	printImage();
}

void posterizing() { // �����Ͷ���¡ �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	int bit = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			for (int k = 1; k < bit; k++) { // input ���� : bit - 1��, output ���� : bit - 2��
				if (k == (bit - 1)) // ������ ����
					outImage[i][j] = 255;
				else if (inImage[i][j] <= 255 / (bit - 1) * k) {
					if (k == 1) // ù ��° ����
						outImage[i][j] = 0;
					else // ������ ����
						outImage[i][j] = 255 / (bit - 2) * (k - 1);

					break;
				}
			}
		}
	}

	printImage();
}

void emboss() { // ȭ�� ���� ó�� : ������ �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[3][3] = { { -1.0, 0.0, 0.0}, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } }; // ������ ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// ��ó�� (����ũ ���� �հ迡 ����)
	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			tmpOutImage[i][j] += 127.0;

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void blur() { // ȭ�� ���� ó�� : ���� �˰���(3x3)
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[3][3] = { { 1.0 / 9, 1.0 / 9, 1.0 / 9 }, 
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 }, 
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 } }; // ���� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void blur2() { // ȭ�� ���� ó�� : ���� �˰���(9x9)
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[9][9]; // ���� ����ũ

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			mask[i][j] = 1.0 / 81;

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 8, inW + 8);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 8; i++)
		for (int j = 0; j < inW + 8; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 4][j + 4] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 9x9 ���ϱ�
			S = 0.0; // ����ũ 81���� �Է°� 81���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 9; m++)
				for (int n = 0; n < 9; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 8);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();

}

void sharp() { // ȭ�� ���� ó�� : ������ �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[3][3] = { { 0.0, -1.0, 0.0 },
		{ -1.0, 5.0, -1.0 },
		{ 0.0, -1.0, 0.0 } }; // ������ ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void sharpHf() { // ȭ�� ���� ó�� : ������ ������ �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[3][3] = { { -1.0 / 9, -1.0 / 9, -1.0 / 9 },
		{ -1.0 / 9, 8.0 / 9, -1.0 / 9 }, 
		{ -1.0 / 9, -1.0 / 9, -1.0 / 9 } }; // ������ ������ ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n] * 20;

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void sharpLf() {
	// ȭ�� ���� ó�� : ������ ������ �˰���
   // �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	int alpha = getIntValue();

	double mask[3][3] = { { 1.0 / 9, 1.0 / 9, 1.0 / 9 }, 
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 }, 
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 } }; // ������ ������ ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	double unsharp;

	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			unsharp = alpha * inImage[i][j] - tmpOutImage[i][j];

			if (unsharp < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < unsharp)
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)unsharp;
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void gaussian() { // ȭ�� ���� ó�� : ����þ� �˰���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[3][3] = { { 1.0 / 16, 1.0 / 8, 1.0 / 16 }, 
		{ 1.0 / 8, 1.0 / 4, 1.0 / 8 }, 
		{ 1.0 / 16, 1.0 / 8, 1.0 / 16 } }; // ����þ� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edgeVer() { // ��輱 �˰��� + ����
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[3][3] = { { 0.0, 0.0, 0.0 }, 
		{ -1.0, 1.0, 0.0 }, 
		{ 0.0, 0.0, 0.0 } }; // ���� ���� ���� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edgeHor() { // ��輱 �˰��� + ����
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[3][3] = { { 0.0, -1.0, 0.0 }, 
		{ 0.0, 1.0, 0.0 }, 
		{ 0.0, 0.0, 0.0 } }; // ���� ���� ���� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edgeHomogen() { // ��輱 �˰��� + ���� ������
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			S = 0,0;

			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					if (S < fabs(tmpInImage[i + 1][j + 1] - tmpInImage[i + m][j + n]))
						S = fabs(tmpInImage[i + 1][j + 1] - tmpInImage[i + m][j + n]);
				}
			}

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edgeDiff() { // ��輱 �˰��� + �� ������
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			S = 0, 0;

			for (int n = 0; n < 3; n++) {
				if (S < fabs(tmpInImage[i][j + n] - tmpInImage[i + 2][j + - n + 2]))
					S = fabs(tmpInImage[i][j + n] - tmpInImage[i + 2][j + - n + 2]);
			}

			if (S < fabs(tmpInImage[i + 1][j + 2] - tmpInImage[i + 1][j]))
				S = fabs(tmpInImage[i + 1][j + 2] - tmpInImage[i + 1][j]);

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edgeRoberts() { // ��輱 1�� �̺� �˰��� + �ι���
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double maskRow[3][3] = { { -1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 }, 
		{ 0.0, 0.0, 0.0 } }; // �ι��� �� ���� ���� ����ũ
	double maskCol[3][3] = { { 0.0, 0.0, -1.0 }, 
		{ 0.0, 1.0, 0.0 }, 
		{ 0.0, 0.0, 0.0 } }; // �ι��� �� ���� ���� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpRowInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpColInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpRowOutImage = mallocDoubleMemory(outH, outW);
	double** tmpColOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpRowInImage[i][j] = tmpColInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S1, S2;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S1 = S2 = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S1 += tmpRowInImage[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImage[i + m][j + n] * maskCol[m][n];
				}
			}

			tmpRowOutImage[i][j] = S1;
			tmpColOutImage[i][j] = S2;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			S1 = tmpRowOutImage[i][j];
			S2 = tmpColOutImage[i][j];

			if (sqrt((double) (S1 * S1 + S2 * S2)) < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));
		}
	}

	freeDoubleMemory(tmpRowInImage, inH + 2);
	freeDoubleMemory(tmpColInImage, inH + 2);
	freeDoubleMemory(tmpRowOutImage, outH);
	freeDoubleMemory(tmpColOutImage, outH);

	printImage();
}

void edgePrewitt() { // ��輱 1�� �̺� �˰��� + ������
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double maskRow[3][3] = { { -1.0, -1.0, -1.0 }, 
		{ 0.0, 0.0, 0.0 }, 
		{ 1.0, 1.0, 1.0 } }; // ������ �� ���� ���� ����ũ
	double maskCol[3][3] = { { 1.0, 0.0, -1.0 }, 
		{ 1.0, 0.0, -1.0 }, 
		{ 1.0, 0.0, -1.0 } }; // ������ �� ���� ���� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpRowInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpColInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpRowOutImage = mallocDoubleMemory(outH, outW);
	double** tmpColOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpRowInImage[i][j] = tmpColInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S1, S2;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S1 = S2 = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S1 += tmpRowInImage[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImage[i + m][j + n] * maskCol[m][n];
				}
			}

			tmpRowOutImage[i][j] = S1;
			tmpColOutImage[i][j] = S2;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			S1 = tmpRowOutImage[i][j];
			S2 = tmpColOutImage[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));
		}
	}

	freeDoubleMemory(tmpRowInImage, inH + 2);
	freeDoubleMemory(tmpColInImage, inH + 2);
	freeDoubleMemory(tmpRowOutImage, outH);
	freeDoubleMemory(tmpColOutImage, outH);

	printImage();
}

void edgeSobel() { // ��輱 1�� �̺� �˰��� + �Һ�
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double maskRow[3][3] = { { -1.0, -2.0, -1.0 }, 
		{ 0.0, 0.0, 0.0 }, 
		{ 1.0, 2.0, 1.0 } }; // �Һ� �� ���� ���� ����ũ
	double maskCol[3][3] = { { 1.0, 0.0, -1.0 }, 
		{ 2.0, 0.0, -2.0 }, 
		{ 1.0, 0.0, -1.0 } }; // �Һ� �� ���� ���� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpRowInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpColInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpRowOutImage = mallocDoubleMemory(outH, outW);
	double** tmpColOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpRowInImage[i][j] = tmpColInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S1, S2;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S1 = S2 = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S1 += tmpRowInImage[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImage[i + m][j + n] * maskCol[m][n];
				}
			}

			tmpRowOutImage[i][j] = S1;
			tmpColOutImage[i][j] = S2;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			S1 = tmpRowOutImage[i][j];
			S2 = tmpColOutImage[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));
		}
	}

	freeDoubleMemory(tmpRowInImage, inH + 2);
	freeDoubleMemory(tmpColInImage, inH + 2);
	freeDoubleMemory(tmpRowOutImage, outH);
	freeDoubleMemory(tmpColOutImage, outH);

	printImage();
}

void edgeLaplacian() { // ��輱 2�� �̺� �˰��� + ���ö�þ�
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[3][3] = { { 0.0, -1.0, 0.0 }, 
		{ -1.0, 4.0, -1.0 }, 
		{ 0.0, -1.0, 0.0 } }; // ���ö�þ� ���� ���� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 3x3 ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edgeLoG() { // ��輱 2�� �̺� �˰��� + LoG
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[5][5] = { { 0.0, 0.0, -1.0, 0.0, 0.0 }, 
		{ 0.0, -1.0, -2.0, -1.0, 0.0 },
		{ -1.0, -2.0, 16.0, -2.0, -1.0 }, 
		{ 0.0, -1.0, -2.0, -1.0, 0.0 }, 
		{ 0.0, 0.0, -1.0, 0.0, 0.0 } }; // LoG ���� ���� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 4, inW + 4);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 4; i++)
		for (int j = 0; j < inW + 4; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 2][j + 2] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 5x5 ���ϱ�
			S = 0.0; // ����ũ 25���� �Է°� 25���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 4);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edgeDog() {  // ��輱 2�� �̺� �˰��� + DoG
	// �޸� ����
	freeOutputMemory();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� --> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�
	mallocOutputMemory();

	//////////////////
	// ȭ�� ���� ó��
	//////////////////

	double mask[7][7] = { { 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0 }, 
		{ 0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0 }, 
		{ -1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0 },
		{ -1.0, -3.0, 5.0, 16.0, 5.0, -3.0, -1.0 }, 
		{ -1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0 }, 
		{ 0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0 }, 
		{ 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0 } }; // DoG ���� ���� ����ũ

	// �ӽ� �޸� �Ҵ� (�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 6, inW + 6);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 6; i++)
		for (int j = 0; j < inW + 6; j++)
			tmpInImage[i][j] = 127;

	// �Է� �̹��� -> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 3][j + 3] = inImage[i][j];

	// ** ȸ�� ����
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// ����ũ(3x3)�� �� ���� �߽����� �� 5x5 ���ϱ�
			S = 0.0; // ����ũ 25���� �Է°� 25���� ���� ���ؼ� ���� ��

			for (int m = 0; m < 7; m++)
				for (int n = 0; n < 7; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// �ӽ� ��� ���� --> ��� ����
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				outImage[i][j] = 0;
			else if (255.0 < tmpOutImage[i][j])
				outImage[i][j] = 255;
			else
				outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	freeDoubleMemory(tmpInImage, inH + 6);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}