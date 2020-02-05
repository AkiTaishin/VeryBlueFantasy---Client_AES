#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>
#include <vector>
#include <string>

// CharCount 所持キャラクター総数
struct CharCount
{
	int charNumber;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(charNumber)
		);
	}
};

struct POSSESSION
{
	int number;
	std::string userID;
	int charID;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(number),
			CEREAL_NVP(userID),
			CEREAL_NVP(charID)
		);
	}
};

class CPossession
{
private:

public:
	// 所持キャラクターのIDが格納されるメンバ
	// static std::vector<int> m_CharIDs;
	static int m_CharIDs[10];

	// 所持キャラクター総数が格納されるメンバ
	static int m_PossessionNumber;

	// golangからユーザーIDと一致するユーザーのキャラ所持情報を受け取る
	static void GetUserPossessionChar(std::string userID);

	// ユーザーIDをgolangに送る&ユーザーIDと一致するユーザーのキャラ所持情報を受け取る
	static void SendUserIDandGetCharIDs(std::string userID);
};
