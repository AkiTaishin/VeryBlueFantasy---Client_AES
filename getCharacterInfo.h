#pragma once
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>
#include <vector>
#include "main.h"

struct CHARIDS
{
	// std::vector<int> charIDs;
	int charIDs[10];

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(charIDs)
			
			/*CEREAL_NVP(cereal::make_nvp("array0", charIDs[0])),
			CEREAL_NVP(cereal::make_nvp("array1", charIDs[1]))
			CEREAL_NVP(cereal::make_nvp("array2", charIDs[2])),
			CEREAL_NVP(cereal::make_nvp("array3", charIDs[3])),
			CEREAL_NVP(cereal::make_nvp("array4", charIDs[4])),
			CEREAL_NVP(cereal::make_nvp("array5", charIDs[5])),
			CEREAL_NVP(cereal::make_nvp("array6", charIDs[6])),
			CEREAL_NVP(cereal::make_nvp("array7", charIDs[7])),
			CEREAL_NVP(cereal::make_nvp("array8", charIDs[8])),
			CEREAL_NVP(cereal::make_nvp("array9", charIDs[9]))*/
			
		);
	}
};

struct GETINFO
{
	// 結合元のキャラ情報テーブル
	int id;
	std::string name;
	std::string asset;
	std::string detail;
	std::string formation;
	int attack;
	int hp;
	int element;

	// 結合するキャラ所持情報テーブル
	int number;
	std::string userID;
	int charID;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(id),
			CEREAL_NVP(name),
			CEREAL_NVP(asset),
			CEREAL_NVP(detail),
			CEREAL_NVP(formation),
			CEREAL_NVP(attack),
			CEREAL_NVP(hp),
			CEREAL_NVP(element),
			CEREAL_NVP(number),
			CEREAL_NVP(userID),
			CEREAL_NVP(charID)
		);
	}
};

class CGetCharacterInfo
{
private:

public:
	// formationで選択されたキャラクター位置保存用
	static int m_SaveCharacterNumber;
	// formationで選択されたキャラの次の位置保存用(編成画面で空白ができないように)
	static int m_SaveCharacterNextNumber;
	// Selectで選択されたキャラクターのID保存用
	static int m_SaveSelectCharacterId;
	// 所持しているキャラクターデータが格納されているVector
	static std::vector<GETINFO> m_GetCharInfo;
	//static std::vector<GETINFO> GetCharInfo(std::vector<int> charIDs);
	static std::vector<GETINFO> GetCharInfo();
};
