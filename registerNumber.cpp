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
#include "registerNumber.h"
#include <list>
#include <string>
#include <iostream>
#include "login.h"

/// <summary>
/// 登録者数の保存や読み込み
/// </summary>

int CRegister::LoadRegisterNumber(void)
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

	// HTTPで「/」をリクエストする文字列を生成
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "GET /pleaseRecordNumber HTTP/1.0\r\n\r\n");

	// HTTPリクエスト送信
	int n = send(sock, buf, (int)strlen(buf), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
	}

#pragma endregion

#pragma region データ受信

	RECORD_NUMBER record;

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

		inArchive(record);
	}

#pragma endregion

	// winsock2の終了処理
	WSACleanup();

	return record.recordNumber;
}

void CRegister::SaveRegisterNumber(REGISTER SendNumber)
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

	REGISTER saveNumber;
	saveNumber = SendNumber;

	std::stringstream sendData;
	{
		cereal::JSONOutputArchive outArchive(sendData);
		outArchive(cereal::make_nvp("data", saveNumber));
	}

	// HTTPで「/」をリクエストする文字列を生成
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf), "POST /pleaseSaveRegisterNumber HTTP/1.0\r\nContent-Length:%d\r\nContent-Type:application/json\r\n\r\n", (int)strlen(sendData.str().c_str()));

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

//REGISTER CRegister::LoadRegisterNumber(void)
//{
//	WSADATA wsaData;
//	struct sockaddr_in server;
//	SOCKET sock;
//	char buf[2048];
//
//	// winsock2の初期化
//	WSAStartup(MAKEWORD(2, 0), &wsaData);
//
//	// ソケットの作成
//	sock = socket(AF_INET, SOCK_STREAM, 0);
//
//#pragma region 接続先指定用構造体の準備
//
//	server.sin_family = AF_INET;
//	server.sin_port = htons(8080);
//	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//
//#pragma endregion
//
//	// サーバに接続
//	connect(sock, (struct sockaddr *)&server, sizeof(server));
//
//#pragma region リクエスト送信
//
//	// HTTPで「/」をリクエストする文字列を生成
//	memset(buf, 0, sizeof(buf));
//	_snprintf(buf, sizeof(buf), "GET /pleaseLoadRegisterNumber HTTP/1.0\r\n\r\n");
//
//	// HTTPリクエスト送信
//	int n = send(sock, buf, (int)strlen(buf), 0);
//	if (n < 0) {
//		printf("send : %d\n", WSAGetLastError());
//	}
//
//#pragma endregion
//
//#pragma region データ受信
//
//	REGISTER loadNumber[2];
//
//	// サーバからデータを受信
//	memset(buf, 0, sizeof(buf));
//	int len = sizeof(buf);
//	int nn = recv(sock, buf, len, 0);
//
//	// bufからJsonDataを取り出す
//	std::string getJsonData = buf;
//	int startJsonData = getJsonData.find("[");
//	getJsonData = getJsonData.substr(startJsonData);
//
//	{
//		/// <summary>
//		/// 現在何件のユーザーデータが保存されているか管理しなければSerializeする際にエラーがでる
//		/// この通信より前に通信してデータが何件あるか取得する以外にもっとスマートな方法はないものか@todo
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
//	// winsock2の終了処理
//	WSACleanup();
//
//	return loadNumber[0];
//}