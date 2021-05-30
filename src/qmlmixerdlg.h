#ifndef QMLMIXERDLG_H
#define QMLMIXERDLG_H

#include <QObject>

#include "client.h"
#include "global.h"

class QmlMixerDlg : public QObject
{
    Q_OBJECT

public:
    QmlMixerDlg( CClient* );

private:
    bool bPracticeMode;
    CClient * pClient;

public slots:
    void PracticeMode();
};

#endif // QMLMIXERDLG_H
