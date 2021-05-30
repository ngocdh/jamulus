#include "qmlconnectdlg.h"

QmlConnectDlg::QmlConnectDlg( CClient* pClnt )
{
    pClient = pClnt;

}

void QmlConnectDlg::connect( const QString &serveraddr ){

    if ( pClient->IsConnected() )
        pClient->Stop();
    pClient->SetServerAddr( serveraddr );
    pClient->Start();
}
