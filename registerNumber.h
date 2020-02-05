#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>
#include <vector>
#include <string>

struct REGISTER
{
	int key;
	int registerNumber;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(key),
			CEREAL_NVP(registerNumber)
		);
	}
};

struct RECORD_NUMBER
{
	int recordNumber;
	
	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(recordNumber)
		);
	}
};

class CRegister
{
private:

public:
	static void SaveRegisterNumber(REGISTER SendNumber);
	static int LoadRegisterNumber(void);
	//static REGISTER LoadRegisterNumber(void);
};
