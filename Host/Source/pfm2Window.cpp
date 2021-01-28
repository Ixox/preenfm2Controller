/*
* Copyright 2020 Xavier Hosxe
*
* Author: Xavier Hosxe (xavier <dot> hosxe
*                      (at) g m a i l <dot> com)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pfm2Window.h"


void StandalonePluginHolder::createPresetFolders() {
	FileChooser myChooser("Create presets folder from a preenfm bank",
		getLastSelectedPresetFolder(),
		"*.bnk");

	if (myChooser.browseForFileToOpen())
	{
		setLastSelectedPresetFolder(myChooser);

		presets->savePresetsFolder(myChooser.getResult());
	}
}

void StandalonePluginHolder::createPfmBank() {
	FileChooser myChooser("Create bank from a presets folder",
		getLastSelectedPresetBank());

	if (myChooser.browseForDirectory())
	{
		setLastSelectedPresetBank(myChooser);

		presets->savePfmBankFile(myChooser.getResult());
	}
}

void StandalonePluginHolder::organizePfmBankFile() {
	FileChooser myChooser("Choose the bank to reorgnize",
		getLastSelectedPresetFolder(),
		"*.bnk");

	if (myChooser.browseForFileToOpen())
	{
		setLastSelectedPresetFolder(myChooser);

		presets->organizeBank(myChooser.getResult());
	}
		
}