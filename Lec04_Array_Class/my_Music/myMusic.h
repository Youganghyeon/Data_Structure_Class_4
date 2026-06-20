#pragma once
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Music {
private:
	string artist;
	string album;
	string song;
	int year;
public:
	Music(string a_artist, string a_album, string a_getsong, int a_getyear)
	{
		this->artist = a_artist;
		this->album = a_album;
		this->song = a_getsong;
		this->year = a_getyear;
	}

	string getartist(void)
	{
		return artist;
	}

	string getalbum(void)
	{
		return album;
	}

	string getsong(void)
	{
		return song;
	}

	int getyear(void)
	{
		return year;
	}
};

class MusicStreaming {
private:
	vector<Music> Music_list;
public:
	MusicStreaming() {};
	void addMusic(string a_artist, string a_album, string a_getsong, string a_getyear) 
	{
		Music newMusic(a_artist, a_album, a_getsong, a_getyear);
		Music_list.push_back(newMusic);
	};

};