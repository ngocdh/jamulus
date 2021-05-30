#include "qmlconnectdlg.h"

QmlConnectDlg::QmlConnectDlg()
{

}

void QmlConnectDlg::connect(const QString &serveraddr){
    CClient Client ( DEFAULT_PORT_NUMBER, DEFAULT_QOS_NUMBER, "10.55.107.104", "", false, "iOScOnly", false );
    Client.SetEnableOPUS64( true );
    Client.SetSndCrdPrefFrameSizeFactor( 128 );
    Client.SetAudioQuality( AQ_HIGH );
    Client.SetAudioChannels( CC_STEREO );
    Client.SetMuteOutStream( false );
    Client.SetDoAutoSockBufSize( true );
}
