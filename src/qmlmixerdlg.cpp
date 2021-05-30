#include "qmlmixerdlg.h"

QmlMixerDlg::QmlMixerDlg( CClient* pClnt )
{
    pClient = pClnt;
    bPracticeMode = false;
}

void QmlMixerDlg::PracticeMode(){

    if ( pClient->IsConnected() )
        pClient->Stop();
    bPracticeMode = ! bPracticeMode;
    pClient->SetMuteOutStream( bPracticeMode );
    pClient->Start();
}
