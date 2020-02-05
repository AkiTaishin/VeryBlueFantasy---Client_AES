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
#include "getFormationData.h"
#include "getCharacterInfo.h"
#include "login.h"
#include <list>
#include <string>
#include <iostream>
#include "possessionChar.h"

std::vector<GETINFO> CGetCharacterInfo::m_GetCharInfo;

int m_SaveCharacterNumber = 0;
int m_SaveCharacterNextNumber = 0;
int m_SaveSelectCharacterId;

/// <summary>
/// httpサーバーに接続するための関数
/// ホスト情報、IPアドレス、受信データ等のやり取りをしている
/// </summary>
std::vector<GETINFO> CGetCharacterInfo::GetCharInfo()
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

	// dataが送れていない
	std::stringstream data;
	{
		cereal::JSONOutputArchive outArchive(data);
		outArchive(cereal::make_nvp("data", sendData));
	}

	// HTTPで「/」をリクエストする文字列を生成
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseCharacterInfo HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(data.str().c_str()));

	std::string newBuf = buf;

	newBuf = newBuf + data.str();

	// HTTPリクエスト送信
	int n = send(sock, newBuf.c_str(), (int)strlen(newBuf.c_str()), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region データ受信

	GETINFO getInfo[CHAR_MAX];

	// サーバからデータを受信
	memset(buf, 0, sizeof(buf));
	int len = sizeof(buf);
	int nn = recv(sock, buf, len, 0);

	// bufからJsonDataを取り出す
	std::string getJsonData = buf;
	int startJsonData = getJsonData.find("[");
	// 新規ユーザーorキャラ所持0の時の場合
	if (startJsonData == -1)
	{
		return m_GetCharInfo;
	}
	getJsonData = getJsonData.substr(startJsonData);

	std::stringstream work(getJsonData);
	cereal::JSONInputArchive inArchive(work);

	for (int i = 0; i < CPossession::m_PossessionNumber; i++)
	{
		inArchive(getInfo[i]);
	}

#pragma endregion

	// winsock2の終了処理
	WSACleanup();

	int SizeCheck = m_GetCharInfo.size();

	// すべてをリストに格納して取り出す
	// すでにVectorに何かが格納されている場合は中身を置き換える
	if (SizeCheck > 0)
	{
		m_GetCharInfo.assign(&getInfo[0], &getInfo[CPossession::m_PossessionNumber]);
	}
	else
	{
		// まだ何も入っていない場合は最初に一度だけVectorに詰める
		for (int i = 0; i < CPossession::m_PossessionNumber; i++)
		{
			m_GetCharInfo.push_back(getInfo[i]);
		}
	}

	return m_GetCharInfo;
}

/// <summary>
/// キャラ選択画面でキャラクターが選択されたら
/// 選択画面でクリックされたところにキャラクター情報を入れたい
/// </summary>