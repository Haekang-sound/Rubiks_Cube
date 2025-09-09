#include "Cube.h"

void SettingValueCube(Cube* cube)
{
	int colors[6] = { 1, 5, 10, 12, 6, 11 };	//{BLUE,Purple,GREEN,red,YELLOW,CYAN} 
	for (int i = 0; i < 6; i++)					// "FRONT","LEFT","BACK","RIGHT","UP","DOWN"
	{											
		int curColor = colors[i];
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cube->cubeArr[i][j][k].color = curColor;
			}
		}
	}
}

// void PrintCube(Cube* cube)
// {
// 	const char* CubeFace[] = { "FRONT","LEFT","BACK","RIGHT","UP","DOWN" };
// 	for (int i = 0; i < 6; i++)
// 	{
// 		printf("%s", CubeFace[i]);
// 		printf("\n");
// 		for (int j = 0; j < 3; j++)
// 		{
// 			for (int k = 0; k < 3; k++)
// 			{
// 				printf("%d", cube->cubeArr[i][j][k].color);
// 			}
// 			printf("\n");
// 		}
// 		printf("\n");
// 	}
// }

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