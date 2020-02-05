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
#include "registerNumber.h"
#include <list>
#include <string>
#include <iostream>
#include "login.h"

/// <summary>
/// �o�^�Ґ��̕ۑ���ǂݍ���
/// </summary>

int CRegister::LoadRegisterNumber(void)
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

	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "GET /pleaseRecordNumber HTTP/1.0\r\n\r\n");

	// HTTP���N�G�X�g���M
	int n = send(sock, buf, (int)strlen(buf), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region �f�[�^��M

	RECORD_NUMBER record;

	// �T�[�o����f�[�^����M
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

	// buf����JsonData�����o��
	std::string getJsonData = buf;
	int startJsonData = getJsonData.find("[");
	getJsonData = getJsonData.substr(startJsonData);

	{
		/// <summary>
		/// ���݉����̃��[�U�[�f�[�^���ۑ�����Ă��邩�Ǘ����Ȃ����Serialize����ۂɃG���[���ł�
		/// ���̒ʐM���O�ɒʐM���ăf�[�^���������邩�擾����ȊO�ɂ����ƃX�}�[�g�ȕ��@�͂Ȃ����̂�
		/// </summary>
		std::stringstream work(getJsonData);
		cereal::JSONInputArchive inArchive(work);

		inArchive(record);
	}

#pragma endregion

	// winsock2�̏I������
	WSACleanup();

	return record.recordNumber;
}

void CRegister::SaveRegisterNumber(REGISTER SendNumber)
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

	REGISTER saveNumber;
	saveNumber = SendNumber;

	std::stringstream sendData;
	{
		cereal::JSONOutputArchive outArchive(sendData);
		outArchive(cereal::make_nvp("data", saveNumber));
	}

	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseSaveRegisterNumber HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(sendData.str().c_str()));

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

//REGISTER CRegister::LoadRegisterNumber(void)
//{
//	WSADATA wsaData;
//	struct sockaddr_in server;
//	SOCKET sock;
//	char buf[2048];
//
//	// winsock2�̏�����
//	WSAStartup(MAKEWORD(2, 0), &wsaData);
//
//	// �\�P�b�g�̍쐬
//	sock = socket(AF_INET, SOCK_STREAM, 0);
//
//#pragma region �ڑ���w��p�\���̂̏���
//
//	server.sin_family = AF_INET;
//	server.sin_port = htons(8080);
//	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//
//#pragma endregion
//
//	// �T�[�o�ɐڑ�
//	connect(sock, (struct sockaddr *)&server, sizeof(server));
//
//#pragma region ���N�G�X�g���M
//
//	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
//	memset(buf, 0, sizeof(buf));
//	_snprintf(buf, sizeof(buf), "GET /pleaseLoadRegisterNumber HTTP/1.0\r\n\r\n");
//
//	// HTTP���N�G�X�g���M
//	int n = send(sock, buf, (int)strlen(buf), 0);
//	if (n < 0) {
//		printf("send : %d\n", WSAGetLastError());
//	}
//
//#pragma endregion
//
//#pragma region �f�[�^��M
//
//	REGISTER loadNumber[2];
//
//	// �T�[�o����f�[�^����M
//	memset(buf, 0, sizeof(buf));
//	int len = sizeof(buf);
//	int nn = recv(sock, buf, len, 0);
//
//	// buf����JsonData�����o��
//	std::string getJsonData = buf;
//	int startJsonData = getJsonData.find("[");
//	getJsonData = getJsonData.substr(startJsonData);
//
//	{
//		/// <summary>
//		/// ���݉����̃��[�U�[�f�[�^���ۑ�����Ă��邩�Ǘ����Ȃ����Serialize����ۂɃG���[���ł�
//		/// ���̒ʐM���O�ɒʐM���ăf�[�^���������邩�擾����ȊO�ɂ����ƃX�}�[�g�ȕ��@�͂Ȃ����̂�@todo
//		/// </summary>
//		std::stringstream work(getJsonData);
//		cereal::JSONInputArchive inArchive(work);
//
//		inArchive(loadNumber[0]);
//		inArchive(loadNumber[1]);
//	}
//
//#pragma endregion
//
//	// winsock2�̏I������
//	WSACleanup();
//
//	return loadNumber[0];
//}