
#include <string>
#include <fstream>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;



void Euler_receive(int arduinoCOM, HANDLE hComm, float Euler[3])
{

	double rob_x, rob_y, rob_rad;

	
	//�V���A���|�[�g���J���ăn���h�����擾
	string com = "\\\\.\\COM" + to_string(arduinoCOM);
	hComm = CreateFile(com.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hComm == INVALID_HANDLE_VALUE){
		printf("�V���A���|�[�g���J�����Ƃ��ł��܂���ł����B");
		char z;
		z = getchar();
		return;
	}else
	{
		DCB lpTest;
		GetCommState(hComm, &lpTest);
		lpTest.BaudRate = 115200;
		lpTest.ByteSize = 8;
		lpTest.Parity = NOPARITY;
		lpTest.StopBits = ONESTOPBIT;
		SetCommState(hComm, &lpTest);
	}
	
	bool isInitialized = false;
	unsigned char	sendbuf[1];
	unsigned char	receive_data[30] = {};
	int				ret;
	unsigned long	len;
	char *euler_1, *euler_2, *euler_3;
	int i = 0;
	Sleep(500);

	while (1)
	{
		if (GetAsyncKeyState(VK_SPACE)==1)
		{
			break;
		}

		//getchar();
		// �n���h���`�F�b�N
//		if (!hComm)	return;
		// �o�b�t�@�N���A
		memset(sendbuf, 0x00, sizeof(sendbuf));
		// �p�P�b�g�쐬
		sendbuf[0] = (unsigned char)1;
		// �ʐM�o�b�t�@�N���A
		PurgeComm(hComm, PURGE_RXCLEAR);
		// ���M
		ret = WriteFile(hComm, &sendbuf, 1, &len, NULL);


		// �o�b�t�@�N���A
		memset(receive_data, 0x00, sizeof(receive_data));
		// �ʐM�o�b�t�@�N���A
		PurgeComm(hComm, PURGE_RXCLEAR);
		// Arduino����f�[�^����M
		ret = ReadFile(hComm, &receive_data, 20, &len, NULL);
		//cout << static_cast<bitset<8>>(receive_data[0]) << "," << static_cast<bitset<8>>(receive_data[1] )<< endl;


		//����������Ă��Ȃ���Ώ�����(���߂̃f�[�^���̂Ă�)
		if (!isInitialized)
		{
			isInitialized = true;
			//return ;
		}
		euler_1 = strtok((char*)receive_data, ",");
		euler_2 = strtok(NULL, ",");
		euler_3 = strtok(NULL, ",");
		printf("%s\n", receive_data);

		Euler[0] = strtod(euler_1, NULL);
		Euler[1] = strtod(euler_2, NULL);
		Euler[2] = strtod(euler_3, NULL);

		printf("%f\n", Euler[0]);
		printf("%f\n", Euler[1]);
		printf("%f\n", Euler[2]);
	}
}

void init_arduino(int arduinoCOM, HANDLE hComm, float Euler[3])
{
	string com = "\\\\.\\COM" + to_string(arduinoCOM);
	hComm = CreateFile(com.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hComm == INVALID_HANDLE_VALUE){
		printf("�V���A���|�[�g���J�����Ƃ��ł��܂���ł����B");
		char z;
		z = getchar();
		return;
	}
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
	

}

void main()
{

	
	
	int arduinoCOM=71;
	HANDLE hComm=0;
	float Euler[3], initEuler[3];
	

	printf("init_arduino_in");
	//init_arduino(arduinoCOM, hComm, initEuler);
	
	printf("Euler_receive_in");
	Euler_receive(arduinoCOM, hComm, Euler);


}



/*

#include <string>
using namespace std;

int main()
{
	string str;
}*/