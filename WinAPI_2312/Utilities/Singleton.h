#pragma once

template <typename T>
class Singleton
{
public:
	static T* Get()
	{
		//static Singleton instance;
		//return &instance;

		if (instance == nullptr)
		{
			instance = new T();
		}
		
		return instance;
	}

	static void Delete()
	{
		delete instance;
		instance = nullptr;
	}

private:
	static T* instance;
};

template <typename T>
T* Singleton<T>::instance = nullptr;