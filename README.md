콘솔 미니게임 프로젝트 : Rubik's Cube

<img width="426" height="240" alt="image" src="https://github.com/user-attachments/assets/66751917-407c-4807-b103-0a52212866a7" />

## 1. 프로젝트 개요
  Rubik's Cube는 C언어 학습을 목표로 제가 처음으로 만들어본 게임입니다.
  콘솔 창 내부에 3D 큐브를 띄우고 실제 루빅스큐브 처럼 큐브를 섞고 맞추는 게임입니다.
  4인 팀 프로젝트로 작업하였고 제가 맡은 역할은 콘솔 창에 3차원 큐브를 투영하는 것이었습니다.

## 2. 기술설명
  ### 2.1 3D 투영
  3차원 큐브를 콘솔창(2D 화면)에 그리기 위해 3D 좌표를 2D로 변환합니다.
콘솔창을 스크린(z = 0인 평면)으로 간주하고 다음 과정을 통해 투영합니다.
  ```c
  // 시점과 3차원상의 좌표를 입력받고 
  // 2차원상의 좌표로 투영합니다.
  COORD ScreenCOORD(Vector3 startPoint, Vector3 endPoint)
  {
  	COORD temp = { 0,0 };
  	Vector3 directionVector; // 방향벡터
  
  	directionVector.x = endPoint.x - startPoint.x;
  	directionVector.y = endPoint.y - startPoint.y;
  	directionVector.z = endPoint.z - startPoint.z;
  
  	// t = 시점, 투사면, 3D 오브젝트간 z거리 비율
  	double t;				
  
  	// 시점벡터z / 방향벡터z
  	t = startPoint.z / directionVector.z;
  
  	temp.X = startPoint.x - directionVector.x * t;
  	temp.Y = startPoint.y - directionVector.y * t;
	  return temp;
  }
  ```
  #### 입력값
  - 시점 좌표 `startPoint`
  - 큐브의 정점 좌표 `endPoint`
  #### 벡터 계산
  - `directionVector` = `endPoint - startPoint`
  #### 거리 비율 계산
  - `t = startPoint.z / directionVector.z`
  #### 2D 좌표로 변환
  - `temp.X = startPoint.x - directionVector.x * t`
  - `temp.Y = startPoint.y - directionVector.y * t`

  ### 2.2 Backface Culling
  큐브의 뒷면을 생략하여 불필요한 연산을 줄이는 기술입니다.이 프로젝트에서는 외적과 내적을 활용하여 구현했습니다.
  ```c
  // 면을 이루는 벡터2개를 추출합니다.
	Vector3 v1Back = MakeVector3D(cubePoint3D[18][1], cubePoint3D[18][0]);
	Vector3 v2Back = MakeVector3D(cubePoint3D[18][1], cubePoint3D[18][5]);
	
	// 면을 이루는 벡터를 외적해서 법선벡터를 만들고 이 값을 
	// 시선벡터와 내적합니다.
	double checkScalar2 = Dot(Cross(v1Back, v2Back), start);
	
	// 내적한 값을 면을 그리는 함수에 반영합니다.
	for (int i = 0;  18 + i <= 26; i++)
	{
		DrawSurface(cubePoint2D[i+18][0], cubePoint2D[i+18][5], cubePoint2D[i+18][1], cubePoint2D[i+18][4], myCube.cubeArr[0][i/3][i%3].color, checkScalar2); //abfe
	```
  ```
    // 면을 그리는 함수입입니다.
    void DrawSurface(COORD startPoint, COORD endPoint, COORD topPoint, COORD bottomPoint, int color, double checkNormal)
    {
  	  // checkNormal값이 0보다 작을경우 면을 그리지 않고 리턴합니다.
	    if (checkNormal < 0)
	    {
    		return;
	    }
	    //...//
    }
    ```
- 한 면을 구성하는 두 벡터를 외적하여 면에 수직한 벡터를 계산합니다.
- 수직 벡터와 시선 벡터를 내적합니다.
- 내적 결과가 0보다 작으면 면이 사용자를 바라보지 않으므로 해당 면을 그리지 않습니다.
<img width="240" height="240" alt="image" src="https://github.com/user-attachments/assets/5902dfb8-bd7f-48d6-b7f2-80c0d45e80f4" /> before <img width="240" height="240" alt="image" src="https://github.com/user-attachments/assets/31e5f8f3-4962-472c-b7b8-b405dc41d712" /> after


### 2.3 면 내부를 채우는 알고리즘
큐브의 각 면을 그리는 과정입니다.
- 사각형의 큐브에서 마주보는 꼭짓점을 startPoint와 endPoint로 두고 startPoint에서 endpoint로의 직선의 방정식을 구합니다.\
	<img width="240" height="160" alt="image" src="https://github.com/user-attachments/assets/a49f8dd1-78f0-411c-a1c7-ef315b63f915" />

- crossPoint라는 점이 직선의 방정식을 따라서 한칸씩 전진합니다.\
	<img width="240" height="160" alt="image" src="https://github.com/user-attachments/assets/6ad55358-64e3-4601-aff0-982db50fbdd3" />

- 이때 한 칸씩 전진하면서 crossPoint로부터 큐브의 마주보는점 bottomPoint, topPoint로 직선의 방정식을 이용해 선을 그리며 면 내부를 채웁니다.\
	<img width="240" height="160" alt="image" src="https://github.com/user-attachments/assets/61fba144-990d-49e3-be35-a4befd959ac1" />


```c
// 하나의 면을 채우는 함수
void DrawSurface(COORD startPoint, COORD endPoint, COORD topPoint, COORD bottomPoint, int color, double checkNormal)
{
	if (checkNormal < 0)
	{
		return;
	}
	// 1. startPoint부터 endPoint까지 직선의 방정식을 구한다.
	double ratioXY;

	// 2. 대각선 꼭짓점의 한 위치가 같을경우 예외처리한다.
	if (startPoint.X == endPoint.X)
	{
		DrawLine(startPoint, endPoint, color);
		return;
	}
	else if (startPoint.Y == endPoint.Y)
	{
		DrawLine(startPoint, endPoint, color);
		return;
	}
	else
	{
		//	3.  기울기를 구한다.
		ratioXY = (startPoint.Y - endPoint.Y) / ((double)startPoint.X - endPoint.X);

	}

	double c = startPoint.Y - (ratioXY * startPoint.X);
	if (startPoint.X < endPoint.X)
	{
		for (double i = startPoint.X; i <= endPoint.X; i++)
		{
			COORD crossPoint = { i , ratioXY * i + c };
			DrawLine(crossPoint, topPoint, color);
			DrawLine(crossPoint, bottomPoint, color);
		}
	}
	else if (endPoint.X < startPoint.X)
	{
		for (double i = endPoint.X; i <= startPoint.X; i++)
		{
			COORD crossPoint = { i, ratioXY * (i)+c };
			DrawLine(crossPoint, topPoint, color);
			DrawLine(crossPoint, bottomPoint, color);
		}
	}
}
```
  
