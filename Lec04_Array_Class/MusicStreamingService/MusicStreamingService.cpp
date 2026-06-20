#include "MusicStreamingService.h"

int main(void)
{
	MusicStreamingService a("service1");
	a.addMusic("gassi", "buzz", "gassi_album", 2000);
	a.addMusic("SWIM", "BTS", "SWIM_album", 2014);
	a.addMusic("bridge", "zion_T", "bridge_album", 2016);

	string music_title;
	cout << "Enter the Music  " << endl;
	cin >> music_title;//scanf_s("%s", &musicTitle);
	Music* result = a.serachByTitle(music_title);
	if (result != NULL)
	{
		cout << "found" << result->getTitle() << "by" << result->getartist() << endl;
	}
	else
	{
		cout << "NOT FOUND" << endl;
	}

	string artist_name;
	cout << "Enter the Artist name";
	cin >> artist_name;
	vector<Music*> artistResult = a.serachByArtist(artist_name);

	if (artistResult.size() > 0)
	{
		cout << "found" << artistResult.size() << "by" << artist_name << endl;
		for (int i = 0; i < artistResult.size(); i++) {
			cout << artistResult[i]->getTitle() << endl;
		}
	}
	else {
		cout << "NOT Found" << endl;
	}

	return 0;
}