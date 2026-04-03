#pragma once
#include <cstdio>
#include <iostream>
#include  <vector>

using namespace std;

class Music {
protected:
	string title;
	string artist;
	string album;
	int	   year;
public:
	Music(string a, string b, string c, int y) {
		this->title = a;
		this->artist = b;
		this->album = c;
		this->year = y;
	}
	
	string getTitle() { 
		return title;
	};
	string getartist() {
		return artist;
	};
	string getalbum() {
		return title;
	};
	int getyear() {
		return year;
	};

};

class MusicStreamingService:Music {
private:
	string serviceName;
	vector<Music>  MusicList;
public:
	//MusicStreamingService() : serviceName("Default Service") {};
	MusicStreamingService(string serviceName_i): Music("", "", "", 0) {
		this->serviceName = serviceName_i;
	};
	void addMusic(string title_i, string artist_i, string album_i, int year_i)
	{
		Music newMusic(title_i, artist_i, album_i, year_i);
		MusicList.push_back(newMusic);
		cout << title << "by" << artist<< "addedto" << serviceName<< endl;
	};

	Music* serachByTitle(string title) {
		for (int i = 0; i < MusicList.size(); i++)
		{
			if (MusicList[i].getTitle() == title)
			{
				return &MusicList[i];
			}
			return NULL;
		}
	}

};
