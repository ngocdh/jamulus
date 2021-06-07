/******************************************************************************\
 * Copyright (c) 2004-2020
 *
 * Author(s):
 *  Volker Fischer
 *
 ******************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
\******************************************************************************/

#include <QCoreApplication>
#include "global.h"
#include <QApplication>
#include "client.h"
#include "connectdlg.h"
#ifdef ANDROID
#    include <QtAndroidExtras/QtAndroid>
#endif

// Implementation **************************************************************

int main ( int argc, char** argv )
{
    QApplication* qiApp = new QApplication ( argc, argv );
    CClient Client ( DEFAULT_PORT_NUMBER, DEFAULT_QOS_NUMBER, "", "", false, "SuperSimpleClient", false );
    Client.SetEnableOPUS64(true);
    Client.SetSndCrdPrefFrameSizeFactor(128);
    Client.SetMuteOutStream(false);
    Client.SetDoAutoSockBufSize(true);
    Client.SetAudioChannels(CC_STEREO);
    
    Client.SetAudioQuality( AQ_NORMAL );
    
    CClientSettings Settings ( &Client, "jamulussettings.ini" );
    
    CConnectDlg ConnectDlg ( &Client, &Settings, nullptr );

#ifdef ANDROID
    // special Android coded needed for record audio permission handling
    auto result = QtAndroid::checkPermission ( QString ( "android.permission.RECORD_AUDIO" ) );

    if ( result == QtAndroid::PermissionResult::Denied )
    {
        QtAndroid::PermissionResultMap resultHash = QtAndroid::requestPermissionsSync ( QStringList ( { "android.permission.RECORD_AUDIO" } ) );

        if ( resultHash["android.permission.RECORD_AUDIO"] == QtAndroid::PermissionResult::Denied )
        {
            return 0;
        }
    }
#endif
    
    // show dialog
    ConnectDlg.show();
    

    qiApp->exec();
    return 0;

}
