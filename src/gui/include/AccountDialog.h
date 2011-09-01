/*
 *	 TwitCrusader-GUI is part of TwitCrusader - Twitter Client For Linux Desktop
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

#ifndef ACCOUNTDIALOG_H_
#define ACCOUNTDIALOG_H_

#include <gtkmm.h>
#include <gtkmm/stock.h>

#include "Icons.h"
#include "../../core/include/TwitterObject.h"

using namespace std;
using namespace Gtk;
using namespace Glib;

namespace TwitCrusader {

class AccountDialog: public Dialog
{
private:
	Table table;
	Label label;
	Label account;
	Button button;

protected:
void delete_account();

public:
	AccountDialog();
	virtual ~AccountDialog();
};

} /* namespace TwitCrusader */
#endif /* ACCOUNTDIALOG_H_ */
