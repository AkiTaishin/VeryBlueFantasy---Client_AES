/// <summary>
/// �T�[�o�[�ɐڑ�����CFormation���擾����
/// Json����CFormation�����o����悤�ɂ���B
/// </summary>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <stdio.h>
#include <winsock2.h>
#include "toScene.h"
#include <list>
#include <string>
#include <iostream>

/// <summary>
/// http�T�[�o�[�ɐڑ����邽�߂̊֐�
/// �z�X�g���AIP�A�h���X�A��M�f�[�^���̂��������Ă���
/// </summary>
std::string CtoScene::GoToScene(int index)
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

	URI sendData;
	sendData.number = index;
	sendData.templateName = "";

	// ������̕ϊ�
	std::stringstream data;
	{
		cereal::JSONOutputArchive outArchive(data);
		outArchive(cereal::make_nvp("data", sendData));
	}

	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
	// /pleaseSendUserID
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /goToScene HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(data.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + data.str();

	// HTTP���N�G�X�g���M
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region �f�[�^��M

	URI getUri;

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
		inArchive(getUri); // ���틭��
		
	}

#pragma endregion

	// winsock2�̏I������
	WSACleanup();

	return getUri.templateName;
}