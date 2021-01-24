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
	FileChooser myChooser("Create presets folder  from a preenfm bank",
		getLastSelectedPresetFolder(),
		"*.BNK");

	if (myChooser.browseForFileToOpen())
	{
		setLastSelectedPresetFolder(myChooser);

		String folderName = presets->savePresets(myChooser.getResult());

		if (folderName.length() > 0) {
			AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
				TRANS("Folder Created"),
				TRANS("A folder with all the bank presets has been created here \r\n" +
					folderName));
		}
		else {
			AlertWindow::showMessageBox(AlertWindow::WarningIcon,
				TRANS("Error"),
				TRANS("Could not create you bank folder"));
		}
	}
}

void StandalonePluginHolder::createPfmBank() {
	FileChooser myChooser("Create bank from a presets folder",
		getLastSelectedPresetBank());

	if (myChooser.browseForDirectory())
	{
		setLastSelectedPresetBank(myChooser);

		presets->saveBank(myChooser.getResult());
	}
}

