/// <summary>
/// サーバーに接続してCFormationを取得する
/// JsonからCFormationを取り出せるようにする。
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
/// httpサーバーに接続するための関数
/// ホスト情報、IPアドレス、受信データ等のやり取りをしている
/// </summary>
std::string CtoScene::GoToScene(int index)
{
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;
	char buf[2048];
	//SendMes mes;

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

	URI sendData;
	sendData.number = index;
	sendData.templateName = "";

	// 送る情報の変換
	std::stringstream data;
	{
		cereal::JSONOutputArchive outArchive(data);
		outArchive(cereal::make_nvp("data", sendData));
	}

	// HTTPで「/」をリクエストする文字列を生成
	// /pleaseSendUserID
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /goToScene HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(data.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + data.str();

	// HTTPリクエスト送信
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region データ受信

	URI getUri;

	// サーバからデータを受信
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

	// bufからJsonDataを取り出す
	std::string getJsonData = buf;
	int startJsonData = getJsonData.find("[");
	getJsonData = getJsonData.substr(startJsonData);

	{
		std::stringstream work(getJsonData);

		cereal::JSONInputArchive inArchive(work);
		inArchive(getUri); // 武器強化
		
	}

#pragma endregion

	// winsock2の終了処理
	WSACleanup();

	return getUri.templateName;
}