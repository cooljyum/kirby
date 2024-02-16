#include "Framework.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

void DataManager::LoadData(string file, int mapIndex)
{
	ifstream loadFile(file);

	string temp;

	while (true)
	{
		loadFile >> temp;

		if (loadFile.eof())
			return;

		vector<string> row = SplitString(temp, ",");

		vector<int> rowData;
		for (string n : row)
			rowData.push_back(stoi(n));

		mapDatas[mapIndex].push_back(rowData);
	}
}
