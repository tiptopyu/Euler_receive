
#include <string>
#include <fstream>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

void main()
{
	int arduinoCOM=71;
	HANDLE hComm;
	//シリアルポートを開いてハンドルを取得
	string com = "\\\\.\\COM" + to_string(arduinoCOM);
	hComm = CreateFile(com.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hComm == INVALID_HANDLE_VALUE){
		printf("シリアルポートを開くことができませんでした。");
		char z;
		z = getchar();
		return;
	}
	//ポートを開けていれば通信設定を行う
	else
	{
		DCB lpTest;
		GetCommState(hComm, &lpTest);
		lpTest.BaudRate = 115200;
		lpTest.ByteSize = 8;
		lpTest.Parity = NOPARITY;
		lpTest.StopBits = ONESTOPBIT;
		SetCommState(hComm, &lpTest);
	}
	printf("opened!!\n");


	bool isInitialized = false;
	unsigned char	sendbuf[1];
	unsigned char	receive_data[30] = {};
	int				ret;
	float			DL, DR, DIS, ANG;
	unsigned long	len;
	char *euler_1, *euler_2, *euler_3;
	float Euler[3];
	int i = 0;
	float			droidOrientation[3];
	Sleep(2000);

	while (i<=20)
	{
		i++;

		getchar();
		// ハンドルチェック
		if (!hComm)	return;
		// バッファクリア
		memset(sendbuf, 0x00, sizeof(sendbuf));
		// パケット作成
		sendbuf[0] = (unsigned char)1;
		// 通信バッファクリア
		PurgeComm(hComm, PURGE_RXCLEAR);
		// 送信
		ret = WriteFile(hComm, &sendbuf, 1, &len, NULL);


		// バッファクリア
		memset(receive_data, 0x00, sizeof(receive_data));
		// 通信バッファクリア
		PurgeComm(hComm, PURGE_RXCLEAR);
		// Arduinoからデータを受信
		ret = ReadFile(hComm, &receive_data, 20, &len, NULL);
		//cout << static_cast<bitset<8>>(receive_data[0]) << "," << static_cast<bitset<8>>(receive_data[1] )<< endl;


		//初期化されていなければ初期化(初めのデータを捨てる)
		if (!isInitialized)
		{
			isInitialized = true;
			//return ;
		}
		euler_1 = strtok((char*)receive_data, ",");
		euler_2 = strtok(NULL, ",");
		euler_3 = strtok(NULL, ",");
		//printf("%s\n", receive_data);

		Euler[0] = strtod(euler_1, NULL);
		Euler[1] = strtod(euler_2, NULL);
		Euler[2] = strtod(euler_3, NULL);
		printf("%f\n", Euler[0]);
		printf("%f\n", Euler[1]);
		printf("%f\n", Euler[2]);
	}
}



/*

#include <string>
using namespace std;

int main()
{
	string str;
}*/