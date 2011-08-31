/*
 *	 	Twitter Client For Linux Desktop
 *		Copyright (C) 2011  TwitCrusader Team
 *
 *		This program is free software: you can redistribute it and/or modify
 *		it under the terms of the GNU General Public License as published by
 *		the Free Software Foundation, either version 3 of the License, or
 *		(at your option) any later version.
 *
 *		This program is distributed in the hope that it will be useful,
 *		but WITHOUT ANY WARRANTY; without even the implied warranty of
 *		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *		GNU General Public License for more details.
 *
 *		You should have received a copy of the GNU General Public License
 *		along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *		WebSite: http://www.twitcrusader.org/
 * 		Development Guidelines: http://dev.twitcrusader.org/
 *		Follow on Twitter: @teamtwc
 * 		IRC: chat.freenode.net at #teamtwc
 * 		E-mail: teamtwc@twitcrusader.org
 *
 */

#ifndef TIMELINE_H_
#define TIMELINE_H_

/*
 *
 */
#include<iostream>
#include<vector>
#include <curl/curl.h>

extern "C"{
#include <oauth.h>
}

#include "Tweet.h"
#include "Config.h"
#include "TwitterURL.h"

using  namespace std;

namespace TwitCrusader {

#define TWITTER_KEY "3Y0iGu8KBpyNFaiWsIZPw"
#define TWITTER_KEY_SECRET "nNTvX1wvaEaHqz7Am4DYFFpkBN4vTFSWv3CYGOFk"

class TimeLine {

private:

	vector<Tweet> timeline;
	string timelineURL;
	string timelineFile;

public:
	TimeLine();
	virtual ~TimeLine();

	string getTimelineURL();
	string getTimelineFile();
	vector<Tweet> getTimeline();

	void setTimelineURL(string);
	void setTimelineFile(string);
	void setTimeline(vector<Tweet>);


	string getTimeLineElement(xmlDocPtr, xmlNodePtr, string);
	void getStatus (xmlDocPtr, xmlNodePtr, int);
	bool readTimeLine(string);

};
}
#endif /* TIMELINE_H_ */
