#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <stdio.h>
#include <winsock2.h>
#include "ClientManager.h"
#include <list>
#include <string>
#include <iostream>

/// <summary>
/// http�T�[�o�[�ɐڑ����邽�߂̊֐�
/// �z�X�g���AIP�A�h���X�A��M�f�[�^���̂��������Ă���
/// </summary>
int CNetWorkManager::NetworkManager()
{
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;
	char buf[2048];
	//SendMes mes;

	// winsock2�̏�����
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	// �\�P�b�g�̍쐬
	sock = socket(AF_INET, SOCK_STREAM, 0);

#pragma region �ڑ���w��p�\���̂̏���

	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

#pragma endregion

	// �T�[�o�ɐڑ�
	connect(sock, (struct sockaddr *)&server, sizeof(server));

#pragma region ���N�G�X�g���M

	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "GET /pleaseSqldata HTTP/1.0\r\nContent-Type:application/json\r\n\r\n");

	// HTTP���N�G�X�g���M
	int n = send(sock, buf, (int)strlen(buf), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
		return 1;
	}

#pragma endregion

#pragma region �f�[�^��M

	std::list <GETARRAY> storeArray;
	GETARRAY getArray[4];

	// �T�[�o����f�[�^����M
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

	// buf����JsonData�����o��
	std::string getJsonData = buf;
	int startJsonData = getJsonData.find("[");
	getJsonData = getJsonData.substr(startJsonData);

	{
		std::stringstream work(getJsonData);

		cereal::JSONInputArchive inArchive(work);
		inArchive(getArray[0]);
		inArchive(getArray[1]);
		inArchive(getArray[2]);
		inArchive(getArray[3]);
	}

#pragma endregion

	// winsock2�̏I������
	WSACleanup();

	return 0;
}