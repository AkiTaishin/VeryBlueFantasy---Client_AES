#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>
#include <vector>
#include <string>

// CharCount �����L�����N�^�[����
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
	// �����L�����N�^�[��ID���i�[����郁���o
	// static std::vector<int> m_CharIDs;
	static int m_CharIDs[10];

	// �����L�����N�^�[�������i�[����郁���o
	static int m_PossessionNumber;

	// golang���烆�[�U�[ID�ƈ�v���郆�[�U�[�̃L�������������󂯎��
	static void GetUserPossessionChar(std::string userID);

	// ���[�U�[ID��golang�ɑ���&���[�U�[ID�ƈ�v���郆�[�U�[�̃L�������������󂯎��
	static void SendUserIDandGetCharIDs(std::string userID);
};
