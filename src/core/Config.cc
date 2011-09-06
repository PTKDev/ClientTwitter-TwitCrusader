/*
 *	 TwitCrusader++ - Twitter Client For Linux Desktop
 *		Copyright (C) 2011  TwitCrusader++
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
 *		Source: https://github.com/RoxShannon/TwitCrusaderpp
 *		email: orazio.1985@hotmail.com
 *
 */

#include "include/Config.h"

namespace TwitCrusader {

Config::Config()
{
	avatarDir=ustring();
	configDir=ustring();
	configFile=ustring();
	timelineDir=ustring();
	homeDir=ustring();

	homeDir.assign(Glib::get_home_dir());
	setAvatarDir();
	setConfigDir();
	setConfigFile();
	setTimelineDir();
/*
	cout<<"config: \n";
	cout<<getAvatarDir()<<"\n";
	cout<<getConfigDir()<<"\n";
	cout<<getConfigFile()<<"\n";
	cout<<getTimeLineDir()<<"\n";
*/
	this->createAvatarDir();
	this->createConfigDir();
	this->createTimelineDir();

}

Config::~Config()
{

}

void Config::setAvatarDir()
{

	avatarDir.assign(homeDir);
	avatarDir.append(AVATAR_SUBDIR);
}

bool Config::createAvatarDir()
{

	/* User-Directory Path */

	//Avatar Dir
	if(!avatarDir.empty()){
		remove(avatarDir.c_str());
		//mkdir( avatarDir.c_str(), 0777);

		ustring cmd=ustring();
		cmd.assign(MKDIR_CMD);
		cmd.append(avatarDir);
		cout<<cmd;
		system(cmd.c_str());

		return true;
	}

	return false;
}

void Config::setConfigDir()
{

	//Configuration File
	configDir.assign(homeDir);
	configDir.append(CONFIG_SUBDIR);
}

bool Config::createConfigDir()
{

	if(!configDir.empty()){
		//mkdir( configDir.c_str(), 0777);
		ustring cmd=ustring();
		cmd.assign(MKDIR_CMD);
		cmd.append(configDir);
		system(cmd.c_str());
		return true;
	}
	return false;

}

void Config::setTimelineDir()
{
	timelineDir.assign(homeDir);
	timelineDir.append(TIMELINE_SUBDIR);

}

bool Config::createTimelineDir()
{

	if(!timelineDir.empty()){
		//mkdir(timelineDir.c_str(), 0777);
		ustring cmd=ustring();
		cmd.assign(MKDIR_CMD);
		cmd.append(timelineDir);
		system(cmd.c_str());
		return true;
	}

	return false;

}

void Config::setConfigFile()
{
	configFile.assign(configDir);
	configFile.append(CONFIG_FILENAME);
}


ustring Config::getAvatarDir()
{
	return avatarDir;
}

ustring Config::getConfigDir()
{
	return configDir;
}

ustring Config::getConfigFile()
{
	return configFile;
}


ustring Config::getTimeLineDir()
{
	return timelineDir;
}


bool Config::deleteConfigFile()
{
	ustring cmd=ustring();

	cmd.assign(RM_CMD);
	cmd.append(configFile);
	system(cmd.c_str());

	return true;
}

bool Config::is_registered(){
	bool reg=Functions::readRawTextFile(getConfigFile().c_str()).empty();
	return !reg;
}
}
