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

// ユーザーが持つキャラクターの総数を獲得する
void CPossession::GetUserPossessionChar(std::string userID)
{
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;
	char buf[2048];

	// winsock2の初期化
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	// ソケットの作成
	sock = socket(AF_INET, SOCK_STREAM, 0);

#pragma region 接続先指定用構造体の準備

	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

#pragma endregion

	// サーバに接続
	connect(sock, (struct sockaddr *)&server, sizeof(server));

#pragma region リクエスト送信

	POSSESSION sendData;
	sendData.number = -1;
	sendData.userID = userID;
	sendData.charID = -1;
	// dataが送れていない
	std::stringstream data;
	{
		cereal::JSONOutputArchive outArchive(data);
		outArchive(cereal::make_nvp("data", sendData));
	}

	// HTTPで「/」をリクエストする文字列を生成
	// /pleaseSendUserID
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleasePossessionNumber HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(data.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + data.str();

	// HTTPリクエスト送信
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region データ受信

	// レコード数を取得して何回ループするかしなければならない
	CharCount number;

	// サーバからデータを受信
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

	// bufからJsonDataを取り出す
	std::string getJsonData = buf;
	int startJsonData = getJsonData.find("[");
	getJsonData = getJsonData.substr(startJsonData);

	{
		/// <summary>
		/// 現在何件のユーザーデータが保存されているか管理しなければSerializeする際にエラーがでる
		/// この通信より前に通信してデータが何件あるか取得する以外にもっとスマートな方法はないものか
		/// </summary>
		std::stringstream work(getJsonData);
		cereal::JSONInputArchive inArchive(work);

		inArchive(number);
	}

#pragma endregion

	// winsock2の終了処理
	WSACleanup();

	// ここでキャラクター所持総数が格納される
	m_PossessionNumber = number.charNumber;
}

// golangにユーザーIDを送信する
void CPossession::SendUserIDandGetCharIDs(std::string userID)
{
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;
	char buf[2048];

	// winsock2の初期化
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	// ソケットの作成
	sock = socket(AF_INET, SOCK_STREAM, 0);

#pragma region 接続先指定用構造体の準備

	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

#pragma endregion

	// サーバに接続
	connect(sock, (struct sockaddr *)&server, sizeof(server));

#pragma region リクエスト送信

	POSSESSION sendData;
	sendData.number = -1;
	sendData.userID = userID;
	sendData.charID = -1;
	// dataが送れていない
	std::stringstream data;
	{
		cereal::JSONOutputArchive outArchive(data);
		outArchive(cereal::make_nvp("data", sendData));
	}

	// HTTPで「/」をリクエストする文字列を生成
	// /pleaseSendUserID
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseSendUserID HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(data.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + data.str();

	// HTTPリクエスト送信
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region データ受信

	// レコード数を取得して何回ループするかしなければならない
	POSSESSION getCharIDs[CHAR_MAX];

	// サーバからデータを受信
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

	// bufからJsonDataを取り出す
	std::string getJsonData = buf;
	int startJsonData = getJsonData.find("[");
	// 新規ユーザーor所持キャラ0の場合
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

	// すべてをVectorに格納して取り出す
	for (int i = 0; i < m_PossessionNumber; i++)
	{
		m_CharIDs[i] = getCharIDs[i].charID;
	}
	// 格納されていない場所には-1を詰める
	for (int i = m_PossessionNumber; i < 10; i++)
	{
		m_CharIDs[i] = -1;
	}
	//m_CharIDs.assign(&getCharIDs[0], &getCharIDs[m_PossessionNumber]);

#pragma endregion

	// winsock2の終了処理
	WSACleanup();
}