/// <summary>
/// ���݂̕ۑ�����Ă���Ґ������o��
/// ����̓Q�[�����I������Ă��ۑ�����Ă���悤�Ƀf�[�^�x�[�X������������Ă���
/// </summary>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <stdio.h>
#include <winsock2.h>
#include "scene.h"
#include "manager.h"
#include "getFormationData.h"
#include "login.h"
#include <list>
#include <string>
#include <iostream>

std::vector<SERIALIZE_DATA> CGetFormationData::m_GetFormationData;

/// <summary>
/// http�T�[�o�[�ɐڑ����邽�߂̊֐�
/// �z�X�g���AIP�A�h���X�A��M�f�[�^���̂��������Ă���
/// </summary>
std::vector<SERIALIZE_DATA> CGetFormationData::GetFormationData()
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

	GET_DETAIL sendData;
	sendData.admin = -1;
	sendData.number = -1;
	sendData.id = -1;
	sendData.name = "hoge";
	sendData.asset = "hoge";
	sendData.attack = -1;
	sendData.hp = -1;
	sendData.element = -1;
	sendData.userID = CLogin::m_UserID;

	// data������Ă��Ȃ�
	std::stringstream data;
	{
		cereal::JSONOutputArchive outArchive(data);
		outArchive(cereal::make_nvp("data", sendData));
	}

	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseFormationData HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(data.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + data.str();

	// HTTP���N�G�X�g���M
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region �f�[�^��M

	SERIALIZE_DATA getFormation[FORMATION_MAX];

	// �T�[�o����f�[�^����M
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

	// buf����JsonData�����o��
	std::string getJsonData = buf;
	int startJsonData = getJsonData.find("[");
	// �V�K���[�U�[or�����L����0�̏ꍇ
	if (startJsonData == -1)
	{
		return m_GetFormationData;
	}

	getJsonData = getJsonData.substr(startJsonData);

	{
		std::stringstream work(getJsonData);

		cereal::JSONInputArchive inArchive(work);
		inArchive(getFormation[0]); // �擪�L����
		inArchive(getFormation[1]); // �Q�Ԏ�
		inArchive(getFormation[2]); // �R�Ԏ�
	}

#pragma endregion

	// winsock2�̏I������
	WSACleanup();

	// ���ׂĂ����X�g�Ɋi�[���Ď��o��
	m_GetFormationData.assign(&getFormation[0], &getFormation[3]);

	return m_GetFormationData;
}