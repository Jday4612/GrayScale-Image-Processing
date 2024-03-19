#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <math.h>

/////////////////////
// 전역 변수부
/////////////////////
HWND hwnd; // 윈도우 화면(외부, 물리적)
HDC hdc; // 윈도우 화면(내부, 논리적)

FILE* rfp, * wfp;
char fileName[200];
int inH = 0, inW = 0, outH = 0, outW = 0, tmpH = 0, tmpW = 0;
// 메모리 확보
unsigned char** inImage = NULL, ** outImage = NULL;
unsigned char** dataImage = NULL, ** tmpImage = NULL;

/////////////////////
// 함수 선언부
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
// 함수 정의부
/////////////////////
/// 공통 함수
//////////////
void printMenu() {
	puts("\n ## GrayScale Image Processing (Version 1.0) ##\n");
	puts("\t     0.열기 1.저장 9.종료");
	puts("\n+----------------------------------------------+\n");
	puts("A.동일(Null) B1.밝게(덧셈) B2.어둡게(뺄셈) B3.곱셈 B4.나눗셈");
	puts("C1.AND C2.OR C3.XOR C4.NOT(반전) D.감마 E.파라볼라");
	puts("F1.히스토그램 - 스트레칭(명암 - 대비 - 스트레칭) F2.endIn F3.펑활화");
	puts("G.포스터라이징 H.강조(이진) I.모핑");
	puts("J1.흑백 J2.흑백(평균값) J3.흑백(중앙값)\n");
	puts("K1.확대(포워딩) K2.확대(백워딩) K3.확대(양선형 보간)");
	puts("L1.축소 L2.축소(평균값) L3.축소(중앙값)");
	puts("M1.미러링(상하) M2.미러링(좌우)");
	puts("N1.회전(기본) N2.회전(중앙 + 백워딩) N3.회전(확대) N4.회전(확대 + 양선형) O.이동\n");
	puts("P1.엠보싱 P2.블러링(3x3) P3.블러링(9x9) P4.샤프닝 P5.샤프닝(고주파) P6.샤프닝(저주파) P7.가우시안");
	puts("Q1.경계선(수직) Q2.경계선(수평) Q3.경계선(유사-연산자) Q4.경계선(차-연산자)");
	puts("R1.경계선(로버츠) R2.경계선(프리윗) R3.경계선(소벨) R4.경계선(라플라시안) R5.경계선(LoG) R6.경계선(DoG)\n\n");
}

void loadImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];

	printf("열어 볼 파일명-->"); // flower512, LENA256
	scanf("%s", tmpName);

	// fileName 초기화
	memset(fileName, '\0', 200);

	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcat(fileName, fullName);

	// (중요!) 이미지의 폭과 높이를 결정
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
	long long fsize = ftell(rfp); // 어디쯤인지 262, 144 --> 512
	fclose(rfp);
	// 메모리 해제
	freeInputMemory();
	// 높이, 폭 구하기
	inH = inW = (int)sqrt(fsize);
	// 메모리 할당
	mallocInputMemory();

	// 파일 --> 메모리
	rfp = fopen(fileName, "rb");

	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);

	fclose(rfp);

	equalImage();
}

void saveImage() {
	if (outH == 0 || outW == 0) {
		system("cls");
		printf(" ** 저장할 이미지가 존재하지 않음 **\n\n");
		return;
	}

	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];

	printf("저장할 파일명-->"); // out01, out02, ...
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// 메모리 -> 파일 (한 행씩)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);

	fclose(wfp);
	//MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
	system("cls");
	printf(" [저장 완료]\n\n");
}

void printImage() {
	if (outH == 0 || outW == 0) {
		system("cls");
		printf(" ** 열려 있는 이미지가 존재하지 않음 **\n\n");
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
	printf("정수값-->");
	scanf("%d", &retValue);
	return retValue;
}

double getDoubleValue() {
	double retValue;

	printf("실수값-->");
	scanf("%lf", &retValue);

	return retValue;
}

void makeDataImage() {
	// 메모리 해제
	freeDataMemory();

	// 메모리 할당
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
//  영상처리 함수
////////////////////
void equalImage() { // 동일영상 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = inImage[i][j];
		}
	}

	printImage();
}

void addImage() { // 더하기 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++)
			outImage[i][j] = 255 - inImage[i][j];
	}

	printImage();
}

void bwImage() {
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
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
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	printf("시작 구간 ");
	int val1 = getIntValue();

	printf("마지막 구간 ");
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

void morphing() { // 모핑 알고리즘
	// 메모리 해제
	freeOutputMemory();
	freeTmpMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = tmpH = inH;
	outW = tmpW = inW;

	// 메모리 할당
	mallocOutputMemory();
	mallocTmpMemory();

	// 다른 이미지 불러오기 (기존 이미지의 크기에 맞춰 자름
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];

	printf("모핑할 다른 파일명-->"); // flower512, LENA256
	scanf("%s", tmpName);

	// fileName 초기화
	memset(fileName, '\0', 200);

	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcat(fileName, fullName);

	// (중요!) 이미지의 폭과 높이를 결정
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
	fclose(rfp);

	// 파일 --> 메모리
	rfp = fopen(fileName, "rb");

	for (int i = 0; i < tmpH; i++)
		fread(tmpImage[i], sizeof(unsigned char), tmpW, rfp);

	fclose(rfp);
	/////////////////////////////////

	// 입력 배열 --> 출력 배열
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

void zoomOut() { // 축소 알고리즘 + 포워딩
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH / scale;
	outW = inW / scale;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++)
			outImage[(int)(i / scale)][(int)(j / scale)] = inImage[i][j];
	}

	printImage();
}

void zoomIn1() { // 확대 알고리즘 + 포워딩
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH * scale;
	outW = inW * scale;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++)
			outImage[(int)(i * scale)][(int)(j * scale)] = inImage[i][j];
	}

	printImage();
}

void zoomIn2() { // 확대 알고리즘 + 백워딩
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH * scale;
	outW = inW * scale;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++)
			outImage[i][j] = inImage[(int)(i / scale)][(int)(j / scale)];
	}

	printImage();
}

void rotate() { // 회전 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			outImage[i][j] = 0;

	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// 입력 배열 --> 출력 배열
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

void rotate2() { // 회전 알고리즘 + 중앙/백워딩
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			outImage[i][j] = 0;

	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	int cx = inH / 2;
	int cy = inW / 2;

	// 입력 배열 --> 출력 배열
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

void rotateZoomIn() { // 회전(확대) 알고리즘
	printf("확대 정도 ");
	int scale = getIntValue();

	printf("회전 각도 ");
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// 메모리 해제
	freeOutputMemory();
	freeTmpMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = tmpH = inH * scale;
	outW = tmpW = inW * scale;

	// 메모리 할당
	mallocOutputMemory();
	mallocTmpMemory();

	// 확대
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++)
			tmpImage[i][j] = inImage[(int)(i / scale)][(int)(j / scale)];
	}

	// 회전
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

void rotateZoomInBilinear() { // 회전 알고리즘 + 확대/양선형
	printf("확대 정도 ");
	int scale = getIntValue();

	printf("회전 각도 ");
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;

	// 메모리 해제
	freeOutputMemory();
	freeTmpMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = tmpH = inH * scale;
	outW = tmpW = inW * scale;

	// 메모리 할당
	mallocOutputMemory();
	mallocTmpMemory();

	// 확대(양선형 보간)
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

	// 회전
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

void move() { // 이동 알고리즘
	printf("이동할 Height ");
	int posH = getIntValue();
	printf("이동할 Width ");
	int posW = getIntValue();

	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			outImage[i][j] = 0;

	// 입력 배열 --> 출력 배열
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

void mirrorVer() { // 상하 미러링
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = inImage[inH - 1 - i][j];
		}
	}

	printImage();
}

void mirrorHor() { // 좌우 미러링
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = inImage[i][inH - 1 - j];
		}
	}

	printImage();
}

void zoomOutAvg() { // 축소 알고리즘 + 평균값
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH / scale;
	outW = inW / scale;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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

void zoomOutMed() { // 축소 알고리즘 + 중앙값
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH / scale;
	outW = inW / scale;

	// 메모리 할당
	mallocOutputMemory();

	unsigned char* arr = (unsigned char*)malloc(sizeof(unsigned char) * scale * scale);

	// 입력 배열 --> 출력 배열
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

void zoomInBilinear() { // 확대 알고리즘 + 양선형 보간
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH * scale;
	outW = inW * scale;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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

void histoStretch() { // 히스토그램 스트레칭 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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

void endIn() { // 앤드 인 탐색 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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

void histoEqual() { // 히스토그램 평활화 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 1단계 : 빈도 수 세기 (=히스토그램) histo[256]
	int histo[256] = { 0 };

	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			histo[inImage[i][j]]++;

	// 2단계 : 누적 히스토그램 생성
	int sumHisto[256] = { 0 };
	sumHisto[0] = histo[0];

	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];

	// 3단계 : 정규화된 히스토그램 생성 normalHisto = sumHisto * (1.0 / (inH * inW)) * 255.0
	double normalHisto[256] = { 0 };

	for (int i = 0; i < 256; i++)
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = (unsigned char)normalHisto[inImage[i][j]];
		}
	}

	printImage();
}

void posterizing() { // 포스터라이징 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	int bit = getIntValue();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			for (int k = 1; k < bit; k++) { // input 간격 : bit - 1개, output 간격 : bit - 2개
				if (k == (bit - 1)) // 마지막 구간
					outImage[i][j] = 255;
				else if (inImage[i][j] <= 255 / (bit - 1) * k) {
					if (k == 1) // 첫 번째 구간
						outImage[i][j] = 0;
					else // 나머지 구간
						outImage[i][j] = 255 / (bit - 2) * (k - 1);

					break;
				}
			}
		}
	}

	printImage();
}

void emboss() { // 화소 영역 처리 : 엠보싱 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[3][3] = { { -1.0, 0.0, 0.0}, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } }; // 엠보싱 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 후처리 (마스크 값의 합계에 따라서)
	for (int i = 0; i < outH; i++)
		for (int j = 0; j < outW; j++)
			tmpOutImage[i][j] += 127.0;

	// 임시 출력 영상 --> 출력 영상
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

void blur() { // 화소 영역 처리 : 블러링 알고리즘(3x3)
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[3][3] = { { 1.0 / 9, 1.0 / 9, 1.0 / 9 }, 
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 }, 
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 } }; // 블러링 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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

void blur2() { // 화소 영역 처리 : 블러링 알고리즘(9x9)
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[9][9]; // 블러링 마스크

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			mask[i][j] = 1.0 / 81;

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 8, inW + 8);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 8; i++)
		for (int j = 0; j < inW + 8; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 4][j + 4] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 9x9 곱하기
			S = 0.0; // 마스크 81개와 입력값 81개를 각각 곱해서 합한 값

			for (int m = 0; m < 9; m++)
				for (int n = 0; n < 9; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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

void sharp() { // 화소 영역 처리 : 샤프닝 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[3][3] = { { 0.0, -1.0, 0.0 },
		{ -1.0, 5.0, -1.0 },
		{ 0.0, -1.0, 0.0 } }; // 샤프닝 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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

void sharpHf() { // 화소 영역 처리 : 고주파 샤프닝 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[3][3] = { { -1.0 / 9, -1.0 / 9, -1.0 / 9 },
		{ -1.0 / 9, 8.0 / 9, -1.0 / 9 }, 
		{ -1.0 / 9, -1.0 / 9, -1.0 / 9 } }; // 고주파 샤프닝 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n] * 20;

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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
	// 화소 영역 처리 : 저주파 샤프닝 알고리즘
   // 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	int alpha = getIntValue();

	double mask[3][3] = { { 1.0 / 9, 1.0 / 9, 1.0 / 9 }, 
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 }, 
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 } }; // 저주파 샤프닝 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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

void gaussian() { // 화소 영역 처리 : 가우시안 알고리즘
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[3][3] = { { 1.0 / 16, 1.0 / 8, 1.0 / 16 }, 
		{ 1.0 / 8, 1.0 / 4, 1.0 / 8 }, 
		{ 1.0 / 16, 1.0 / 8, 1.0 / 16 } }; // 가우시안 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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

void edgeVer() { // 경계선 알고리즘 + 수직
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[3][3] = { { 0.0, 0.0, 0.0 }, 
		{ -1.0, 1.0, 0.0 }, 
		{ 0.0, 0.0, 0.0 } }; // 수직 에지 검출 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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

void edgeHor() { // 경계선 알고리즘 + 수평
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[3][3] = { { 0.0, -1.0, 0.0 }, 
		{ 0.0, 1.0, 0.0 }, 
		{ 0.0, 0.0, 0.0 } }; // 수평 에지 검출 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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

void edgeHomogen() { // 경계선 알고리즘 + 유사 연산자
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
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

	// 임시 출력 영상 --> 출력 영상
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

void edgeDiff() { // 경계선 알고리즘 + 차 연산자
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
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

	// 임시 출력 영상 --> 출력 영상
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

void edgeRoberts() { // 경계선 1차 미분 알고리즘 + 로버츠
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double maskRow[3][3] = { { -1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 }, 
		{ 0.0, 0.0, 0.0 } }; // 로버츠 행 에지 검출 마스크
	double maskCol[3][3] = { { 0.0, 0.0, -1.0 }, 
		{ 0.0, 1.0, 0.0 }, 
		{ 0.0, 0.0, 0.0 } }; // 로버츠 열 에지 검출 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpRowInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpColInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpRowOutImage = mallocDoubleMemory(outH, outW);
	double** tmpColOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpRowInImage[i][j] = tmpColInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S1, S2;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

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

	// 임시 출력 영상 --> 출력 영상
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

void edgePrewitt() { // 경계선 1차 미분 알고리즘 + 프리윗
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double maskRow[3][3] = { { -1.0, -1.0, -1.0 }, 
		{ 0.0, 0.0, 0.0 }, 
		{ 1.0, 1.0, 1.0 } }; // 프리윗 행 에지 검출 마스크
	double maskCol[3][3] = { { 1.0, 0.0, -1.0 }, 
		{ 1.0, 0.0, -1.0 }, 
		{ 1.0, 0.0, -1.0 } }; // 프리윗 열 에지 검출 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpRowInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpColInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpRowOutImage = mallocDoubleMemory(outH, outW);
	double** tmpColOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpRowInImage[i][j] = tmpColInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S1, S2;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

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

	// 임시 출력 영상 --> 출력 영상
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

void edgeSobel() { // 경계선 1차 미분 알고리즘 + 소벨
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double maskRow[3][3] = { { -1.0, -2.0, -1.0 }, 
		{ 0.0, 0.0, 0.0 }, 
		{ 1.0, 2.0, 1.0 } }; // 소벨 행 에지 검출 마스크
	double maskCol[3][3] = { { 1.0, 0.0, -1.0 }, 
		{ 2.0, 0.0, -2.0 }, 
		{ 1.0, 0.0, -1.0 } }; // 소벨 열 에지 검출 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpRowInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpColInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpRowOutImage = mallocDoubleMemory(outH, outW);
	double** tmpColOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpRowInImage[i][j] = tmpColInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S1, S2;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

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

	// 임시 출력 영상 --> 출력 영상
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

void edgeLaplacian() { // 경계선 2차 미분 알고리즘 + 라플라시안
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[3][3] = { { 0.0, -1.0, 0.0 }, 
		{ -1.0, 4.0, -1.0 }, 
		{ 0.0, -1.0, 0.0 } }; // 라플라시안 에지 검출 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int j = 0; j < inW + 2; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 1][j + 1] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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

void edgeLoG() { // 경계선 2차 미분 알고리즘 + LoG
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[5][5] = { { 0.0, 0.0, -1.0, 0.0, 0.0 }, 
		{ 0.0, -1.0, -2.0, -1.0, 0.0 },
		{ -1.0, -2.0, 16.0, -2.0, -1.0 }, 
		{ 0.0, -1.0, -2.0, -1.0, 0.0 }, 
		{ 0.0, 0.0, -1.0, 0.0, 0.0 } }; // LoG 에지 검출 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 4, inW + 4);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 4; i++)
		for (int j = 0; j < inW + 4; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 2][j + 2] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 5x5 곱하기
			S = 0.0; // 마스크 25개와 입력값 25개를 각각 곱해서 합한 값

			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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

void edgeDog() {  // 경계선 2차 미분 알고리즘 + DoG
	// 메모리 해제
	freeOutputMemory();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당
	mallocOutputMemory();

	//////////////////
	// 화소 영역 처리
	//////////////////

	double mask[7][7] = { { 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0 }, 
		{ 0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0 }, 
		{ -1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0 },
		{ -1.0, -3.0, 5.0, 16.0, 5.0, -3.0, -1.0 }, 
		{ -1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0 }, 
		{ 0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0 }, 
		{ 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0 } }; // DoG 에지 검출 마스크

	// 임시 메모리 할당 (실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 6, inW + 6);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 6; i++)
		for (int j = 0; j < inW + 6; j++)
			tmpInImage[i][j] = 127;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int j = 0; j < inW; j++)
			tmpInImage[i + 3][j + 3] = inImage[i][j];

	// ** 회선 연산
	double S;

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 5x5 곱하기
			S = 0.0; // 마스크 25개와 입력값 25개를 각각 곱해서 합한 값

			for (int m = 0; m < 7; m++)
				for (int n = 0; n < 7; n++)
					S += tmpInImage[i + m][j + n] * mask[m][n];

			tmpOutImage[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
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