#include "MusicStreamingService.h"

int main(void)
{
	MusicStreamingService a("service1");
	a.addMusic("gassi", "buzz", "gassi_album", 2000);
	a.addMusic("SWIM", "BTS", "SWIM_album", 2014);
	a.addMusic("bridge", "zion_T", "bridge_album", 2016);

	string music_title;
	cout << "Enter the Music";
	cin >> music_title;//scanf_s("%s", &musicTitle);
	Music* result = a.serachByTitle(music_title);
	if (result != NULL)
	{
		cout << "found" << result->getTitle() << "by" << result->getartist() << endl;
	}
	return 0;
}