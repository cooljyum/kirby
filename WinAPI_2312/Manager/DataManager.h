#pragma once

class DataManager : public Singleton<DataManager>
{
private:
	friend class Singleton;

	DataManager();
	~DataManager();

public:
	void LoadData(string file, int mapIndex);

	vector<vector<int>> GetMapData(int mapIndex) { return mapDatas[mapIndex]; }
	int GetMapSize() { return mapDatas.size(); }
private:
	map<int, vector<vector<int>>> mapDatas;
};