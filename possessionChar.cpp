#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <stdio.h>
#include <winsock2.h>
#include "scene.h"
#include "manager.h"
#include <list>
#include <string>
#include <iostream>
#include "possessionChar.h"
#include "login.h"

//std::vector<int> CPossession::m_CharIDs;
int CPossession::m_CharIDs[10];
int CPossession::m_PossessionNumber;

// ���[�U�[�����L�����N�^�[�̑������l������
void CPossession::GetUserPossessionChar(std::string userID)
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

	POSSESSION sendData;
	sendData.number = -1;
	sendData.userID = userID;
	sendData.charID = -1;
	// data������Ă��Ȃ�
	std::stringstream data;
	{
		cereal::JSONOutputArchive outArchive(data);
		outArchive(cereal::make_nvp("data", sendData));
	}

	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
	// /pleaseSendUserID
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleasePossessionNumber HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(data.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + data.str();

	// HTTP���N�G�X�g���M
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region �f�[�^��M

	// ���R�[�h�����擾���ĉ��񃋁[�v���邩���Ȃ���΂Ȃ�Ȃ�
	CharCount number;

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

		inArchive(number);
	}

#pragma endregion

	// winsock2�̏I������
	WSACleanup();

	// �����ŃL�����N�^�[�����������i�[�����
	m_PossessionNumber = number.charNumber;
}

// golang�Ƀ��[�U�[ID�𑗐M����
void CPossession::SendUserIDandGetCharIDs(std::string userID)
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

	POSSESSION sendData;
	sendData.number = -1;
	sendData.userID = userID;
	sendData.charID = -1;
	// data������Ă��Ȃ�
	std::stringstream data;
	{
		cereal::JSONOutputArchive outArchive(data);
		outArchive(cereal::make_nvp("data", sendData));
	}

	// HTTP�Łu/�v�����N�G�X�g���镶����𐶐�
	// /pleaseSendUserID
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseSendUserID HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(data.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + data.str();

	// HTTP���N�G�X�g���M
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region �f�[�^��M

	// ���R�[�h�����擾���ĉ��񃋁[�v���邩���Ȃ���΂Ȃ�Ȃ�
	POSSESSION getCharIDs[CHAR_MAX];

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
		return;
	}

	getJsonData = getJsonData.substr(startJsonData);

	std::stringstream work(getJsonData);
	cereal::JSONInputArchive inArchive(work);
	for (int i = 0; i < m_PossessionNumber; i++)
	{
		inArchive(getCharIDs[i]);
	}

	// ���ׂĂ�Vector�Ɋi�[���Ď��o��
	for (int i = 0; i < m_PossessionNumber; i++)
	{
		m_CharIDs[i] = getCharIDs[i].charID;
	}
	// �i�[����Ă��Ȃ��ꏊ�ɂ�-1���l�߂�
	for (int i = m_PossessionNumber; i < 10; i++)
	{
		m_CharIDs[i] = -1;
	}
	//m_CharIDs.assign(&getCharIDs[0], &getCharIDs[m_PossessionNumber]);

#pragma endregion

	// winsock2�̏I������
	WSACleanup();
}