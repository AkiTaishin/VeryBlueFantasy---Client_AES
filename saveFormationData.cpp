/// <summary>
/// �T�[�o�[�ɐڑ�����CFormation���擾����
/// Json����CFormation�����o����悤�ɂ���B
/// </summary>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <stdio.h>
#include <winsock2.h>
#include "scene.h"
#include "manager.h"
#include "saveFormationData.h"
#include "getCharacterInfo.h"
#include "login.h"
#include <list>
#include <string>
#include <iostream>

/// <summary>
/// http�T�[�o�[�ɐڑ����邽�߂̊֐�
/// �z�X�g���AIP�A�h���X�A��M�f�[�^���̂��������Ă���
/// </summary>
void CSaveFormationData::SaveFormation(SAVE_DETAIL data)
{
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;
	char buf[2048];

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

	SAVE_DETAIL saveData;
	saveData = data;
	std::stringstream sendData;
	{
		cereal::JSONOutputArchive outArchive(sendData);
		outArchive(cereal::make_nvp("data", saveData));
	}

	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseSaveDetail HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(sendData.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + sendData.str();

	// HTTP���N�G�X�g���M
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region �f�[�^��M

	// �T�[�o����f�[�^����M
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

#pragma endregion

	// winsock2�̏I������
	WSACleanup();
}

/// <summary>
/// �Ґ��p��DataBase�̒��g�����Z�b�g����
/// �f�o�b�O�ɗp����
/// </summary>
void CSaveFormationData::ResetFormation(void)
{
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;
	char buf[2048];

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

	SAVE_DETAIL saveData;
	saveData.admin = -1;
	saveData.number = -1;
	saveData.id = -1;
	saveData.name = "hoge";
	saveData.asset = "hoge";
	saveData.attack = -1;
	saveData.hp = -1;
	saveData.element = -1;
	saveData.userID = CLogin::m_UserID;

	std::stringstream sendData;
	{
		cereal::JSONOutputArchive outArchive(sendData);
		outArchive(cereal::make_nvp("data", saveData));
	}

	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseReset HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(sendData.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + sendData.str();

	// HTTP���N�G�X�g���M
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region �f�[�^��M

	// �T�[�o����f�[�^����M
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

#pragma endregion

	CGetCharacterInfo::m_SaveCharacterNumber = CGetCharacterInfo::m_SaveCharacterNextNumber = 0;

	// winsock2�̏I������
	WSACleanup();
}