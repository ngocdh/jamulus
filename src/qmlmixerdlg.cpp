#include "qmlmixerdlg.h"

QmlMixerDlg::QmlMixerDlg( CClient* pClnt )
{
    pClient = pClnt;
    bPracticeMode = false;
}

void QmlMixerDlg::PracticeMode(){
    bPracticeMode = ! bPracticeMode;
    pClient->SetMuteOutStream( bPracticeMode );
}
