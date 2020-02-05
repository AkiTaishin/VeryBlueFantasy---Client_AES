/// <summary>
/// サーバーに接続してCFormationを取得する
/// JsonからCFormationを取り出せるようにする。
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
/// httpサーバーに接続するための関数
/// ホスト情報、IPアドレス、受信データ等のやり取りをしている
/// </summary>
void CSaveFormationData::SaveFormation(SAVE_DETAIL data)
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

	SAVE_DETAIL saveData;
	saveData = data;
	std::stringstream sendData;
	{
		cereal::JSONOutputArchive outArchive(sendData);
		outArchive(cereal::make_nvp("data", saveData));
	}

	// HTTPで「/」をリクエストする文字列を生成
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseSaveDetail HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(sendData.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + sendData.str();

	// HTTPリクエスト送信
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region データ受信

	// サーバからデータを受信
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

#pragma endregion

	// winsock2の終了処理
	WSACleanup();
}

/// <summary>
/// 編成用のDataBaseの中身をリセットする
/// デバッグに用いる
/// </summary>
void CSaveFormationData::ResetFormation(void)
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

	// HTTPで「/」をリクエストする文字列を生成
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseReset HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(sendData.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + sendData.str();

	// HTTPリクエスト送信
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region データ受信

	// サーバからデータを受信
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

#pragma endregion

	CGetCharacterInfo::m_SaveCharacterNumber = CGetCharacterInfo::m_SaveCharacterNextNumber = 0;

	// winsock2の終了処理
	WSACleanup();
}