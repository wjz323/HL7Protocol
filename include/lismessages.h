#ifndef LISMESSAGES_H
#define LISMESSAGES_H

#include <QObject>
#include "Message.h"
#include <QString>
#include <QList>

struct SampleInfo
{
    bool isEmergency;
    QList<QString> listMdid;
    QString sampleBarcode;
    QString sampleId;
};

struct AssayInfo
{
    QString con;
    QString result;  //pos or neg
    QString sampleId;
    QString sampleType;
    QString mdId;
    QString mdCode;
    QString unit;
};

class LisMessages : public QObject
{
    Q_OBJECT
public:
    explicit LisMessages(QObject *parent = nullptr);

    //sample request message
    Message SampleRequestMessage(QString sampleId);
    //sample response message
    SampleInfo SampleResponseMessage(QString strMessage);

    //result send message
    Message ResultSendMessage(AssayInfo asy,int result_type);





};


#endif // LISMESSAGES_H
