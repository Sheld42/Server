#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "ShellAPI.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
wchar_t *convertCharArrayToLPCWSTR(const char* charArray);

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define SOCKET_OK 0

int main()
{
	cout << "This is SERVER and server is litle slave which belong to klient";
	WORD sockVer;
	WSADATA wsaData;
	int retVal;

	sockVer = MAKEWORD(2,2);

	WSAStartup(sockVer, &wsaData);

	/// Creating socket
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(servSock == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		//  MessageBox(NULL, L"Unable to create socket()", L"SOCKET ERROR", MB_OK);
		WSACleanup();
		return SOCKET_ERROR;
	}

	/// Filling in sockaddr_in struct 

	SOCKADDR_IN sin;
	sin.sin_family = PF_INET;
	sin.sin_port = htons(1111);
	sin.sin_addr.s_addr = INADDR_ANY;

	retVal = bind(servSock, (LPSOCKADDR)&sin, sizeof(sin));
	if(retVal == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		// MessageBox(NULL, L"Unable to bind", L"SOCKET ERROR", MB_OK);
		WSACleanup();
		return SOCKET_ERROR;
	}

	/// Trying to listen socket
	retVal = listen(servSock, 10);
	if(retVal == SOCKET_ERROR)
	{
		//  MessageBox(NULL, L"Unable to listen()", L"SOCKET ERROR", MB_OK);
		printf("listen failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return SOCKET_ERROR;
	}

	/// Waiting for a client
	SOCKET clientSock;

	clientSock = accept(servSock, NULL, NULL);

	if(clientSock == INVALID_SOCKET)
	{
		//MessageBox(NULL, L"Unable to accept()", L"SOCKET ERROR", MB_OK);
		printf("accept failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return SOCKET_ERROR;
	}

	char szReq[512]; 
	retVal = recv(clientSock, szReq, 512, 0);
	szReq[retVal]='\0';
	cout << szReq << endl;

	if(retVal == SOCKET_ERROR)
	{
		//  MessageBox(NULL, L"Unable to recv()", L"SOCKET ERROR", MB_OK);
		printf("Unable to recv() with error: %d\n", WSAGetLastError());
		return SOCKET_ERROR;
	}


	// MessageBox(NULL, L"SOMETHING THAT I KANT", L"Got the request from client", MB_OK);
	printf("Seichas bahny eto zapisivat'\n");
	printf("%s\n",szReq);								//В этой переменной лежит строка, принятая
														//от клиента через сокет
														//НЕ ПРЕОБРАЗОВАНА


	char temp[512];			//В темп поомещаем преобразованную строку,
								//полученную от клиента через сокеты.
	strcpy(temp,szReq);




//ХЬЮСТОН, НУЖНА ИДЕЯ

//***************************************************************************************************//
//	А в этой чудесной, красиво обрамленной рамками комментариев и звездочек, территории				 //
// будет находиться самый душещипательный момент, содержащий в себе всю сущность данной программы,	 //
// задания, практики в целом, а так же смысла моего существования на протяжении						 //
// долгих (ЗАМЕНИТЬ ЧИСЛО), невыносимо жарких дней.     											 //
//																									 //
//***************************************************************************************************//		
		
		char *szResp = new char [strlen(temp)];
		strcpy(szResp,temp);

		retVal = send(clientSock, szResp, strlen(szResp), 0);

		if(retVal == SOCKET_ERROR)
		{
			printf("Unable to send with error: %d\n", WSAGetLastError());
			return SOCKET_ERROR;
		}

	cout << "\nFile sent\n";
//	char *szResp;
	szResp = new char[3];
	szResp = "+++";
	retVal = send(clientSock, szResp, strlen(szResp), 0);

	if(retVal == SOCKET_ERROR)
	{
		printf("Unable to send with error: %d\n", WSAGetLastError());
		return SOCKET_ERROR;
	}
	/// Closing socket
	closesocket(clientSock);
	closesocket(servSock);

	WSACleanup();
	system("pause");
	return SOCKET_OK;

}

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString=new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}












	//*char ce[1000];
	//ce[0] = '\0';
	//strcat(ce, "/C ");
	//strcat(ce, "echo  ");
	//strcat(ce, szReq);
	//strcat(ce, " > C:\\Users\\PK-11\\Desktop\\123\\file.txt");
	//int kol = strlen(ce);

	//cout << endl << "Dlinna stroki" << kol << endl;
	//printf("\n%s\n",ce);
	//
	//ShellExecuteA (NULL, "open", "cmd",(ce), NULL,NULL);

	//cout << "Tut jdem poka zapishem v file \n";
	//system("pause");
	//
	//


	//*ifstream myfile ("file.txt");
	//string line;
 //   string text;
 //   if (myfile.is_open())
 //   {
 //       while (! myfile.eof() )
 //       {
 //           getline(myfile,line);
 //           text += line;
 //       }
 //       myfile.close();
 //   }
 //   else cout << "Unable to open file";
	//*/

	//FILE* file = fopen("file.txt", "r" );


	//printf("Posilaem infy klientu iz faila\n");
	//do 
	//{
	//	char *szResp;
	//	char temp[512];
	//	fgets(temp,512,file);
	//	szResp = new char [strlen(temp)];
	//	strcpy(szResp,temp);
