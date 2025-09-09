// Rubik'sCubeData.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <windows.h>
// #include <stdlib.h>
// #include <time.h>
using namespace std;

#define MAX_PSEUDOQUEUE_SIZE 12


struct Piece
{
	int color;
	int x;
	int y;
};

struct Cube		//Cube형 구조체 정의
{
	Piece cubeArr[6][3][3];	//Piece 자료형의 배열 cubeArr
};
//Cube mycube;	//Cube형 변수 mycube 선언

// 큐브 세팅
//Front						//Left					//Back						//Right					//Up					//Down
////[0] BLUE				////[1] RED				////[2] GREEN				////[3] CYAN			////[4] YELLOW 			////[5] WHITE
//	[000][001][002]			//	[100][101][102]		//	[200][201][202]			//	[300][301][302]		//	[400][401][402]		//	[500][501][502]
//	[010][011][012]			//	[110][111][112]		//	[210][211][212]			//	[310][311][312]		//	[410][411][412]		//	[510][511][512]
//	[020][021][022]			//	[120][121][122]		//	[220][221][222]			//	[320][321][322]		//	[420][421][422]		//	[520][521][522]

int colors[6] = { 1, 2, 3, 4, 5, 6 };	//{BLUE,RED,GREEN,CYAN,YELLOW,WHITE} 
void SettingValueCube(Cube* cube)
{
	for (int i = 0; i < 6; i++)														//								Back									
	{																				//							[2] GREEN											
		int curColor = colors[i];													//							[200][201][202]
		for (int j = 0; j < 3; j++)													//							[210][211][212]
		{																			//							[220][221][222]
			for (int k = 0; k < 3; k++)												//							
			{																		//								Up				
				cube->cubeArr[i][j][k].color = curColor;							//							[4] YELLOW 		
			}																		//							[400][401][402]																					
		}																			//							[410][411][412]
	}																				//							[420][421][422]
}																					//																									
																					// 		Right					Front					Left		
//큐브함수 출력(단순 출력)															// 	[3] CYAN				[0] BLUE				[1] RED			
void PrintCube(Cube* cube)															// 	[300][301][302]			[000][001][002]			[100][101][102]
{																					// 	[310][311][312]			[010][011][012]			[110][111][112]
	const char* CubeFace[] = { "FRONT","LEFT","BACK","RIGHT","UP","DOWN" };			// 	[320][321][322]			[020][021][022]			[120][121][122]
	for (int i = 0; i < 6; i++)														// 							
	{																				// 								Down
		printf("%s", CubeFace[i]);													// 							[5] WHITE★ 접었을때 주의 													
		printf("\n");																// 							[500][501][502] 
		//int curColor = colors[i];		//얘는 초기화 할 때 필요한 변수. 밑에서 안쓰니까 안쓰는거 //					[510][511][512] 
		for (int j = 0; j < 3; j++)													// 							[520][521][522]
		{
			for (int k = 0; k < 3; k++)
			{
				//cube->cubeArr[i][j][k].color = curColor;	출력할때마다 계속 초기화를 하기 때문에 
				printf("%d", cube->cubeArr[i][j][k].color);
			}
			printf("\n");
		}
		printf("\n");
	};
}

//큐브 회전으로 같이 움직이는 3*4=12개의 순환구조가 9개 만들어지며, 회전방향이 양쪽이므로 double ended queue(deque) 구조를 생각했지만
//deque와 다르기 때문에 비슷한 구조를 생각함. (chat gpt 도움 받았다)
struct PseudoDeque
{
	//int* arr;	//chat gpt는 포인터로 하라고 했었다. 이유는 모른다
	int dataMZ[MAX_PSEUDOQUEUE_SIZE];			//int*  dataMZ[MAX_QUEUE_SIZE];  이런식으로 int*로 써서 error가 났었다. 이유는 모름
	// 	int frontMZ;					  //int* frontMZ;
	// 	int rearMZ;						  //int* rearMZ;                  큐 아니었다

	int dataKA[MAX_PSEUDOQUEUE_SIZE];

	int dataOQ[MAX_PSEUDOQUEUE_SIZE];

	int dataWS[MAX_PSEUDOQUEUE_SIZE];

	int dataED[MAX_PSEUDOQUEUE_SIZE];

	int dataRF[MAX_PSEUDOQUEUE_SIZE];

	int dataGT[MAX_PSEUDOQUEUE_SIZE];

	int dataHY[MAX_PSEUDOQUEUE_SIZE];

	int dataJU[MAX_PSEUDOQUEUE_SIZE];
};


//순환구조를 배열로, 이어진 12개를 data->dataKA[MAX_QUEUE_SIZE - 1]={ 배열요소 12개 }한번에 정의하려고 했는데 , 한번에 정의하는 방법을 몰라서 수작업했음
// (chat gpt는 "data->dataKA[MAX_QUEUE_SIZE - 1]은 배열이 아니라 큐에서 rear 포인터가 가리키는 위치를 나타내는 변수입니다.이 변수에 배열을 대입하는 것은 올바르지 않습니다." 라고 헀음)
//void init_pseudodeque(PseudoDeque* data)
//{
//	// 	data->frontMZ = 0;								큐가 아니었다. front, rear 삭제할까 했는데, 실수 흔적이라 그냥 남기기로 했다
//	// 	data->rearMZ = MAX_QUEUE_SIZE / 4 - 1;			맨 위에 한개만 남기고 아래에 있는건 지우기로
//
//	// 이미 데이터가 모두 채워져 있음	
//	//dataMZ은 [1][2][0]~[1][0][0], [5][0][2]~[5][0][0], [3][2][2]~[3][0][2], [4][2][2]~[4][2][0] 
//	data->dataMZ[0] = mycube.cubeArr[1][0][0].color;	//	data->dataMZ[0] = mycube.cubeArr[1][0][0];	이렇게 써서 error가 났었다. 배열안에 있는 color까지 고려헀어야함
//	data->dataMZ[1] = mycube.cubeArr[1][1][0].color;	// 그리고 mycube.cubeArr[1][0][0].color가 int형 자료라 위에 가서 dataMZ를 int형으로 바꿨음. 다른것들도 마찬가지
//	data->dataMZ[2] = mycube.cubeArr[1][2][0].color;
//	data->dataMZ[3] = mycube.cubeArr[5][0][2].color;
//	data->dataMZ[4] = mycube.cubeArr[5][0][1].color;
//	data->dataMZ[5] = mycube.cubeArr[5][0][0].color;
//	data->dataMZ[6] = mycube.cubeArr[3][2][2].color;
//	data->dataMZ[7] = mycube.cubeArr[3][1][2].color;
//	data->dataMZ[8] = mycube.cubeArr[3][0][2].color;
//	data->dataMZ[9] = mycube.cubeArr[4][2][0].color;
//	data->dataMZ[10] = mycube.cubeArr[4][2][1].color;
//	data->dataMZ[11] = mycube.cubeArr[4][2][2].color;
//
//	// 이미 데이터가 모두 채워져 있음
//	////dataKA은 [1][0][1]~[1][2][1], [5][1][2]~[5][1][0], [3][2][1]~[3][0][1], [4][1][0]~[4][1][2]   
//	data->dataKA[0] = mycube.cubeArr[1][0][1].color;
//	data->dataKA[1] = mycube.cubeArr[1][1][1].color;
//	data->dataKA[2] = mycube.cubeArr[1][2][1].color;
//	data->dataKA[3] = mycube.cubeArr[5][1][2].color;
//	data->dataKA[4] = mycube.cubeArr[5][1][1].color;
//	data->dataKA[5] = mycube.cubeArr[5][1][0].color;
//	data->dataKA[6] = mycube.cubeArr[3][2][1].color;
//	data->dataKA[7] = mycube.cubeArr[3][1][1].color;
//	data->dataKA[8] = mycube.cubeArr[3][0][1].color;
//	data->dataKA[9] = mycube.cubeArr[4][1][0].color;
//	data->dataKA[10] = mycube.cubeArr[4][1][1].color;
//	data->dataKA[11] = mycube.cubeArr[4][1][2].color;
//
//	// 이미 데이터가 모두 채워져 있음
//	////dataOQ은 [1][0][2]~[1][2][2],[5][2][2]~[5][2][0], [3][2][0]~[3][0][0], [4][0][0]~[4][0][2]  
//	data->dataOQ[0] = mycube.cubeArr[1][0][2].color;
//	data->dataOQ[1] = mycube.cubeArr[1][1][2].color;
//	data->dataOQ[2] = mycube.cubeArr[1][2][2].color;
//	data->dataOQ[3] = mycube.cubeArr[5][2][2].color;
//	data->dataOQ[4] = mycube.cubeArr[5][2][1].color;
//	data->dataOQ[5] = mycube.cubeArr[5][2][0].color;
//	data->dataOQ[6] = mycube.cubeArr[3][2][0].color;
//	data->dataOQ[7] = mycube.cubeArr[3][1][0].color;
//	data->dataOQ[8] = mycube.cubeArr[3][0][0].color;
//	data->dataOQ[9] = mycube.cubeArr[4][0][0].color;
//	data->dataOQ[10] = mycube.cubeArr[4][0][1].color;
//	data->dataOQ[11] = mycube.cubeArr[4][0][2].color;
//
//	// 이미 데이터가 모두 채워져 있음
//	////dataWS은 [4][0][0]~[4][2][0], [0][0][0]~[0][2][0], [5][0][0]~[5][2][0], [2][2][2]~[2][0][2] 
//	data->dataWS[0] = mycube.cubeArr[4][0][0].color;
//	data->dataWS[1] = mycube.cubeArr[4][1][0].color;
//	data->dataWS[2] = mycube.cubeArr[4][2][0].color;
//	data->dataWS[3] = mycube.cubeArr[0][0][0].color;
//	data->dataWS[4] = mycube.cubeArr[0][1][0].color;
//	data->dataWS[5] = mycube.cubeArr[0][2][0].color;
//	data->dataWS[6] = mycube.cubeArr[5][0][0].color;
//	data->dataWS[7] = mycube.cubeArr[5][1][0].color;
//	data->dataWS[8] = mycube.cubeArr[5][2][0].color;
//	data->dataWS[9] = mycube.cubeArr[2][2][2].color;
//	data->dataWS[10] = mycube.cubeArr[2][1][2].color;
//	data->dataWS[11] = mycube.cubeArr[2][0][2].color;
//
//	// 이미 데이터가 모두 채워져 있음
//	////dataED은 [4][0][1]~[4][2][1], [0][0][1]~[0][2][1], [5][0][1]~[5][2][1], [2][0][1]~[2][2][1] 
//	data->dataED[0] = mycube.cubeArr[4][0][1].color;
//	data->dataED[1] = mycube.cubeArr[4][1][1].color;
//	data->dataED[2] = mycube.cubeArr[4][2][1].color;
//	data->dataED[3] = mycube.cubeArr[0][0][1].color;
//	data->dataED[4] = mycube.cubeArr[0][1][1].color;
//	data->dataED[5] = mycube.cubeArr[0][2][1].color;
//	data->dataED[6] = mycube.cubeArr[5][0][1].color;
//	data->dataED[7] = mycube.cubeArr[5][1][1].color;
//	data->dataED[8] = mycube.cubeArr[5][2][1].color;
//	data->dataED[9] = mycube.cubeArr[2][2][1].color;
//	data->dataED[10] = mycube.cubeArr[2][1][1].color;
//	data->dataED[11] = mycube.cubeArr[2][0][1].color;
//
//	// 이미 데이터가 모두 채워져 있음
//	////dataRF은 [4][0][2]~[4][2][2], [0][0][2]~[0][2][2], [5][0][2]~[5][2][2], [2][2][0]~[2][0][0]
//	data->dataRF[0] = mycube.cubeArr[4][0][2].color;
//	data->dataRF[1] = mycube.cubeArr[4][1][2].color;
//	data->dataRF[2] = mycube.cubeArr[4][2][2].color;
//	data->dataRF[3] = mycube.cubeArr[0][0][2].color;
//	data->dataRF[4] = mycube.cubeArr[0][1][2].color;
//	data->dataRF[5] = mycube.cubeArr[0][2][2].color;
//	data->dataRF[6] = mycube.cubeArr[5][0][2].color;
//	data->dataRF[7] = mycube.cubeArr[5][1][2].color;
//	data->dataRF[8] = mycube.cubeArr[5][2][2].color;
//	data->dataRF[9] = mycube.cubeArr[2][2][0].color;
//	data->dataRF[10] = mycube.cubeArr[2][1][0].color;
//	data->dataRF[11] = mycube.cubeArr[2][0][0].color;
//
//	// 이미 데이터가 모두 채워져 있음
//	////dataGT은 [0][0][0]~[0][0][2], [1][0][0]~[1][0][2], [2][0][0]~[2][0][2], [3][0][0]~[3][0][2]
//	data->dataGT[0] = mycube.cubeArr[0][0][0].color;
//	data->dataGT[1] = mycube.cubeArr[0][0][1].color;
//	data->dataGT[2] = mycube.cubeArr[0][0][2].color;
//	data->dataGT[3] = mycube.cubeArr[1][0][0].color;
//	data->dataGT[4] = mycube.cubeArr[1][0][1].color;
//	data->dataGT[5] = mycube.cubeArr[1][0][2].color;
//	data->dataGT[6] = mycube.cubeArr[2][0][0].color;
//	data->dataGT[7] = mycube.cubeArr[2][0][1].color;
//	data->dataGT[8] = mycube.cubeArr[2][0][2].color;
//	data->dataGT[9] = mycube.cubeArr[3][0][0].color;
//	data->dataGT[10] = mycube.cubeArr[3][0][1].color;
//	data->dataGT[11] = mycube.cubeArr[3][0][2].color;
//
//	// 이미 데이터가 모두 채워져 있음
//	////dataHY은 [0][1][0]~[0][1][2], [1][1][0]~[1][1][2], [2][1][0]~[2][1][2], [3][1][0]~[3][1][2]
//	data->dataHY[0] = mycube.cubeArr[0][1][0].color;
//	data->dataHY[1] = mycube.cubeArr[0][1][1].color;
//	data->dataHY[2] = mycube.cubeArr[0][1][2].color;
//	data->dataHY[3] = mycube.cubeArr[1][1][0].color;
//	data->dataHY[4] = mycube.cubeArr[1][1][1].color;
//	data->dataHY[5] = mycube.cubeArr[1][1][2].color;
//	data->dataHY[6] = mycube.cubeArr[2][1][0].color;
//	data->dataHY[7] = mycube.cubeArr[2][1][1].color;
//	data->dataHY[8] = mycube.cubeArr[2][1][2].color;
//	data->dataHY[9] = mycube.cubeArr[3][1][0].color;
//	data->dataHY[10] = mycube.cubeArr[3][1][1].color;
//	data->dataHY[11] = mycube.cubeArr[3][1][2].color;
//
//	// 이미 데이터가 모두 채워져 있음
//	////dataJU은 [0][2][0]~[0][2][2], [1][2][0]~[1][2][2], [2][2][0]~[2][2][2], [3][2][0]~[3][2][2]
//	data->dataJU[0] = mycube.cubeArr[0][2][0].color;
//	data->dataJU[1] = mycube.cubeArr[0][2][1].color;
//	data->dataJU[2] = mycube.cubeArr[0][2][2].color;
//	data->dataJU[3] = mycube.cubeArr[1][2][0].color;
//	data->dataJU[4] = mycube.cubeArr[1][2][1].color;
//	data->dataJU[5] = mycube.cubeArr[1][2][2].color;
//	data->dataJU[6] = mycube.cubeArr[2][2][0].color;
//	data->dataJU[7] = mycube.cubeArr[2][2][1].color;
//	data->dataJU[8] = mycube.cubeArr[2][2][2].color;
//	data->dataJU[9] = mycube.cubeArr[3][2][0].color;
//	data->dataJU[10] = mycube.cubeArr[3][2][1].color;
//	data->dataJU[11] = mycube.cubeArr[3][2][2].color;
//}

//큐브 회전(회전방향이 18개라 최대한 큐브 모양에 가깝게 키를 지정하려고 함)
//모듈러 연산 이용하여 회전 
//회전하면 front, rear의 값이 회전방향에 따라 + 또는 -변하는 것처럼 하고 싶었지만, 이건 deque가 아니다 
void RotateCube(Cube* cube, char p)	//p는 입력한 키
{
	int temp[20];
	for (int i = 0; i <= 19; i++)
	{
		temp[i] = 0;
	}
	//M - LEFT 면의 왼쪽 세로줄을 반시계방향으로 90도 회전	
	if (p == 'm') {
		//for (int i = 0; i < MAX_PSEUDOQUEUE_SIZE; i++)
		//{
		// call by reference 시도
		//	int temp1, temp2, temp3;
		//	temp1 = PseudoDeque.dataMZ[0];		//자료형이 맞는데 계산이 안돼. 구조체는 원래 그런거래
		//	temp2 = PseudoDeque.dataMZ[1];		
		//	temp3 = PseudoDeque.dataMZ[2];		
		//	if (i + 3 >= 12) PseudoDeque.dataMZ[i % 3] == PseudoDeque.dataMZ[i + 3];
		//	else PseudoDeque.dataMZ[i + 3] = PseudoDeque.dataMZ[i];
		//	당연히 되어야 할 것이 안되니까 어쩔 수 없이 하드코딩
		//}

		//call by value...

		temp[0] = cube->cubeArr[1][0][0].color;
		temp[1] = cube->cubeArr[1][1][0].color;
		temp[2] = cube->cubeArr[1][2][0].color;
		temp[3] = cube->cubeArr[5][0][2].color;
		temp[4] = cube->cubeArr[5][0][1].color;
		temp[5] = cube->cubeArr[5][0][0].color;
		temp[6] = cube->cubeArr[3][2][2].color;
		temp[7] = cube->cubeArr[3][1][2].color;
		temp[8] = cube->cubeArr[3][0][2].color;
		temp[9] = cube->cubeArr[4][2][0].color;
		temp[10] = cube->cubeArr[4][2][1].color;
		temp[11] = cube->cubeArr[4][2][2].color;
		cube->cubeArr[1][0][0].color = temp[3];	 //0번
		cube->cubeArr[1][1][0].color = temp[4];	 //1번
		cube->cubeArr[1][2][0].color = temp[5];	 //2번
		cube->cubeArr[5][0][2].color = temp[6];	 //3번
		cube->cubeArr[5][0][1].color = temp[7];	 //4번
		cube->cubeArr[5][0][0].color = temp[8];	 //5번
		cube->cubeArr[3][2][2].color = temp[9];	 //6번
		cube->cubeArr[3][1][2].color = temp[10];	 //7번
		cube->cubeArr[3][0][2].color = temp[11];	 //8번
		cube->cubeArr[4][2][0].color = temp[0];							 //9번
		cube->cubeArr[4][2][1].color = temp[1];							 //10번
		cube->cubeArr[4][2][2].color = temp[2];							 //11번

		//★주의: FRONT면도 돌아간다.
		temp[12] = cube->cubeArr[0][0][0].color;
		temp[13] = cube->cubeArr[0][1][0].color;
		temp[14] = cube->cubeArr[0][2][0].color;
		temp[15] = cube->cubeArr[0][2][1].color;
		temp[16] = cube->cubeArr[0][2][2].color;
		temp[17] = cube->cubeArr[0][1][2].color;
		temp[18] = cube->cubeArr[0][0][2].color;
		temp[19] = cube->cubeArr[0][0][1].color;

		cube->cubeArr[0][0][0].color = temp[18];	 //0번과 같이 돌아간다
		cube->cubeArr[0][1][0].color = temp[19];	 //1번과 같이 돌아간다
		cube->cubeArr[0][2][0].color = temp[12];	 //2번과 같이 돌아간다
		cube->cubeArr[0][2][1].color = temp[13];	 //4번과 같이 돌아간다
		cube->cubeArr[0][2][2].color = temp[14];	 //5번과 같이 돌아간다
		cube->cubeArr[0][1][2].color = temp[15];	 //7번과 같이 돌아간다
		cube->cubeArr[0][0][2].color = temp[16];	 //8번과 같이 돌아간다
		cube->cubeArr[0][0][1].color = temp[17];	 //10번과 같이 돌아간다		
	}
	//Z -  LEFT 면의 왼쪽 세로줄을 시계방향으로 90도 회전	
	else if (p == 'z') {
		temp[0] = cube->cubeArr[1][0][0].color;
		temp[1] = cube->cubeArr[1][1][0].color;
		temp[2] = cube->cubeArr[1][2][0].color;
		temp[3] = cube->cubeArr[4][2][0].color;
		temp[4] = cube->cubeArr[4][2][1].color;
		temp[5] = cube->cubeArr[4][2][2].color;
		temp[6] = cube->cubeArr[3][2][2].color;
		temp[7] = cube->cubeArr[3][1][2].color;
		temp[8] = cube->cubeArr[3][0][2].color;
		temp[9] = cube->cubeArr[5][0][2].color;
		temp[10] = cube->cubeArr[5][0][1].color;
		temp[11] = cube->cubeArr[5][0][0].color;

		cube->cubeArr[1][0][0].color = temp[3];	//0번
		cube->cubeArr[1][1][0].color = temp[4];	//1번
		cube->cubeArr[1][2][0].color = temp[5];	//2번
		cube->cubeArr[4][2][0].color = temp[6];	//9번
		cube->cubeArr[4][2][1].color = temp[7];	//10번
		cube->cubeArr[4][2][2].color = temp[8];	//11번
		cube->cubeArr[3][2][2].color = temp[9];	//6번
		cube->cubeArr[3][1][2].color = temp[10];	//7번
		cube->cubeArr[3][0][2].color = temp[11];	//8번
		cube->cubeArr[5][0][2].color = temp[0];		//3번
		cube->cubeArr[5][0][1].color = temp[1];		//4번
		cube->cubeArr[5][0][0].color = temp[2];		//5번

		//★주의: FRONT면도 돌아간다.
		temp[12] = cube->cubeArr[0][0][0].color;
		temp[13] = cube->cubeArr[0][0][1].color;
		temp[14] = cube->cubeArr[0][0][2].color;
		temp[15] = cube->cubeArr[0][1][2].color;
		temp[16] = cube->cubeArr[0][2][2].color;
		temp[17] = cube->cubeArr[0][2][1].color;
		temp[18] = cube->cubeArr[0][2][0].color;
		temp[19] = cube->cubeArr[0][1][0].color;


		cube->cubeArr[0][0][0].color = temp[18];	 //0번과 같이 돌아간다
		cube->cubeArr[0][0][1].color = temp[19];	 //1번과 같이 돌아간다
		cube->cubeArr[0][0][2].color = temp[12];	 //2번과 같이 돌아간다
		cube->cubeArr[0][1][2].color = temp[13];		 //9번과 같이 돌아간다
		cube->cubeArr[0][2][2].color = temp[14];	 //10번과 같이 돌아간다
		cube->cubeArr[0][2][1].color = temp[15];	 //6번과 같이 돌아간다
		cube->cubeArr[0][2][0].color = temp[16];	 //7번과 같이 돌아간다
		cube->cubeArr[0][1][0].color = temp[17];	 //4번과 같이 돌아간다
	}
	///--------------------------------------------------


	//K - LEFT 면의 가운데 세로줄을 반시계방향으로 90도 회전	
	else if (p == 'k') {
		temp[0] = cube->cubeArr[1][0][1].color;
		temp[1] = cube->cubeArr[1][1][1].color;
		temp[2] = cube->cubeArr[1][2][1].color;
		temp[3] = cube->cubeArr[5][1][2].color;
		temp[4] = cube->cubeArr[5][1][1].color;
		temp[5] = cube->cubeArr[5][1][0].color;
		temp[6] = cube->cubeArr[3][2][1].color;
		temp[7] = cube->cubeArr[3][1][1].color;
		temp[8] = cube->cubeArr[3][0][1].color;
		temp[9] = cube->cubeArr[4][1][0].color;
		temp[10] = cube->cubeArr[4][1][1].color;
		temp[11] = cube->cubeArr[4][1][2].color;



		cube->cubeArr[1][0][1].color = temp[3];	  //0번
		cube->cubeArr[1][1][1].color = temp[4];	  //1번
		cube->cubeArr[1][2][1].color = temp[5];	  //2번
		cube->cubeArr[5][1][2].color = temp[6];	  //3번
		cube->cubeArr[5][1][1].color = temp[7];	  //4번
		cube->cubeArr[5][1][0].color = temp[8];	  //5번
		cube->cubeArr[3][2][1].color = temp[9];	  //6번
		cube->cubeArr[3][1][1].color = temp[10];	  //7번
		cube->cubeArr[3][0][1].color = temp[11];	  //8번
		cube->cubeArr[4][1][0].color = temp[0];							  //9번
		cube->cubeArr[4][1][1].color = temp[1];							  //10번
		cube->cubeArr[4][1][2].color = temp[2];							  //11번
	}
	//A - LEFT 면의 가운데 세로줄을 반시계방향으로 90도 회전
	else if (p == 'a') {
		temp[0] = cube->cubeArr[1][0][1].color;
		temp[1] = cube->cubeArr[1][1][1].color;
		temp[2] = cube->cubeArr[1][2][1].color;
		temp[3] = cube->cubeArr[4][1][0].color;
		temp[4] = cube->cubeArr[4][1][1].color;
		temp[5] = cube->cubeArr[4][1][2].color;
		temp[6] = cube->cubeArr[3][2][1].color;
		temp[7] = cube->cubeArr[3][1][1].color;
		temp[8] = cube->cubeArr[3][0][1].color;
		temp[9] = cube->cubeArr[5][1][2].color;
		temp[10] = cube->cubeArr[5][1][1].color;
		temp[11] = cube->cubeArr[5][1][0].color;

		cube->cubeArr[1][0][1].color = temp[3];	  //0번
		cube->cubeArr[1][1][1].color = temp[4];	  //1번
		cube->cubeArr[1][2][1].color = temp[5];	  //2번
		cube->cubeArr[4][1][0].color = temp[6];	  //9번
		cube->cubeArr[4][1][1].color = temp[7];	  //10번
		cube->cubeArr[4][1][2].color = temp[8];	  //11번
		cube->cubeArr[3][2][1].color = temp[9];	  //6번
		cube->cubeArr[3][1][1].color = temp[10];	  //7번
		cube->cubeArr[3][0][1].color = temp[11];	  //8번
		cube->cubeArr[5][1][2].color = temp[0];							  //3번
		cube->cubeArr[5][1][1].color = temp[1];							  //4번
		cube->cubeArr[5][1][0].color = temp[2];							  //5번
	}

	///------------------------------------------------

	//O - LEFT 면의 오른쪽 세로줄을 반시계방향으로 90도 회전	
	else if (p == 'o') {
		temp[0] = cube->cubeArr[1][0][2].color;
		temp[1] = cube->cubeArr[1][1][2].color;
		temp[2] = cube->cubeArr[1][2][2].color;
		temp[3] = cube->cubeArr[5][2][2].color;
		temp[4] = cube->cubeArr[5][2][1].color;
		temp[5] = cube->cubeArr[5][2][0].color;
		temp[6] = cube->cubeArr[3][2][0].color;
		temp[7] = cube->cubeArr[3][1][0].color;
		temp[8] = cube->cubeArr[3][0][0].color;
		temp[9] = cube->cubeArr[4][0][0].color;
		temp[10] = cube->cubeArr[4][0][1].color;
		temp[11] = cube->cubeArr[4][0][2].color;

		cube->cubeArr[1][0][2].color = temp[3];	   //0번
		cube->cubeArr[1][1][2].color = temp[4];	   //1번
		cube->cubeArr[1][2][2].color = temp[5];	   //2번
		cube->cubeArr[5][2][2].color = temp[6];	   //3번
		cube->cubeArr[5][2][1].color = temp[7];	   //4번
		cube->cubeArr[5][2][0].color = temp[8];	   //5번
		cube->cubeArr[3][2][0].color = temp[9];	   //6번
		cube->cubeArr[3][1][0].color = temp[10];	   //7번
		cube->cubeArr[3][0][0].color = temp[11];	   //8번
		cube->cubeArr[4][0][0].color = temp[0];							   //9번
		cube->cubeArr[4][0][1].color = temp[1];							   //10번
		cube->cubeArr[4][0][2].color = temp[2];							   //11번

		//★주의: BACK면도 돌아간다.
		temp[12] = cube->cubeArr[2][0][0].color;
		temp[13] = cube->cubeArr[2][0][1].color;
		temp[14] = cube->cubeArr[2][0][2].color;
		temp[15] = cube->cubeArr[2][1][2].color;
		temp[16] = cube->cubeArr[2][2][2].color;
		temp[17] = cube->cubeArr[2][2][1].color;
		temp[18] = cube->cubeArr[2][2][0].color;
		temp[19] = cube->cubeArr[2][1][0].color;

		cube->cubeArr[2][0][0].color = temp[18];	 //0번과 같이 돌아간다
		cube->cubeArr[2][0][1].color = temp[19];	 //1번과 같이 돌아간다
		cube->cubeArr[2][0][2].color = temp[12];	 //2번과 같이 돌아간다
		cube->cubeArr[2][1][2].color = temp[13];	 //3번과 같이 돌아간다
		cube->cubeArr[2][2][2].color = temp[14];	 //4번과 같이 돌아간다
		cube->cubeArr[2][2][1].color = temp[15];	 //5번과 같이 돌아간다
		cube->cubeArr[2][2][0].color = temp[16];	 //6번과 같이 돌아간다
		cube->cubeArr[2][1][0].color = temp[17];	 //7번과 같이 돌아간다

	}
	//--------------------------------------------

	//Q - LEFT 면의 오른쪽 세로줄을 시계방향으로 90도 회전	
	else if (p == 'q') {
		temp[0] = cube->cubeArr[1][0][2].color;
		temp[1] = cube->cubeArr[1][1][2].color;
		temp[2] = cube->cubeArr[1][2][2].color;
		temp[3] = cube->cubeArr[4][0][0].color;
		temp[4] = cube->cubeArr[4][0][1].color;
		temp[5] = cube->cubeArr[4][0][2].color;
		temp[6] = cube->cubeArr[3][2][0].color;
		temp[7] = cube->cubeArr[3][1][0].color;
		temp[8] = cube->cubeArr[3][0][0].color;
		temp[9] = cube->cubeArr[5][2][2].color;
		temp[10] = cube->cubeArr[5][2][1].color;
		temp[11] = cube->cubeArr[5][2][0].color;

		cube->cubeArr[1][0][2].color = temp[3];	  //0번
		cube->cubeArr[1][1][2].color = temp[4];	  //1번
		cube->cubeArr[1][2][2].color = temp[5];	  //2번
		cube->cubeArr[4][0][0].color = temp[6];	  //9번
		cube->cubeArr[4][0][1].color = temp[7];	  //10번
		cube->cubeArr[4][0][2].color = temp[8];	  //11번
		cube->cubeArr[3][2][0].color = temp[9];	  //6번
		cube->cubeArr[3][1][0].color = temp[10];	  //7번
		cube->cubeArr[3][0][0].color = temp[11];	  //8번
		cube->cubeArr[5][2][2].color = temp[0];							  //3번
		cube->cubeArr[5][2][1].color = temp[1];							  //4번
		cube->cubeArr[5][2][0].color = temp[2];							  //5번

		//★주의: BACK면도 돌아간다.
		temp[12] = cube->cubeArr[2][0][0].color;
		temp[13] = cube->cubeArr[2][1][0].color;
		temp[14] = cube->cubeArr[2][2][0].color;
		temp[15] = cube->cubeArr[2][2][1].color;
		temp[16] = cube->cubeArr[2][2][2].color;
		temp[17] = cube->cubeArr[2][1][2].color;
		temp[18] = cube->cubeArr[2][0][2].color;
		temp[19] = cube->cubeArr[2][0][1].color;

		cube->cubeArr[2][0][0].color = temp[18];	 //0번과 같이 돌아간다
		cube->cubeArr[2][1][0].color = temp[19];	 //1번과 같이 돌아간다
		cube->cubeArr[2][2][0].color = temp[12];	 //2번과 같이 돌아간다
		cube->cubeArr[2][2][1].color = temp[13];	 //9번과 같이 돌아간다
		cube->cubeArr[2][2][2].color = temp[14];	 //10번과 같이 돌아간다
		cube->cubeArr[2][1][2].color = temp[15];	 //11번과 같이 돌아간다
		cube->cubeArr[2][0][2].color = temp[16];	 //6번과 같이 돌아간다
		cube->cubeArr[2][0][1].color = temp[17];	 //7번과 같이 돌아간다

	}
	///--------------------------------------
	//W - UP 면의 왼쪽 세로줄을 뒤쪽으로 90도 회전	
	else if (p == 'w') {
		temp[0] = cube->cubeArr[4][0][0].color;
		temp[1] = cube->cubeArr[4][1][0].color;
		temp[2] = cube->cubeArr[4][2][0].color;
		temp[3] = cube->cubeArr[0][0][0].color;
		temp[4] = cube->cubeArr[0][1][0].color;
		temp[5] = cube->cubeArr[0][2][0].color;
		temp[6] = cube->cubeArr[5][0][0].color;
		temp[7] = cube->cubeArr[5][1][0].color;
		temp[8] = cube->cubeArr[5][2][0].color;
		temp[9] = cube->cubeArr[2][2][2].color;
		temp[10] = cube->cubeArr[2][1][2].color;
		temp[11] = cube->cubeArr[2][0][2].color;

		cube->cubeArr[4][0][0].color = temp[3];		//0번
		cube->cubeArr[4][1][0].color = temp[4];		//1번
		cube->cubeArr[4][2][0].color = temp[5];		//2번
		cube->cubeArr[0][0][0].color = temp[6];		//3번
		cube->cubeArr[0][1][0].color = temp[7];		//4번
		cube->cubeArr[0][2][0].color = temp[8];		//5번
		cube->cubeArr[5][0][0].color = temp[9];		//6번
		cube->cubeArr[5][1][0].color = temp[10];		//7번
		cube->cubeArr[5][2][0].color = temp[11];		//8번
		cube->cubeArr[2][2][2].color = temp[0];								//9번
		cube->cubeArr[2][1][2].color = temp[1];								//10번
		cube->cubeArr[2][0][2].color = temp[2];								//11번

		//-----------------------
		//★주의: RIGHT면도 돌아간다.
		temp[12] = cube->cubeArr[3][0][0].color;
		temp[13] = cube->cubeArr[3][1][0].color;
		temp[14] = cube->cubeArr[3][2][0].color;
		temp[15] = cube->cubeArr[3][2][1].color;
		temp[16] = cube->cubeArr[3][2][2].color;
		temp[17] = cube->cubeArr[3][1][2].color;
		temp[18] = cube->cubeArr[3][0][2].color;
		temp[19] = cube->cubeArr[3][0][1].color;


		cube->cubeArr[3][0][0].color = temp[18];	 //0번과 같이 돌아간다
		cube->cubeArr[3][1][0].color = temp[19];	 //1번과 같이 돌아간다
		cube->cubeArr[3][2][0].color = temp[12];	 //2번과 같이 돌아간다
		cube->cubeArr[3][2][1].color = temp[13];	 //3번과 같이 돌아간다
		cube->cubeArr[3][2][2].color = temp[14];	 //4번과 같이 돌아간다
		cube->cubeArr[3][1][2].color = temp[15];	 //5번과 같이 돌아간다
		cube->cubeArr[3][0][2].color = temp[16];	 //6번과 같이 돌아간다
		cube->cubeArr[3][0][1].color = temp[17];	 //7번과 같이 돌아간다

	}
	///------------------------------------------------- 

	//S - UP 면의 왼쪽 세로줄을 앞쪽으로 90도 회전.

	else if (p == 's') {
		temp[0] = cube->cubeArr[4][0][0].color;
		temp[1] = cube->cubeArr[4][1][0].color;
		temp[2] = cube->cubeArr[4][2][0].color;
		temp[3] = cube->cubeArr[2][2][2].color;
		temp[4] = cube->cubeArr[2][1][2].color;
		temp[5] = cube->cubeArr[2][0][2].color;
		temp[6] = cube->cubeArr[5][0][0].color;
		temp[7] = cube->cubeArr[5][1][0].color;
		temp[8] = cube->cubeArr[5][2][0].color;
		temp[9] = cube->cubeArr[0][0][0].color;
		temp[10] = cube->cubeArr[0][1][0].color;
		temp[11] = cube->cubeArr[0][2][0].color;

		cube->cubeArr[4][0][0].color = temp[3];		//0번
		cube->cubeArr[4][1][0].color = temp[4];		//1번
		cube->cubeArr[4][2][0].color = temp[5];		//2번
		cube->cubeArr[2][2][2].color = temp[6];		//9번
		cube->cubeArr[2][1][2].color = temp[7];		//10번
		cube->cubeArr[2][0][2].color = temp[8];		//11번
		cube->cubeArr[5][0][0].color = temp[9];		//6번
		cube->cubeArr[5][1][0].color = temp[10];		//7번
		cube->cubeArr[5][2][0].color = temp[11];		//8번
		cube->cubeArr[0][0][0].color = temp[0];								//3번
		cube->cubeArr[0][1][0].color = temp[1];								//4번
		cube->cubeArr[0][2][0].color = temp[2];								//5번

		//-------------------------------------------
		//★주의: RIGHT면도 돌아간다
		temp[12] = cube->cubeArr[3][0][0].color;
		temp[13] = cube->cubeArr[3][0][1].color;
		temp[14] = cube->cubeArr[3][0][2].color;
		temp[15] = cube->cubeArr[3][1][2].color;
		temp[16] = cube->cubeArr[3][2][2].color;
		temp[17] = cube->cubeArr[3][2][1].color;
		temp[18] = cube->cubeArr[3][2][0].color;
		temp[19] = cube->cubeArr[3][1][0].color;


		cube->cubeArr[3][0][0].color = temp[18];	 //0번과 같이 돌아간다
		cube->cubeArr[3][0][1].color = temp[19];	 //1번과 같이 돌아간다
		cube->cubeArr[3][0][2].color = temp[12];	 //2번과 같이 돌아간다
		cube->cubeArr[3][1][2].color = temp[13];	 //9번과 같이 돌아간다
		cube->cubeArr[3][2][2].color = temp[14];	 //10번과 같이 돌아간다
		cube->cubeArr[3][2][1].color = temp[15];	 //11번과 같이 돌아간다
		cube->cubeArr[3][2][0].color = temp[16];	 //6번과 같이 돌아간다
		cube->cubeArr[3][1][0].color = temp[17];	 //7번과 같이 돌아간다

	}

	///------------------------------------------------------

	//E - UP 면의 가운데 세로줄을 뒤쪽으로 90도 회전	
	else if (p == 'e') {
		temp[0] = cube->cubeArr[4][0][1].color;
		temp[1] = cube->cubeArr[4][1][1].color;
		temp[2] = cube->cubeArr[4][2][1].color;
		temp[3] = cube->cubeArr[0][0][1].color;
		temp[4] = cube->cubeArr[0][1][1].color;
		temp[5] = cube->cubeArr[0][2][1].color;
		temp[6] = cube->cubeArr[5][0][1].color;
		temp[7] = cube->cubeArr[5][1][1].color;
		temp[8] = cube->cubeArr[5][2][1].color;
		temp[9] = cube->cubeArr[2][2][1].color;
		temp[10] = cube->cubeArr[2][1][1].color;
		temp[11] = cube->cubeArr[2][0][1].color;


		cube->cubeArr[4][0][1].color = temp[3];		//0번
		cube->cubeArr[4][1][1].color = temp[4];		//1번
		cube->cubeArr[4][2][1].color = temp[5];		//2번
		cube->cubeArr[0][0][1].color = temp[6];		//3번
		cube->cubeArr[0][1][1].color = temp[7];		//4번
		cube->cubeArr[0][2][1].color = temp[8];		//5번
		cube->cubeArr[5][0][1].color = temp[9];		//6번
		cube->cubeArr[5][1][1].color = temp[10];		//7번
		cube->cubeArr[5][2][1].color = temp[11];		//8번
		cube->cubeArr[2][2][1].color = temp[0];								//9번
		cube->cubeArr[2][1][1].color = temp[1];								//10번
		cube->cubeArr[2][0][1].color = temp[2];								//11번
	}
	//D - UP 면의 가운데 세로줄을 앞쪽으로 90도 회전
	else if (p == 'd') {
		temp[0] = cube->cubeArr[4][0][1].color;
		temp[1] = cube->cubeArr[4][1][1].color;
		temp[2] = cube->cubeArr[4][2][1].color;
		temp[3] = cube->cubeArr[2][2][1].color;
		temp[4] = cube->cubeArr[2][1][1].color;
		temp[5] = cube->cubeArr[2][0][1].color;
		temp[6] = cube->cubeArr[5][0][1].color;
		temp[7] = cube->cubeArr[5][1][1].color;
		temp[8] = cube->cubeArr[5][2][1].color;
		temp[9] = cube->cubeArr[0][0][1].color;
		temp[10] = cube->cubeArr[0][1][1].color;
		temp[11] = cube->cubeArr[0][2][1].color;

		cube->cubeArr[4][0][1].color = temp[3];		//0번
		cube->cubeArr[4][1][1].color = temp[4];		//1번
		cube->cubeArr[4][2][1].color = temp[5];		//2번
		cube->cubeArr[2][2][1].color = temp[6];		//9번
		cube->cubeArr[2][1][1].color = temp[7];		//10번
		cube->cubeArr[2][0][1].color = temp[8];		//11번
		cube->cubeArr[5][0][1].color = temp[9];		//6번
		cube->cubeArr[5][1][1].color = temp[10];		//7번
		cube->cubeArr[5][2][1].color = temp[11];		//8번
		cube->cubeArr[0][0][1].color = temp[0];								//3번
		cube->cubeArr[0][1][1].color = temp[1];								//4번
		cube->cubeArr[0][2][1].color = temp[2];								//5번
	}
	///------------------------------------------------

	//R - UP 면의 오른쪽 세로줄을 뒤쪽으로 90도 회전

	else if (p == 'r') {
		temp[0] = cube->cubeArr[4][0][2].color;
		temp[1] = cube->cubeArr[4][1][2].color;
		temp[2] = cube->cubeArr[4][2][2].color;
		temp[3] = cube->cubeArr[0][0][2].color;
		temp[4] = cube->cubeArr[0][1][2].color;
		temp[5] = cube->cubeArr[0][2][2].color;
		temp[6] = cube->cubeArr[5][0][2].color;
		temp[7] = cube->cubeArr[5][1][2].color;
		temp[8] = cube->cubeArr[5][2][2].color;
		temp[9] = cube->cubeArr[2][2][0].color;
		temp[10] = cube->cubeArr[2][1][0].color;
		temp[11] = cube->cubeArr[2][0][0].color;

		cube->cubeArr[4][0][2].color = temp[3];		//0번
		cube->cubeArr[4][1][2].color = temp[4];		//1번
		cube->cubeArr[4][2][2].color = temp[5];		//2번
		cube->cubeArr[0][0][2].color = temp[6];		//3번
		cube->cubeArr[0][1][2].color = temp[7];		//4번
		cube->cubeArr[0][2][2].color = temp[8];		//5번
		cube->cubeArr[5][0][2].color = temp[9];		//6번
		cube->cubeArr[5][1][2].color = temp[10];		//7번
		cube->cubeArr[5][2][2].color = temp[11];		//8번
		cube->cubeArr[2][2][0].color = temp[0];								//9번
		cube->cubeArr[2][1][0].color = temp[1];								//10번
		cube->cubeArr[2][0][0].color = temp[2];								//11번
		//----------------------------------
		//★주의: LEFT면도 돌아간다
		temp[12] = cube->cubeArr[1][0][0].color;
		temp[13] = cube->cubeArr[1][0][1].color;
		temp[14] = cube->cubeArr[1][0][2].color;
		temp[15] = cube->cubeArr[1][1][2].color;
		temp[16] = cube->cubeArr[1][2][2].color;
		temp[17] = cube->cubeArr[1][2][1].color;
		temp[18] = cube->cubeArr[1][2][0].color;
		temp[19] = cube->cubeArr[1][1][0].color;


		cube->cubeArr[1][0][0].color = temp[18];	  //0번과 같이 돌아간다
		cube->cubeArr[1][0][1].color = temp[19];	  //1번과 같이 돌아간다
		cube->cubeArr[1][0][2].color = temp[12];	  //2번과 같이 돌아간다
		cube->cubeArr[1][1][2].color = temp[13];	  //3번과 같이 돌아간다
		cube->cubeArr[1][2][2].color = temp[14];	  //4번과 같이 돌아간다
		cube->cubeArr[1][2][1].color = temp[15];	  //5번과 같이 돌아간다
		cube->cubeArr[1][2][0].color = temp[16];	  //6번과 같이 돌아간다
		cube->cubeArr[1][1][0].color = temp[17];	  //7번과 같이 돌아간다

	}

	///-----------------------------------------------------
	//F - UP 면의 오른쪽 세로줄을 앞쪽으로 90도 회전	
	else if (p == 'f') {
		temp[0] = cube->cubeArr[4][0][2].color;
		temp[1] = cube->cubeArr[4][1][2].color;
		temp[2] = cube->cubeArr[4][2][2].color;
		temp[3] = cube->cubeArr[2][2][0].color;
		temp[4] = cube->cubeArr[2][1][0].color;
		temp[5] = cube->cubeArr[2][0][0].color;
		temp[6] = cube->cubeArr[5][0][2].color;
		temp[7] = cube->cubeArr[5][1][2].color;
		temp[8] = cube->cubeArr[5][2][2].color;
		temp[9] = cube->cubeArr[0][0][2].color;
		temp[10] = cube->cubeArr[0][1][2].color;
		temp[11] = cube->cubeArr[0][2][2].color;

		cube->cubeArr[4][0][2].color = temp[3];		//0번
		cube->cubeArr[4][1][2].color = temp[4];		//1번
		cube->cubeArr[4][2][2].color = temp[5];		//2번
		cube->cubeArr[2][2][0].color = temp[6];		//9번
		cube->cubeArr[2][1][0].color = temp[7];		//10번
		cube->cubeArr[2][0][0].color = temp[8];		//11번
		cube->cubeArr[5][0][2].color = temp[9];		//6번
		cube->cubeArr[5][1][2].color = temp[10];		//7번
		cube->cubeArr[5][2][2].color = temp[11];		//8번
		cube->cubeArr[0][0][2].color = temp[0];								//3번
		cube->cubeArr[0][1][2].color = temp[1];								//4번
		cube->cubeArr[0][2][2].color = temp[2];								//5번
		//----------------------------
		//★주의: LEFT면도 돌아간다
		temp[12] = cube->cubeArr[1][0][0].color;
		temp[13] = cube->cubeArr[1][1][0].color;
		temp[14] = cube->cubeArr[1][2][0].color;
		temp[15] = cube->cubeArr[1][2][1].color;
		temp[16] = cube->cubeArr[1][2][2].color;
		temp[17] = cube->cubeArr[1][1][2].color;
		temp[18] = cube->cubeArr[1][0][2].color;
		temp[19] = cube->cubeArr[1][0][1].color;

		cube->cubeArr[1][0][0].color = temp[18];	 //0번과 같이 돌아간다
		cube->cubeArr[1][1][0].color = temp[19];	 //1번과 같이 돌아간다
		cube->cubeArr[1][2][0].color = temp[12];	 //2번과 같이 돌아간다
		cube->cubeArr[1][2][1].color = temp[13];	 //9번과 같이 돌아간다
		cube->cubeArr[1][2][2].color = temp[14];	 //10번과 같이 돌아간다
		cube->cubeArr[1][1][2].color = temp[15];	 //11번과 같이 돌아간다
		cube->cubeArr[1][0][2].color = temp[16];	 //6번과 같이 돌아간다
		cube->cubeArr[1][0][1].color = temp[17];	 //7번과 같이 돌아간다

	}
	///--------------------------------------------------------------------------
	//G - FRONT 면의 위쪽 가로줄을 반시계 방향으로 90도 회전		
	else if (p == 'g') {
		temp[0] = cube->cubeArr[0][0][0].color;
		temp[1] = cube->cubeArr[0][0][1].color;
		temp[2] = cube->cubeArr[0][0][2].color;
		temp[3] = cube->cubeArr[3][0][0].color;
		temp[4] = cube->cubeArr[3][0][1].color;
		temp[5] = cube->cubeArr[3][0][2].color;
		temp[6] = cube->cubeArr[2][0][0].color;
		temp[7] = cube->cubeArr[2][0][1].color;
		temp[8] = cube->cubeArr[2][0][2].color;
		temp[9] = cube->cubeArr[1][0][0].color;
		temp[10] = cube->cubeArr[1][0][1].color;
		temp[11] = cube->cubeArr[1][0][2].color;

		cube->cubeArr[0][0][0].color = temp[3];		//0번
		cube->cubeArr[0][0][1].color = temp[4];		//1번
		cube->cubeArr[0][0][2].color = temp[5];		//2번
		cube->cubeArr[3][0][0].color = temp[6];		//9번
		cube->cubeArr[3][0][1].color = temp[7];		//10번
		cube->cubeArr[3][0][2].color = temp[8];		//11번
		cube->cubeArr[2][0][0].color = temp[9];		//6번
		cube->cubeArr[2][0][1].color = temp[10];		//7번
		cube->cubeArr[2][0][2].color = temp[11];		//8번
		cube->cubeArr[1][0][0].color = temp[0];								//3번
		cube->cubeArr[1][0][1].color = temp[1];								//4번
		cube->cubeArr[1][0][2].color = temp[2];								//5번
		//----------------------------------
		//★주의: UP면도 돌아간다
		temp[12] = cube->cubeArr[4][0][0].color;
		temp[13] = cube->cubeArr[4][1][0].color;
		temp[14] = cube->cubeArr[4][2][0].color;
		temp[15] = cube->cubeArr[4][2][1].color;
		temp[16] = cube->cubeArr[4][2][2].color;
		temp[17] = cube->cubeArr[4][1][2].color;
		temp[18] = cube->cubeArr[4][0][2].color;
		temp[19] = cube->cubeArr[4][0][1].color;


		cube->cubeArr[4][0][0].color = temp[18];	 //0번과 같이 돌아간다
		cube->cubeArr[4][1][0].color = temp[19];	 //1번과 같이 돌아간다
		cube->cubeArr[4][2][0].color = temp[12];	 //2번과 같이 돌아간다
		cube->cubeArr[4][2][1].color = temp[13];	 //9번과 같이 돌아간다
		cube->cubeArr[4][2][2].color = temp[14];	 //10번과 같이 돌아간다
		cube->cubeArr[4][1][2].color = temp[15];	 //11번과 같이 돌아간다
		cube->cubeArr[4][0][2].color = temp[16];	 //6번과 같이 돌아간다
		cube->cubeArr[4][0][1].color = temp[17];	 //7번과 같이 돌아간다

	}
	///--------------------------------------------------------------
	//T - FRONT 면의 위쪽 가로줄을 시계 방향으로 90도 회전	
	else if (p == 't') {
		temp[0] = cube->cubeArr[0][0][0].color;
		temp[1] = cube->cubeArr[0][0][1].color;
		temp[2] = cube->cubeArr[0][0][2].color;
		temp[3] = cube->cubeArr[1][0][0].color;
		temp[4] = cube->cubeArr[1][0][1].color;
		temp[5] = cube->cubeArr[1][0][2].color;
		temp[6] = cube->cubeArr[2][0][0].color;
		temp[7] = cube->cubeArr[2][0][1].color;
		temp[8] = cube->cubeArr[2][0][2].color;
		temp[9] = cube->cubeArr[3][0][0].color;
		temp[10] = cube->cubeArr[3][0][1].color;
		temp[11] = cube->cubeArr[3][0][2].color;

		cube->cubeArr[0][0][0].color = temp[3];		//0번
		cube->cubeArr[0][0][1].color = temp[4];		//1번
		cube->cubeArr[0][0][2].color = temp[5];		//2번
		cube->cubeArr[1][0][0].color = temp[6];		//3번
		cube->cubeArr[1][0][1].color = temp[7];		//4번
		cube->cubeArr[1][0][2].color = temp[8];		//5번
		cube->cubeArr[2][0][0].color = temp[9];		//6번
		cube->cubeArr[2][0][1].color = temp[10];		//7번
		cube->cubeArr[2][0][2].color = temp[11];		//8번
		cube->cubeArr[3][0][0].color = temp[0];								//9번
		cube->cubeArr[3][0][1].color = temp[1];								//10번
		cube->cubeArr[3][0][2].color = temp[2];								//11번
		//--------------------------------------
		//★주의: UP면도 돌아간다
		temp[12] = cube->cubeArr[4][0][0].color;
		temp[13] = cube->cubeArr[4][0][1].color;
		temp[14] = cube->cubeArr[4][0][2].color;
		temp[15] = cube->cubeArr[4][1][2].color;
		temp[16] = cube->cubeArr[4][2][2].color;
		temp[17] = cube->cubeArr[4][2][1].color;
		temp[18] = cube->cubeArr[4][2][0].color;
		temp[19] = cube->cubeArr[4][1][0].color;

		cube->cubeArr[4][0][0].color = temp[18];	  //0번과 같이 돌아간다
		cube->cubeArr[4][0][1].color = temp[19];	  //1번과 같이 돌아간다
		cube->cubeArr[4][0][2].color = temp[12];	  //2번과 같이 돌아간다
		cube->cubeArr[4][1][2].color = temp[13];	  //3번과 같이 돌아간다
		cube->cubeArr[4][2][2].color = temp[14];	  //4번과 같이 돌아간다
		cube->cubeArr[4][2][1].color = temp[15];	  //5번과 같이 돌아간다
		cube->cubeArr[4][2][0].color = temp[16];	  //6번과 같이 돌아간다
		cube->cubeArr[4][1][0].color = temp[17];	  //7번과 같이 돌아간다
	}
	///------------------------------------------------------------
	//H - FRONT 면의 가운데 가로줄을 반시계 방향으로 90도 회전	
	else if (p == 'h') {
		temp[0] = cube->cubeArr[0][1][0].color;
		temp[1] = cube->cubeArr[0][1][1].color;
		temp[2] = cube->cubeArr[0][1][2].color;
		temp[3] = cube->cubeArr[3][1][0].color;
		temp[4] = cube->cubeArr[3][1][1].color;
		temp[5] = cube->cubeArr[3][1][2].color;
		temp[6] = cube->cubeArr[2][1][0].color;
		temp[7] = cube->cubeArr[2][1][1].color;
		temp[8] = cube->cubeArr[2][1][2].color;
		temp[9] = cube->cubeArr[1][1][0].color;
		temp[10] = cube->cubeArr[1][1][1].color;
		temp[11] = cube->cubeArr[1][1][2].color;

		cube->cubeArr[0][1][0].color = temp[3];		//0번
		cube->cubeArr[0][1][1].color = temp[4];		//1번
		cube->cubeArr[0][1][2].color = temp[5];		//2번
		cube->cubeArr[3][1][0].color = temp[6];		//9번
		cube->cubeArr[3][1][1].color = temp[7];		//10번
		cube->cubeArr[3][1][2].color = temp[8];		//11번
		cube->cubeArr[2][1][0].color = temp[9];		//6번
		cube->cubeArr[2][1][1].color = temp[10];		//7번
		cube->cubeArr[2][1][2].color = temp[11];		//8번
		cube->cubeArr[1][1][0].color = temp[0];								//3번
		cube->cubeArr[1][1][1].color = temp[1];								//4번
		cube->cubeArr[1][1][2].color = temp[2];								//5번
	}
	//Y - FRONT 면의 가운데 가로줄을 시계 방향으로 90도 회전
	else if (p == 'y') {
		temp[0] = cube->cubeArr[0][1][0].color;
		temp[1] = cube->cubeArr[0][1][1].color;
		temp[2] = cube->cubeArr[0][1][2].color;
		temp[3] = cube->cubeArr[1][1][0].color;
		temp[4] = cube->cubeArr[1][1][1].color;
		temp[5] = cube->cubeArr[1][1][2].color;
		temp[6] = cube->cubeArr[2][1][0].color;
		temp[7] = cube->cubeArr[2][1][1].color;
		temp[8] = cube->cubeArr[2][1][2].color;
		temp[9] = cube->cubeArr[3][1][0].color;
		temp[10] = cube->cubeArr[3][1][1].color;
		temp[11] = cube->cubeArr[3][1][2].color;

		cube->cubeArr[0][1][0].color = temp[3];		//0번		
		cube->cubeArr[0][1][1].color = temp[4];		//1번		
		cube->cubeArr[0][1][2].color = temp[5];		//2번		
		cube->cubeArr[1][1][0].color = temp[6];		//3번		
		cube->cubeArr[1][1][1].color = temp[7];		//4번		
		cube->cubeArr[1][1][2].color = temp[8];		//5번		
		cube->cubeArr[2][1][0].color = temp[9];		//6번		
		cube->cubeArr[2][1][1].color = temp[10];		//7번		
		cube->cubeArr[2][1][2].color = temp[11];		//8번		
		cube->cubeArr[3][1][0].color = temp[0];								//9번		
		cube->cubeArr[3][1][1].color = temp[1];								//10번		
		cube->cubeArr[3][1][2].color = temp[2];								//11번		
	}
	///----------------------------------------------------------
	//J - FRONT 면의 아래쪽 가로줄을 반시계 방향으로 90도 회전		
	else if (p == 'j') {
		temp[0] = cube->cubeArr[0][2][0].color;
		temp[1] = cube->cubeArr[0][2][1].color;
		temp[2] = cube->cubeArr[0][2][2].color;
		temp[3] = cube->cubeArr[3][2][0].color;
		temp[4] = cube->cubeArr[3][2][1].color;
		temp[5] = cube->cubeArr[3][2][2].color;
		temp[6] = cube->cubeArr[2][2][0].color;
		temp[7] = cube->cubeArr[2][2][1].color;
		temp[8] = cube->cubeArr[2][2][2].color;
		temp[9] = cube->cubeArr[1][2][0].color;
		temp[10] = cube->cubeArr[1][2][1].color;
		temp[11] = cube->cubeArr[1][2][2].color;

		cube->cubeArr[0][2][0].color = temp[3];		//0번
		cube->cubeArr[0][2][1].color = temp[4];		//1번
		cube->cubeArr[0][2][2].color = temp[5];		//2번
		cube->cubeArr[3][2][0].color = temp[6];		//9번
		cube->cubeArr[3][2][1].color = temp[7];		//10번
		cube->cubeArr[3][2][2].color = temp[8];		//11번
		cube->cubeArr[2][2][0].color = temp[9];		//6번
		cube->cubeArr[2][2][1].color = temp[10];		//7번
		cube->cubeArr[2][2][2].color = temp[11];		//8번
		cube->cubeArr[1][2][0].color = temp[0];								//3번
		cube->cubeArr[1][2][1].color = temp[1];								//4번
		cube->cubeArr[1][2][2].color = temp[2];								//5번
		//-----------------------------------------
		//★주의: DOWN면도 돌아간다
		temp[12] = cube->cubeArr[5][0][0].color;
		temp[13] = cube->cubeArr[5][0][1].color;
		temp[14] = cube->cubeArr[5][0][2].color;
		temp[15] = cube->cubeArr[5][1][2].color;
		temp[16] = cube->cubeArr[5][2][2].color;
		temp[17] = cube->cubeArr[5][2][1].color;
		temp[18] = cube->cubeArr[5][2][0].color;
		temp[19] = cube->cubeArr[5][1][0].color;

		cube->cubeArr[5][0][0].color = temp[18];	 //0번과 같이 돌아간다
		cube->cubeArr[5][0][1].color = temp[19];	 //1번과 같이 돌아간다
		cube->cubeArr[5][0][2].color = temp[12];	 //2번과 같이 돌아간다
		cube->cubeArr[5][1][2].color = temp[13];	 //9번과 같이 돌아간다
		cube->cubeArr[5][2][2].color = temp[14];	 //10번과 같이 돌아간다
		cube->cubeArr[5][2][1].color = temp[15];	 //11번과 같이 돌아간다
		cube->cubeArr[5][2][0].color = temp[16];	 //6번과 같이 돌아간다
		cube->cubeArr[5][1][0].color = temp[17];	 //7번과 같이 돌아간다

	}
	///---------------------------------------------------여기까지
	//U - FRONT 면의 아래쪽 가로줄을 시계 방향으로 90도 회전	
	else if (p == 'u') {
		temp[0] = cube->cubeArr[0][2][0].color;
		temp[1] = cube->cubeArr[0][2][1].color;
		temp[2] = cube->cubeArr[0][2][2].color;
		temp[3] = cube->cubeArr[1][2][0].color;
		temp[4] = cube->cubeArr[1][2][1].color;
		temp[5] = cube->cubeArr[1][2][2].color;
		temp[6] = cube->cubeArr[2][2][0].color;
		temp[7] = cube->cubeArr[2][2][1].color;
		temp[8] = cube->cubeArr[2][2][2].color;
		temp[9] = cube->cubeArr[3][2][0].color;
		temp[10] = cube->cubeArr[3][2][1].color;
		temp[11] = cube->cubeArr[3][2][2].color;

		cube->cubeArr[0][2][0].color = temp[3];		//0번	
		cube->cubeArr[0][2][1].color = temp[4];		//1번	
		cube->cubeArr[0][2][2].color = temp[5];		//2번	
		cube->cubeArr[1][2][0].color = temp[6];		//3번	
		cube->cubeArr[1][2][1].color = temp[7];		//4번	
		cube->cubeArr[1][2][2].color = temp[8];		//5번	
		cube->cubeArr[2][2][0].color = temp[9];		//6번	
		cube->cubeArr[2][2][1].color = temp[10];		//7번	
		cube->cubeArr[2][2][2].color = temp[11];		//8번	
		cube->cubeArr[3][2][0].color = temp[0];								//9번	
		cube->cubeArr[3][2][1].color = temp[1];								//10번	
		cube->cubeArr[3][2][2].color = temp[2];								//11번	

		////★주의: DOWN면도 돌아간다
		temp[12] = cube->cubeArr[5][0][0].color;
		temp[13] = cube->cubeArr[5][1][0].color;
		temp[14] = cube->cubeArr[5][2][0].color;
		temp[15] = cube->cubeArr[5][2][1].color;
		temp[16] = cube->cubeArr[5][2][2].color;
		temp[17] = cube->cubeArr[5][1][2].color;
		temp[18] = cube->cubeArr[5][0][2].color;
		temp[19] = cube->cubeArr[5][0][1].color;

		cube->cubeArr[5][0][0].color = temp[18];	  //0번과 같이 돌아간다
		cube->cubeArr[5][1][0].color = temp[19];	  //1번과 같이 돌아간다
		cube->cubeArr[5][2][0].color = temp[12];	  //2번과 같이 돌아간다
		cube->cubeArr[5][2][1].color = temp[13];	  //3번과 같이 돌아간다
		cube->cubeArr[5][2][2].color = temp[14];	  //4번과 같이 돌아간다
		cube->cubeArr[5][1][2].color = temp[15];	  //5번과 같이 돌아간다
		cube->cubeArr[5][0][2].color = temp[16];	  //6번과 같이 돌아간다
		cube->cubeArr[5][0][1].color = temp[17];	  //7번과 같이 돌아간다		
	}
}

/// 알 수 없는 이유로 4번까지만 써지는 문제가 있음. 그것빼고는 complete


//배열 무작위 섞기
// void ScrambleCube()
// {
// 
// }

//맞는지 확인
// int IsComplete()
// {
// 	for (int i = 0; i < 6; i++)
// 	{
// 		for (int j = 0; j < 3; j++)
// 		{
// 			for (int k = 0; k < 3; k++)
// 			{
// 				Cube.mycube->cubeArr[i][j][k].color == curColor;
// 			}
// 		}
// 	}
// }

int main()
{
	Cube myCube;
	SettingValueCube(&myCube);	//초기화는 시작할 떄 한번만 했어야함

	//시작하면 큐브 무작위 셔플: 회전 랜덤으로 20번 돌린다
	//ScrambleCube();

	while (true)
	{
		cout << "M - LEFT 면의 왼쪽 세로줄을 반시계방향으로 90도 회전" << endl;
		cout << "Z - LEFT 면의 왼쪽 세로줄을 시계방향으로 90도 회전" << endl;
		//-----------------------------------------------------------
		cout << "K - LEFT 면의 가운데 세로줄을 반시계방향으로 90도 회전" << endl;
		cout << "A - LEFT 면의 가운데 세로줄을 시계방향으로 90도 회전" << endl;
		//-----------------------------------------------------------
		cout << "O - LEFT 면의 오른쪽 세로줄을 반시계방향으로 90도 회전" << endl;
		cout << "Q - LEFT 면의 오른쪽 세로줄을 시계방향으로 90도 회전" << endl;
		//=============================================================================
		cout << "W - UP 면의 왼쪽 세로줄을 뒤쪽으로 90도 회전" << endl;
		cout << "S - UP 면의 왼쪽 세로줄을 앞쪽으로 90도 회전" << endl;
		//-----------------------------------------------------------
		cout << "E - UP 면의 가운데 세로줄을 뒤쪽으로 90도 회전" << endl;
		cout << "D - UP 면의 가운데 세로줄을 앞쪽으로 90도 회전" << endl;
		//-----------------------------------------------------------
		cout << "R - UP 면의 오른쪽 세로줄을 뒤쪽으로 90도 회전" << endl;
		cout << "F - UP 면의 오른쪽 세로줄을 앞쪽으로 90도 회전" << endl;
		//=============================================================================
		cout << "G - FRONT 면의 위쪽 가로줄을 반시계 방향으로 90도 회전" << endl;
		cout << "T - FRONT 면의 위쪽 가로줄을 시계 방향으로 90도 회전" << endl;
		//----------------------------------------------------------
		cout << "H - FRONT 면의 가운데 가로줄을 반시계 방향으로 90도 회전" << endl;
		cout << "Y - FRONT 면의 가운데 가로줄을 시계 방향으로 90도 회전" << endl;
		//----------------------------------------------------------
		cout << "J - FRONT 면의 아래쪽 가로줄을 반시계 방향으로 90도 회전" << endl;
		cout << "U - FRONT 면의 아래쪽 가로줄을 시계 방향으로 90도 회전" << endl;
		//============================================================================
		cout << " '?' 입력하면 정답 공개" << endl;

		char p;
		cin >> p;
		if (p == '?') break;
		else
		{

			RotateCube(&myCube, p);
			PrintCube(&myCube);
			//if (IsComplete() == 1) break;
		}
	}

}


//--------------------------------------------------------------------

//쿼터니언 회전은 여기서 하는게 아니다. 이건 3D 그래픽에 적용해야되는거
	//	//쿼터니언 추가
	//	typedef struct
	//{
	//	double w, x, y, z;
	//} Quaternion;

	////쿼터니언 회전
	//Quaternion rotateVectorWithQuaternion(Quaternion q, Quaternion v)
	//{
	//	Quaternion conjugate = { q.w, -q.x, -q.y, -q.z };
	//	Quaternion result = multiplyQuaternions(q, multiplyQuaternions(v, conjugate));
	//	return result;
	//}

	////두 사원수 q1, q2의 곱 (필요없으면 지우자. 굳이 2개의 곱으로 나타낼 필요가 있나 싶음. 회전은 1번씩 할거니까)
	//Quaternion multiplyQuaternions(Quaternion q1, Quaternion q2)
	//{
	//	Quaternion result;
	//	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	//	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	//	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	//	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	//	return result;
	//}


//위 코드에서는 Quaternion 이라는 구조체를 정의하여 쿼터니언을 저장하고, 
//multiplyQuaternions 함수와 rotateVectorWithQuaternion 함수를 정의하여 쿼터니언의 곱셈과 벡터의 회전을 계산합니다.
//main 함수에서는 회전 각도와 초기 벡터를 설정하고, 회전된 벡터를 출력합니다.
//위 코드에서는 theta 값으로 45도를 사용하였지만, 필요에 따라 다른 각도 값을 사용하여 회전할 수 있습니다.
//또한, 초기 벡터의 값을 변경하여 다른 벡터를 회전할 수 있습니다.

//-----------------------------------------------------------------

////실패할 경우를 대비한 큐브 2번째
////이건 2차원 배열을 이용한 것 같은데...
//// 큐브 구조체 정의
//struct Cube {
//	char front[3][3];   // 앞 면
//	char back[3][3];    // 뒷 면
//	char up[3][3];      // 윗 면
//	char down[3][3];    // 아랫 면
//	char left[3][3];    // 왼쪽 면
//	char right[3][3];   // 오른쪽 면
//};
//
//int main() {
//	// 큐브 구조체 초기화
//	struct Cube cube = {
//		{ {'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'} },   // 앞 면 초기화
//		{ {'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'} },   // 뒷 면 초기화
//		{ {'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'} },   // 윗 면 초기화
//		{ {'R', 'R', 'R'}, {'R', 'R', 'R'}, {'R', 'R', 'R'} },   // 아랫 면 초기화
//		{ {'G', 'G', 'G'}, {'G', 'G', 'G'}, {'G', 'G', 'G'} },   // 왼쪽 면 초기화
//		{ {'B', 'B', 'B'}, {'B', 'B', 'B'}, {'B', 'B', 'B'} }    // 오른쪽 면 초기화
//	};
//
//	// 각 면의 성분에 색상 부여
//	cube.front[0][0] = 'B';
//	cube.front[0][1] = 'B';
//	cube.front[0][2] = 'B';
//	cube.front[1][0] = 'B';
//	cube.front[1][1] = 'B';
//	cube.front[1][2] = 'B';
//	cube.front[2][0] = 'B';
//	cube.front[2][1] = 'B';
//	cube.front[2][2] = 'B';
//
//	cube.back[0][0] = 'R ';
//	cube.back[0][1] = 'R ';
//	cube.back[0][2] = 'R ';
//	cube.back[1][0] = 'R ';
//	cube.back[1][1] = 'R ';
//	cube.back[1][2] = 'R ';
//	cube.back[2][0] = 'R ';
//	cube.back[2][1] = 'R ';
//	cube.back[2][2] = 'R ';
//
//	cube.up[0][0] = 'G';
//	cube.up[0][1] = 'G';
//	cube.up[0][2] = 'G';
//	cube.up[1][0] = 'G';
//	cube.up[1][1] = 'G';
//	cube.up[1][2] = 'G';
//	cube.up[2][0] = 'G';
//	cube.up[2][1] = 'G';
//	cube.up[2][2] = 'G';
//
//	cube.down[0][0] = 'C';
//	cube.down[0][1] = 'C';
//	cube.down[0][2] = 'C';
//	cube.down[1][0] = 'C';
//	cube.down[1][1] = 'C';
//	cube.down[1][2] = 'C';
//	cube.down[2][0] = 'C';
//	cube.down[2][1] = 'C';
//	cube.down[2][2] = 'C';
//
//	cube.left[0][0] = 'Y';
//	cube.left[0][1] = 'Y';
//	cube.left[0][2] = 'Y';
//	cube.left[1][0] = 'Y';
//	cube.left[1][1] = 'Y';
//	cube.left[1][2] = 'Y';
//	cube.left[2][0] = 'Y';
//	cube.left[2][1] = 'Y';
//	cube.left[2][2] = 'Y';
//
//	cube.right[0][0] = 'W';
//	cube.right[0][1] = 'W';
//	cube.right[0][2] = 'W';
//	cube.right[1][0] = 'W';
//	cube.right[1][1] = 'W';
//	cube.right[1][2] = 'W';
//	cube.right[2][0] = 'W';
//	cube.right[2][1] = 'W';
//	cube.right[2][2] = 'W';
//
// 
// 
//	// 큐브 출력
//	printf("Front:\n");
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			printf("%c ", cube.front[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	printf("Back:\n");
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			printf("%c ", cube.back[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	printf("Up:\n");
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			printf("%c ", cube.up[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	printf("Down:\n");
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			printf("%c ", cube.down[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	printf("Left:\n");
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			printf("%c ", cube.left[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	printf("Right:\n");
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			printf("%c ", cube.right[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	return 0;



	//// 출력 결과물
	//	Front:
	//	B B B
	//	B B B
	//	B B B
	//	
	//	Back :
	//	R R R
	//	R R R
	//	R R R
	//	
	//	Up :
	//	G G G
	//	G G G
	//	G G G
	//	
	//	Down :
	//	C C C
	//	C C C
	//	C C C
	//	
	//	Left :
	//	Y Y Y
	//	Y Y Y
	//	Y Y Y
	//	
	//	Right :
	//	W W W
	//	W W W
	//	W W W

