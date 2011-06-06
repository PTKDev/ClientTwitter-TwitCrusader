/*
 *	TwitCrusader - Twitter Client For Linux Desktop
 *		Copyright (C) 2011  PTKDev, RoxShannon
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
 *		Author: Patryk Rzucidlo (PTKDev)
 *		Twitter: @ptkdev / @twitcrusader_en
 *		WebSite: http://www.twitcrusader.org
 * 		IRC: chat.freenode.net at #teamtwc
 */

#include "include/config.h"

int writeUserFile(){

	xmlTextWriterPtr writer;
	xmlDocPtr doc;
	xmlNodePtr node;


	if(debug==1){
		printf("\nwriteUserFile()");
		printf("\nuser.screenName= %s",user.screenName);
		printf("\nuser.id= %s", user.id);
		printf("\nuser.consumerKey= %s", user.consumerKey);
		printf("\nuser.consumerSecretKey= %s", user.consumerSecretKey);
		printf("\nuser.Token= %s", user.token);
		printf("\nuser.secretToken= %s", user.secretToken);
	}

	doc = xmlNewDoc((xmlChar*) XML_DEFAULT_VERSION);
	node = xmlNewDocNode(doc, NULL, (xmlChar*) "CONFIG", NULL);

	xmlDocSetRootElement(doc, node);
	writer = xmlNewTextWriterTree(doc, node, 0);

	xmlTextWriterStartDocument(writer, NULL, MY_ENCODING, NULL);
	xmlTextWriterStartElement(writer, (xmlChar*) "USER");

	xmlTextWriterWriteElement(writer, (xmlChar*)"screen_name", (xmlChar*)user.screenName);
	xmlTextWriterWriteElement(writer, (xmlChar*)"id", (xmlChar*)user.id);
	xmlTextWriterWriteElement(writer, (xmlChar*)"ConsumerKey", (xmlChar*)user.consumerKey);
	xmlTextWriterWriteElement(writer, (xmlChar*)"consumerSecretKey", (xmlChar*)user.consumerSecretKey);
	xmlTextWriterWriteElement(writer, (xmlChar*)"token", (xmlChar*)user.token);
	xmlTextWriterWriteElement(writer, (xmlChar*)"secretToken", (xmlChar*)user.secretToken);
	xmlTextWriterEndElement(writer);
	xmlTextWriterEndElement(writer);

	xmlFreeTextWriter(writer);

	xmlSaveFileEnc(progPath.configFile, doc, MY_ENCODING);

	xmlFreeDoc(doc);

	printf("\nreturn;");

	return 0;
}

char* getElement(xmlDocPtr doc, xmlNodePtr cur, char *keyword){

	xmlChar *key = NULL;
	char *empty = "error";

	if ((!xmlStrcmp(cur->name, (const xmlChar *)keyword))) {
		key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		//if(debug==1) printf("\n%s: %s", keyword, key);

		return (char *)key;
	}

	return empty;

}

int readUserFile(){

	int debug=1;
	char *keys;

	xmlDocPtr doc;
	xmlNodePtr cur;


	if(debug==1) puts("\nreadUserFile()");

	doc=xmlParseFile(progPath.configFile);
	if (doc == NULL ){
		printf("\n no file!");
		return 1;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		puts("\n no RootElement");
		xmlFreeDoc(doc);
		return 1;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "CONFIG")) {
		puts("\n no CONFIG");
		xmlFreeDoc(doc);
		return 1;
	}

	cur = cur->xmlChildrenNode;

	while (cur != NULL) {


		if ((!xmlStrcmp(cur->name, (const xmlChar *) "USER"))){

			cur = cur->xmlChildrenNode;

			keys=getElement(doc, cur, "screen_name");
			user.screenName=keys;
			cur = cur->next;


			keys=getElement(doc, cur, "id");
			user.id=keys;
			cur = cur->next;


			keys=getElement(doc, cur, "consumerKey");
			user.consumerKey=keys;
			cur = cur->next;


			keys=getElement(doc, cur, "consumerSecretKey");
			user.consumerSecretKey=keys;
			cur = cur->next;


			keys=getElement(doc, cur, "token");
			user.token=keys;
			cur = cur->next;


			keys=getElement(doc, cur, "secretToken");
			user.secretToken=keys;
			cur = cur->next;
		}
	}

	xmlFreeDoc(doc);

	if(debug==1){
		printf("\nuser.screenName= %s",user.screenName);
		printf("\nuser.id= %s", user.id);
		printf("\nuser.consumerKey= %s", user.consumerKey);
		printf("\nuser.consumerSecretKey= %s", user.consumerSecretKey);
		printf("\nuser.Token= %s", user.token);
		printf("\nuser.secretToken= %s", user.secretToken);
	}

	return 0;
}

void disconnect(){

	strcpy(user.token, " ");
	strcpy(user.consumerKey, " ");
	strcpy(user.consumerSecretKey, " ");
	strcpy(user.id, " ");
	strcpy(user.screenName, " ");
	strcpy(user.secretToken, " ");
}

int deleteAccount(){

	char *cmd;

	asprintf(&cmd, "%s %s", "rm -f ", progPath.configFile);

	if(system(cmd)==0){
		disconnect();
		return 0;
	}

	return 1;
}
