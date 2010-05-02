/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo   *
 *   massimiliano.torromeo@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

//for browsing the filesystem
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "imagedialog.h"
#include "filelister.h"

using namespace std;

ImageDialog::ImageDialog(GMenu2X *gmenu2x, const string &text, const string &filter, const string &file) : FileDialog(gmenu2x, text, filter, file) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	this->filter = filter;
	setPath("/card");
	title = "Image Browser";
	if (!file.empty()) {
		this->file = strreplace(file,"skin:",gmenu2x->getExePath()+"skins/"+gmenu2x->confStr["skin"]+"/");
		string::size_type pos = this->file.rfind("/");
		if (pos != string::npos) {
			setPath( this->file.substr(0, pos) );
			cout << "ib: " << path() << endl;
			this->file = this->file.substr(pos+1,file.length());
		}
	}
	selRow = 0;
}

ImageDialog::~ImageDialog() {
	previews.clear();
}

void ImageDialog::beforeFileList() {
	if (fl.isFile(selected) && fileExists(path()+"/"+fl[selected]))
		previews[path()+"/"+fl[selected]]->blitRight(gmenu2x->s, 310, 43);
}

void ImageDialog::onChangeDir() {
	previews.clear();
}
