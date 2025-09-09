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

void RotateCube(Cube* cube, char p)	//p�� �Է��� Ű
{
	int temp[20];
	for (int i = 0; i <= 19; i++)
	{
		temp[i] = 0;
	}
	//M - LEFT ���� ���� �������� �ݽð�������� 90�� ȸ��	
	if (p == 'm') {
		//for (int i = 0; i < MAX_PSEUDOQUEUE_SIZE; i++)
		//{
		// call by reference �õ�
		//	int temp1, temp2, temp3;
		//	temp1 = PseudoDeque.dataMZ[0];		//�ڷ����� �´µ� ����� �ȵ�. ����ü�� ���� �׷��ŷ�
		//	temp2 = PseudoDeque.dataMZ[1];		
		//	temp3 = PseudoDeque.dataMZ[2];		
		//	if (i + 3 >= 12) PseudoDeque.dataMZ[i % 3] == PseudoDeque.dataMZ[i + 3];
		//	else PseudoDeque.dataMZ[i + 3] = PseudoDeque.dataMZ[i];
		//	�翬�� �Ǿ�� �� ���� �ȵǴϱ� ��¿ �� ���� �ϵ��ڵ�
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
		cube->cubeArr[1][0][0].color = temp[3];	 //0��
		cube->cubeArr[1][1][0].color = temp[4];	 //1��
		cube->cubeArr[1][2][0].color = temp[5];	 //2��
		cube->cubeArr[5][0][2].color = temp[6];	 //3��
		cube->cubeArr[5][0][1].color = temp[7];	 //4��
		cube->cubeArr[5][0][0].color = temp[8];	 //5��
		cube->cubeArr[3][2][2].color = temp[9];	 //6��
		cube->cubeArr[3][1][2].color = temp[10];	 //7��
		cube->cubeArr[3][0][2].color = temp[11];	 //8��
		cube->cubeArr[4][2][0].color = temp[0];							 //9��
		cube->cubeArr[4][2][1].color = temp[1];							 //10��
		cube->cubeArr[4][2][2].color = temp[2];							 //11��

		//������: FRONT�鵵 ���ư���.
		temp[12] = cube->cubeArr[0][0][0].color;
		temp[13] = cube->cubeArr[0][1][0].color;
		temp[14] = cube->cubeArr[0][2][0].color;
		temp[15] = cube->cubeArr[0][2][1].color;
		temp[16] = cube->cubeArr[0][2][2].color;
		temp[17] = cube->cubeArr[0][1][2].color;
		temp[18] = cube->cubeArr[0][0][2].color;
		temp[19] = cube->cubeArr[0][0][1].color;

		cube->cubeArr[0][0][0].color = temp[18];	 //0���� ���� ���ư���
		cube->cubeArr[0][1][0].color = temp[19];	 //1���� ���� ���ư���
		cube->cubeArr[0][2][0].color = temp[12];	 //2���� ���� ���ư���
		cube->cubeArr[0][2][1].color = temp[13];	 //4���� ���� ���ư���
		cube->cubeArr[0][2][2].color = temp[14];	 //5���� ���� ���ư���
		cube->cubeArr[0][1][2].color = temp[15];	 //7���� ���� ���ư���
		cube->cubeArr[0][0][2].color = temp[16];	 //8���� ���� ���ư���
		cube->cubeArr[0][0][1].color = temp[17];	 //10���� ���� ���ư���		
	}
	//Z -  LEFT ���� ���� �������� �ð�������� 90�� ȸ��	
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

		cube->cubeArr[1][0][0].color = temp[3];	//0��
		cube->cubeArr[1][1][0].color = temp[4];	//1��
		cube->cubeArr[1][2][0].color = temp[5];	//2��
		cube->cubeArr[4][2][0].color = temp[6];	//9��
		cube->cubeArr[4][2][1].color = temp[7];	//10��
		cube->cubeArr[4][2][2].color = temp[8];	//11��
		cube->cubeArr[3][2][2].color = temp[9];	//6��
		cube->cubeArr[3][1][2].color = temp[10];	//7��
		cube->cubeArr[3][0][2].color = temp[11];	//8��
		cube->cubeArr[5][0][2].color = temp[0];		//3��
		cube->cubeArr[5][0][1].color = temp[1];		//4��
		cube->cubeArr[5][0][0].color = temp[2];		//5��

		//������: FRONT�鵵 ���ư���.
		temp[12] = cube->cubeArr[0][0][0].color;
		temp[13] = cube->cubeArr[0][0][1].color;
		temp[14] = cube->cubeArr[0][0][2].color;
		temp[15] = cube->cubeArr[0][1][2].color;
		temp[16] = cube->cubeArr[0][2][2].color;
		temp[17] = cube->cubeArr[0][2][1].color;
		temp[18] = cube->cubeArr[0][2][0].color;
		temp[19] = cube->cubeArr[0][1][0].color;


		cube->cubeArr[0][0][0].color = temp[18];	 //0���� ���� ���ư���
		cube->cubeArr[0][0][1].color = temp[19];	 //1���� ���� ���ư���
		cube->cubeArr[0][0][2].color = temp[12];	 //2���� ���� ���ư���
		cube->cubeArr[0][1][2].color = temp[13];		 //9���� ���� ���ư���
		cube->cubeArr[0][2][2].color = temp[14];	 //10���� ���� ���ư���
		cube->cubeArr[0][2][1].color = temp[15];	 //6���� ���� ���ư���
		cube->cubeArr[0][2][0].color = temp[16];	 //7���� ���� ���ư���
		cube->cubeArr[0][1][0].color = temp[17];	 //4���� ���� ���ư���
	}
	///--------------------------------------------------


	//K - LEFT ���� ��� �������� �ݽð�������� 90�� ȸ��	
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



		cube->cubeArr[1][0][1].color = temp[3];	  //0��
		cube->cubeArr[1][1][1].color = temp[4];	  //1��
		cube->cubeArr[1][2][1].color = temp[5];	  //2��
		cube->cubeArr[5][1][2].color = temp[6];	  //3��
		cube->cubeArr[5][1][1].color = temp[7];	  //4��
		cube->cubeArr[5][1][0].color = temp[8];	  //5��
		cube->cubeArr[3][2][1].color = temp[9];	  //6��
		cube->cubeArr[3][1][1].color = temp[10];	  //7��
		cube->cubeArr[3][0][1].color = temp[11];	  //8��
		cube->cubeArr[4][1][0].color = temp[0];							  //9��
		cube->cubeArr[4][1][1].color = temp[1];							  //10��
		cube->cubeArr[4][1][2].color = temp[2];							  //11��
	}
	//A - LEFT ���� ��� �������� �ݽð�������� 90�� ȸ��
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

		cube->cubeArr[1][0][1].color = temp[3];	  //0��
		cube->cubeArr[1][1][1].color = temp[4];	  //1��
		cube->cubeArr[1][2][1].color = temp[5];	  //2��
		cube->cubeArr[4][1][0].color = temp[6];	  //9��
		cube->cubeArr[4][1][1].color = temp[7];	  //10��
		cube->cubeArr[4][1][2].color = temp[8];	  //11��
		cube->cubeArr[3][2][1].color = temp[9];	  //6��
		cube->cubeArr[3][1][1].color = temp[10];	  //7��
		cube->cubeArr[3][0][1].color = temp[11];	  //8��
		cube->cubeArr[5][1][2].color = temp[0];							  //3��
		cube->cubeArr[5][1][1].color = temp[1];							  //4��
		cube->cubeArr[5][1][0].color = temp[2];							  //5��
	}

	///------------------------------------------------

	//O - LEFT ���� ������ �������� �ݽð�������� 90�� ȸ��	
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

		cube->cubeArr[1][0][2].color = temp[3];	   //0��
		cube->cubeArr[1][1][2].color = temp[4];	   //1��
		cube->cubeArr[1][2][2].color = temp[5];	   //2��
		cube->cubeArr[5][2][2].color = temp[6];	   //3��
		cube->cubeArr[5][2][1].color = temp[7];	   //4��
		cube->cubeArr[5][2][0].color = temp[8];	   //5��
		cube->cubeArr[3][2][0].color = temp[9];	   //6��
		cube->cubeArr[3][1][0].color = temp[10];	   //7��
		cube->cubeArr[3][0][0].color = temp[11];	   //8��
		cube->cubeArr[4][0][0].color = temp[0];							   //9��
		cube->cubeArr[4][0][1].color = temp[1];							   //10��
		cube->cubeArr[4][0][2].color = temp[2];							   //11��

		//������: BACK�鵵 ���ư���.
		temp[12] = cube->cubeArr[2][0][0].color;
		temp[13] = cube->cubeArr[2][0][1].color;
		temp[14] = cube->cubeArr[2][0][2].color;
		temp[15] = cube->cubeArr[2][1][2].color;
		temp[16] = cube->cubeArr[2][2][2].color;
		temp[17] = cube->cubeArr[2][2][1].color;
		temp[18] = cube->cubeArr[2][2][0].color;
		temp[19] = cube->cubeArr[2][1][0].color;

		cube->cubeArr[2][0][0].color = temp[18];	 //0���� ���� ���ư���
		cube->cubeArr[2][0][1].color = temp[19];	 //1���� ���� ���ư���
		cube->cubeArr[2][0][2].color = temp[12];	 //2���� ���� ���ư���
		cube->cubeArr[2][1][2].color = temp[13];	 //3���� ���� ���ư���
		cube->cubeArr[2][2][2].color = temp[14];	 //4���� ���� ���ư���
		cube->cubeArr[2][2][1].color = temp[15];	 //5���� ���� ���ư���
		cube->cubeArr[2][2][0].color = temp[16];	 //6���� ���� ���ư���
		cube->cubeArr[2][1][0].color = temp[17];	 //7���� ���� ���ư���

	}
	//--------------------------------------------

	//Q - LEFT ���� ������ �������� �ð�������� 90�� ȸ��	
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

		cube->cubeArr[1][0][2].color = temp[3];	  //0��
		cube->cubeArr[1][1][2].color = temp[4];	  //1��
		cube->cubeArr[1][2][2].color = temp[5];	  //2��
		cube->cubeArr[4][0][0].color = temp[6];	  //9��
		cube->cubeArr[4][0][1].color = temp[7];	  //10��
		cube->cubeArr[4][0][2].color = temp[8];	  //11��
		cube->cubeArr[3][2][0].color = temp[9];	  //6��
		cube->cubeArr[3][1][0].color = temp[10];	  //7��
		cube->cubeArr[3][0][0].color = temp[11];	  //8��
		cube->cubeArr[5][2][2].color = temp[0];							  //3��
		cube->cubeArr[5][2][1].color = temp[1];							  //4��
		cube->cubeArr[5][2][0].color = temp[2];							  //5��

		//������: BACK�鵵 ���ư���.
		temp[12] = cube->cubeArr[2][0][0].color;
		temp[13] = cube->cubeArr[2][1][0].color;
		temp[14] = cube->cubeArr[2][2][0].color;
		temp[15] = cube->cubeArr[2][2][1].color;
		temp[16] = cube->cubeArr[2][2][2].color;
		temp[17] = cube->cubeArr[2][1][2].color;
		temp[18] = cube->cubeArr[2][0][2].color;
		temp[19] = cube->cubeArr[2][0][1].color;

		cube->cubeArr[2][0][0].color = temp[18];	 //0���� ���� ���ư���
		cube->cubeArr[2][1][0].color = temp[19];	 //1���� ���� ���ư���
		cube->cubeArr[2][2][0].color = temp[12];	 //2���� ���� ���ư���
		cube->cubeArr[2][2][1].color = temp[13];	 //9���� ���� ���ư���
		cube->cubeArr[2][2][2].color = temp[14];	 //10���� ���� ���ư���
		cube->cubeArr[2][1][2].color = temp[15];	 //11���� ���� ���ư���
		cube->cubeArr[2][0][2].color = temp[16];	 //6���� ���� ���ư���
		cube->cubeArr[2][0][1].color = temp[17];	 //7���� ���� ���ư���

	}
	///--------------------------------------
	//W - UP ���� ���� �������� �������� 90�� ȸ��	
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

		cube->cubeArr[4][0][0].color = temp[3];		//0��
		cube->cubeArr[4][1][0].color = temp[4];		//1��
		cube->cubeArr[4][2][0].color = temp[5];		//2��
		cube->cubeArr[0][0][0].color = temp[6];		//3��
		cube->cubeArr[0][1][0].color = temp[7];		//4��
		cube->cubeArr[0][2][0].color = temp[8];		//5��
		cube->cubeArr[5][0][0].color = temp[9];		//6��
		cube->cubeArr[5][1][0].color = temp[10];		//7��
		cube->cubeArr[5][2][0].color = temp[11];		//8��
		cube->cubeArr[2][2][2].color = temp[0];								//9��
		cube->cubeArr[2][1][2].color = temp[1];								//10��
		cube->cubeArr[2][0][2].color = temp[2];								//11��

		//-----------------------
		//������: RIGHT�鵵 ���ư���.
		temp[12] = cube->cubeArr[3][0][0].color;
		temp[13] = cube->cubeArr[3][1][0].color;
		temp[14] = cube->cubeArr[3][2][0].color;
		temp[15] = cube->cubeArr[3][2][1].color;
		temp[16] = cube->cubeArr[3][2][2].color;
		temp[17] = cube->cubeArr[3][1][2].color;
		temp[18] = cube->cubeArr[3][0][2].color;
		temp[19] = cube->cubeArr[3][0][1].color;


		cube->cubeArr[3][0][0].color = temp[18];	 //0���� ���� ���ư���
		cube->cubeArr[3][1][0].color = temp[19];	 //1���� ���� ���ư���
		cube->cubeArr[3][2][0].color = temp[12];	 //2���� ���� ���ư���
		cube->cubeArr[3][2][1].color = temp[13];	 //3���� ���� ���ư���
		cube->cubeArr[3][2][2].color = temp[14];	 //4���� ���� ���ư���
		cube->cubeArr[3][1][2].color = temp[15];	 //5���� ���� ���ư���
		cube->cubeArr[3][0][2].color = temp[16];	 //6���� ���� ���ư���
		cube->cubeArr[3][0][1].color = temp[17];	 //7���� ���� ���ư���

	}
	///------------------------------------------------- 

	//S - UP ���� ���� �������� �������� 90�� ȸ��.

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

		cube->cubeArr[4][0][0].color = temp[3];		//0��
		cube->cubeArr[4][1][0].color = temp[4];		//1��
		cube->cubeArr[4][2][0].color = temp[5];		//2��
		cube->cubeArr[2][2][2].color = temp[6];		//9��
		cube->cubeArr[2][1][2].color = temp[7];		//10��
		cube->cubeArr[2][0][2].color = temp[8];		//11��
		cube->cubeArr[5][0][0].color = temp[9];		//6��
		cube->cubeArr[5][1][0].color = temp[10];		//7��
		cube->cubeArr[5][2][0].color = temp[11];		//8��
		cube->cubeArr[0][0][0].color = temp[0];								//3��
		cube->cubeArr[0][1][0].color = temp[1];								//4��
		cube->cubeArr[0][2][0].color = temp[2];								//5��

		//-------------------------------------------
		//������: RIGHT�鵵 ���ư���
		temp[12] = cube->cubeArr[3][0][0].color;
		temp[13] = cube->cubeArr[3][0][1].color;
		temp[14] = cube->cubeArr[3][0][2].color;
		temp[15] = cube->cubeArr[3][1][2].color;
		temp[16] = cube->cubeArr[3][2][2].color;
		temp[17] = cube->cubeArr[3][2][1].color;
		temp[18] = cube->cubeArr[3][2][0].color;
		temp[19] = cube->cubeArr[3][1][0].color;


		cube->cubeArr[3][0][0].color = temp[18];	 //0���� ���� ���ư���
		cube->cubeArr[3][0][1].color = temp[19];	 //1���� ���� ���ư���
		cube->cubeArr[3][0][2].color = temp[12];	 //2���� ���� ���ư���
		cube->cubeArr[3][1][2].color = temp[13];	 //9���� ���� ���ư���
		cube->cubeArr[3][2][2].color = temp[14];	 //10���� ���� ���ư���
		cube->cubeArr[3][2][1].color = temp[15];	 //11���� ���� ���ư���
		cube->cubeArr[3][2][0].color = temp[16];	 //6���� ���� ���ư���
		cube->cubeArr[3][1][0].color = temp[17];	 //7���� ���� ���ư���

	}

	///------------------------------------------------------

	//E - UP ���� ��� �������� �������� 90�� ȸ��	
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


		cube->cubeArr[4][0][1].color = temp[3];		//0��
		cube->cubeArr[4][1][1].color = temp[4];		//1��
		cube->cubeArr[4][2][1].color = temp[5];		//2��
		cube->cubeArr[0][0][1].color = temp[6];		//3��
		cube->cubeArr[0][1][1].color = temp[7];		//4��
		cube->cubeArr[0][2][1].color = temp[8];		//5��
		cube->cubeArr[5][0][1].color = temp[9];		//6��
		cube->cubeArr[5][1][1].color = temp[10];		//7��
		cube->cubeArr[5][2][1].color = temp[11];		//8��
		cube->cubeArr[2][2][1].color = temp[0];								//9��
		cube->cubeArr[2][1][1].color = temp[1];								//10��
		cube->cubeArr[2][0][1].color = temp[2];								//11��
	}
	//D - UP ���� ��� �������� �������� 90�� ȸ��
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

		cube->cubeArr[4][0][1].color = temp[3];		//0��
		cube->cubeArr[4][1][1].color = temp[4];		//1��
		cube->cubeArr[4][2][1].color = temp[5];		//2��
		cube->cubeArr[2][2][1].color = temp[6];		//9��
		cube->cubeArr[2][1][1].color = temp[7];		//10��
		cube->cubeArr[2][0][1].color = temp[8];		//11��
		cube->cubeArr[5][0][1].color = temp[9];		//6��
		cube->cubeArr[5][1][1].color = temp[10];		//7��
		cube->cubeArr[5][2][1].color = temp[11];		//8��
		cube->cubeArr[0][0][1].color = temp[0];								//3��
		cube->cubeArr[0][1][1].color = temp[1];								//4��
		cube->cubeArr[0][2][1].color = temp[2];								//5��
	}
	///------------------------------------------------

	//R - UP ���� ������ �������� �������� 90�� ȸ��

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

		cube->cubeArr[4][0][2].color = temp[3];		//0��
		cube->cubeArr[4][1][2].color = temp[4];		//1��
		cube->cubeArr[4][2][2].color = temp[5];		//2��
		cube->cubeArr[0][0][2].color = temp[6];		//3��
		cube->cubeArr[0][1][2].color = temp[7];		//4��
		cube->cubeArr[0][2][2].color = temp[8];		//5��
		cube->cubeArr[5][0][2].color = temp[9];		//6��
		cube->cubeArr[5][1][2].color = temp[10];		//7��
		cube->cubeArr[5][2][2].color = temp[11];		//8��
		cube->cubeArr[2][2][0].color = temp[0];								//9��
		cube->cubeArr[2][1][0].color = temp[1];								//10��
		cube->cubeArr[2][0][0].color = temp[2];								//11��
		//----------------------------------
		//������: LEFT�鵵 ���ư���
		temp[12] = cube->cubeArr[1][0][0].color;
		temp[13] = cube->cubeArr[1][0][1].color;
		temp[14] = cube->cubeArr[1][0][2].color;
		temp[15] = cube->cubeArr[1][1][2].color;
		temp[16] = cube->cubeArr[1][2][2].color;
		temp[17] = cube->cubeArr[1][2][1].color;
		temp[18] = cube->cubeArr[1][2][0].color;
		temp[19] = cube->cubeArr[1][1][0].color;


		cube->cubeArr[1][0][0].color = temp[18];	  //0���� ���� ���ư���
		cube->cubeArr[1][0][1].color = temp[19];	  //1���� ���� ���ư���
		cube->cubeArr[1][0][2].color = temp[12];	  //2���� ���� ���ư���
		cube->cubeArr[1][1][2].color = temp[13];	  //3���� ���� ���ư���
		cube->cubeArr[1][2][2].color = temp[14];	  //4���� ���� ���ư���
		cube->cubeArr[1][2][1].color = temp[15];	  //5���� ���� ���ư���
		cube->cubeArr[1][2][0].color = temp[16];	  //6���� ���� ���ư���
		cube->cubeArr[1][1][0].color = temp[17];	  //7���� ���� ���ư���

	}

	///-----------------------------------------------------
	//F - UP ���� ������ �������� �������� 90�� ȸ��	
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

		cube->cubeArr[4][0][2].color = temp[3];		//0��
		cube->cubeArr[4][1][2].color = temp[4];		//1��
		cube->cubeArr[4][2][2].color = temp[5];		//2��
		cube->cubeArr[2][2][0].color = temp[6];		//9��
		cube->cubeArr[2][1][0].color = temp[7];		//10��
		cube->cubeArr[2][0][0].color = temp[8];		//11��
		cube->cubeArr[5][0][2].color = temp[9];		//6��
		cube->cubeArr[5][1][2].color = temp[10];		//7��
		cube->cubeArr[5][2][2].color = temp[11];		//8��
		cube->cubeArr[0][0][2].color = temp[0];								//3��
		cube->cubeArr[0][1][2].color = temp[1];								//4��
		cube->cubeArr[0][2][2].color = temp[2];								//5��
		//----------------------------
		//������: LEFT�鵵 ���ư���
		temp[12] = cube->cubeArr[1][0][0].color;
		temp[13] = cube->cubeArr[1][1][0].color;
		temp[14] = cube->cubeArr[1][2][0].color;
		temp[15] = cube->cubeArr[1][2][1].color;
		temp[16] = cube->cubeArr[1][2][2].color;
		temp[17] = cube->cubeArr[1][1][2].color;
		temp[18] = cube->cubeArr[1][0][2].color;
		temp[19] = cube->cubeArr[1][0][1].color;

		cube->cubeArr[1][0][0].color = temp[18];	 //0���� ���� ���ư���
		cube->cubeArr[1][1][0].color = temp[19];	 //1���� ���� ���ư���
		cube->cubeArr[1][2][0].color = temp[12];	 //2���� ���� ���ư���
		cube->cubeArr[1][2][1].color = temp[13];	 //9���� ���� ���ư���
		cube->cubeArr[1][2][2].color = temp[14];	 //10���� ���� ���ư���
		cube->cubeArr[1][1][2].color = temp[15];	 //11���� ���� ���ư���
		cube->cubeArr[1][0][2].color = temp[16];	 //6���� ���� ���ư���
		cube->cubeArr[1][0][1].color = temp[17];	 //7���� ���� ���ư���

	}
	///--------------------------------------------------------------------------
	//G - FRONT ���� ���� �������� �ݽð� �������� 90�� ȸ��		
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

		cube->cubeArr[0][0][0].color = temp[3];		//0��
		cube->cubeArr[0][0][1].color = temp[4];		//1��
		cube->cubeArr[0][0][2].color = temp[5];		//2��
		cube->cubeArr[3][0][0].color = temp[6];		//9��
		cube->cubeArr[3][0][1].color = temp[7];		//10��
		cube->cubeArr[3][0][2].color = temp[8];		//11��
		cube->cubeArr[2][0][0].color = temp[9];		//6��
		cube->cubeArr[2][0][1].color = temp[10];		//7��
		cube->cubeArr[2][0][2].color = temp[11];		//8��
		cube->cubeArr[1][0][0].color = temp[0];								//3��
		cube->cubeArr[1][0][1].color = temp[1];								//4��
		cube->cubeArr[1][0][2].color = temp[2];								//5��
		//----------------------------------
		//������: UP�鵵 ���ư���
		temp[12] = cube->cubeArr[4][0][0].color;
		temp[13] = cube->cubeArr[4][1][0].color;
		temp[14] = cube->cubeArr[4][2][0].color;
		temp[15] = cube->cubeArr[4][2][1].color;
		temp[16] = cube->cubeArr[4][2][2].color;
		temp[17] = cube->cubeArr[4][1][2].color;
		temp[18] = cube->cubeArr[4][0][2].color;
		temp[19] = cube->cubeArr[4][0][1].color;


		cube->cubeArr[4][0][0].color = temp[18];	 //0���� ���� ���ư���
		cube->cubeArr[4][1][0].color = temp[19];	 //1���� ���� ���ư���
		cube->cubeArr[4][2][0].color = temp[12];	 //2���� ���� ���ư���
		cube->cubeArr[4][2][1].color = temp[13];	 //9���� ���� ���ư���
		cube->cubeArr[4][2][2].color = temp[14];	 //10���� ���� ���ư���
		cube->cubeArr[4][1][2].color = temp[15];	 //11���� ���� ���ư���
		cube->cubeArr[4][0][2].color = temp[16];	 //6���� ���� ���ư���
		cube->cubeArr[4][0][1].color = temp[17];	 //7���� ���� ���ư���

	}
	///--------------------------------------------------------------
	//T - FRONT ���� ���� �������� �ð� �������� 90�� ȸ��	
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

		cube->cubeArr[0][0][0].color = temp[3];		//0��
		cube->cubeArr[0][0][1].color = temp[4];		//1��
		cube->cubeArr[0][0][2].color = temp[5];		//2��
		cube->cubeArr[1][0][0].color = temp[6];		//3��
		cube->cubeArr[1][0][1].color = temp[7];		//4��
		cube->cubeArr[1][0][2].color = temp[8];		//5��
		cube->cubeArr[2][0][0].color = temp[9];		//6��
		cube->cubeArr[2][0][1].color = temp[10];		//7��
		cube->cubeArr[2][0][2].color = temp[11];		//8��
		cube->cubeArr[3][0][0].color = temp[0];								//9��
		cube->cubeArr[3][0][1].color = temp[1];								//10��
		cube->cubeArr[3][0][2].color = temp[2];								//11��
		//--------------------------------------
		//������: UP�鵵 ���ư���
		temp[12] = cube->cubeArr[4][0][0].color;
		temp[13] = cube->cubeArr[4][0][1].color;
		temp[14] = cube->cubeArr[4][0][2].color;
		temp[15] = cube->cubeArr[4][1][2].color;
		temp[16] = cube->cubeArr[4][2][2].color;
		temp[17] = cube->cubeArr[4][2][1].color;
		temp[18] = cube->cubeArr[4][2][0].color;
		temp[19] = cube->cubeArr[4][1][0].color;

		cube->cubeArr[4][0][0].color = temp[18];	  //0���� ���� ���ư���
		cube->cubeArr[4][0][1].color = temp[19];	  //1���� ���� ���ư���
		cube->cubeArr[4][0][2].color = temp[12];	  //2���� ���� ���ư���
		cube->cubeArr[4][1][2].color = temp[13];	  //3���� ���� ���ư���
		cube->cubeArr[4][2][2].color = temp[14];	  //4���� ���� ���ư���
		cube->cubeArr[4][2][1].color = temp[15];	  //5���� ���� ���ư���
		cube->cubeArr[4][2][0].color = temp[16];	  //6���� ���� ���ư���
		cube->cubeArr[4][1][0].color = temp[17];	  //7���� ���� ���ư���
	}
	///------------------------------------------------------------
	//H - FRONT ���� ��� �������� �ݽð� �������� 90�� ȸ��	
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

		cube->cubeArr[0][1][0].color = temp[3];		//0��
		cube->cubeArr[0][1][1].color = temp[4];		//1��
		cube->cubeArr[0][1][2].color = temp[5];		//2��
		cube->cubeArr[3][1][0].color = temp[6];		//9��
		cube->cubeArr[3][1][1].color = temp[7];		//10��
		cube->cubeArr[3][1][2].color = temp[8];		//11��
		cube->cubeArr[2][1][0].color = temp[9];		//6��
		cube->cubeArr[2][1][1].color = temp[10];		//7��
		cube->cubeArr[2][1][2].color = temp[11];		//8��
		cube->cubeArr[1][1][0].color = temp[0];								//3��
		cube->cubeArr[1][1][1].color = temp[1];								//4��
		cube->cubeArr[1][1][2].color = temp[2];								//5��
	}
	//Y - FRONT ���� ��� �������� �ð� �������� 90�� ȸ��
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

		cube->cubeArr[0][1][0].color = temp[3];		//0��		
		cube->cubeArr[0][1][1].color = temp[4];		//1��		
		cube->cubeArr[0][1][2].color = temp[5];		//2��		
		cube->cubeArr[1][1][0].color = temp[6];		//3��		
		cube->cubeArr[1][1][1].color = temp[7];		//4��		
		cube->cubeArr[1][1][2].color = temp[8];		//5��		
		cube->cubeArr[2][1][0].color = temp[9];		//6��		
		cube->cubeArr[2][1][1].color = temp[10];		//7��		
		cube->cubeArr[2][1][2].color = temp[11];		//8��		
		cube->cubeArr[3][1][0].color = temp[0];								//9��		
		cube->cubeArr[3][1][1].color = temp[1];								//10��		
		cube->cubeArr[3][1][2].color = temp[2];								//11��		
	}
	///----------------------------------------------------------
	//J - FRONT ���� �Ʒ��� �������� �ݽð� �������� 90�� ȸ��		
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

		cube->cubeArr[0][2][0].color = temp[3];		//0��
		cube->cubeArr[0][2][1].color = temp[4];		//1��
		cube->cubeArr[0][2][2].color = temp[5];		//2��
		cube->cubeArr[3][2][0].color = temp[6];		//9��
		cube->cubeArr[3][2][1].color = temp[7];		//10��
		cube->cubeArr[3][2][2].color = temp[8];		//11��
		cube->cubeArr[2][2][0].color = temp[9];		//6��
		cube->cubeArr[2][2][1].color = temp[10];		//7��
		cube->cubeArr[2][2][2].color = temp[11];		//8��
		cube->cubeArr[1][2][0].color = temp[0];								//3��
		cube->cubeArr[1][2][1].color = temp[1];								//4��
		cube->cubeArr[1][2][2].color = temp[2];								//5��
		//-----------------------------------------
		//������: DOWN�鵵 ���ư���
		temp[12] = cube->cubeArr[5][0][0].color;
		temp[13] = cube->cubeArr[5][0][1].color;
		temp[14] = cube->cubeArr[5][0][2].color;
		temp[15] = cube->cubeArr[5][1][2].color;
		temp[16] = cube->cubeArr[5][2][2].color;
		temp[17] = cube->cubeArr[5][2][1].color;
		temp[18] = cube->cubeArr[5][2][0].color;
		temp[19] = cube->cubeArr[5][1][0].color;

		cube->cubeArr[5][0][0].color = temp[18];	 //0���� ���� ���ư���
		cube->cubeArr[5][0][1].color = temp[19];	 //1���� ���� ���ư���
		cube->cubeArr[5][0][2].color = temp[12];	 //2���� ���� ���ư���
		cube->cubeArr[5][1][2].color = temp[13];	 //9���� ���� ���ư���
		cube->cubeArr[5][2][2].color = temp[14];	 //10���� ���� ���ư���
		cube->cubeArr[5][2][1].color = temp[15];	 //11���� ���� ���ư���
		cube->cubeArr[5][2][0].color = temp[16];	 //6���� ���� ���ư���
		cube->cubeArr[5][1][0].color = temp[17];	 //7���� ���� ���ư���

	}
	///---------------------------------------------------�������
	//U - FRONT ���� �Ʒ��� �������� �ð� �������� 90�� ȸ��	
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

		cube->cubeArr[0][2][0].color = temp[3];		//0��	
		cube->cubeArr[0][2][1].color = temp[4];		//1��	
		cube->cubeArr[0][2][2].color = temp[5];		//2��	
		cube->cubeArr[1][2][0].color = temp[6];		//3��	
		cube->cubeArr[1][2][1].color = temp[7];		//4��	
		cube->cubeArr[1][2][2].color = temp[8];		//5��	
		cube->cubeArr[2][2][0].color = temp[9];		//6��	
		cube->cubeArr[2][2][1].color = temp[10];		//7��	
		cube->cubeArr[2][2][2].color = temp[11];		//8��	
		cube->cubeArr[3][2][0].color = temp[0];								//9��	
		cube->cubeArr[3][2][1].color = temp[1];								//10��	
		cube->cubeArr[3][2][2].color = temp[2];								//11��	

		////������: DOWN�鵵 ���ư���
		temp[12] = cube->cubeArr[5][0][0].color;
		temp[13] = cube->cubeArr[5][1][0].color;
		temp[14] = cube->cubeArr[5][2][0].color;
		temp[15] = cube->cubeArr[5][2][1].color;
		temp[16] = cube->cubeArr[5][2][2].color;
		temp[17] = cube->cubeArr[5][1][2].color;
		temp[18] = cube->cubeArr[5][0][2].color;
		temp[19] = cube->cubeArr[5][0][1].color;

		cube->cubeArr[5][0][0].color = temp[18];	  //0���� ���� ���ư���
		cube->cubeArr[5][1][0].color = temp[19];	  //1���� ���� ���ư���
		cube->cubeArr[5][2][0].color = temp[12];	  //2���� ���� ���ư���
		cube->cubeArr[5][2][1].color = temp[13];	  //3���� ���� ���ư���
		cube->cubeArr[5][2][2].color = temp[14];	  //4���� ���� ���ư���
		cube->cubeArr[5][1][2].color = temp[15];	  //5���� ���� ���ư���
		cube->cubeArr[5][0][2].color = temp[16];	  //6���� ���� ���ư���
		cube->cubeArr[5][0][1].color = temp[17];	  //7���� ���� ���ư���		
	}
}