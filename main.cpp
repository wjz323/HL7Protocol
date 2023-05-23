#include <QCoreApplication>
#include "include/Message.h"
#include <QDebug>
#include <QString>
#include <QList>
#include "include/lismessages.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //example1 string to message
    auto sampleMessage =
                   R"(MSH|^~\&|IA PHIMS Stage^2.16.840.1.114222.4.3.3.5.1.2^ISO|IA Public Health Lab^2.16.840.1.114222.4.1.10411^ISO|IA.DOH.IDSS^2.16.840.1.114222.4.3.3.19^ISO|IADOH^2.16.840.1.114222.4.1.3650^ISO|201203312359||ORU^R01^ORU_R01|2.16.840.1.114222.4.3.3.5.1.2-20120314235954.325|T|2.5.1|||AL|NE|USA||||PHLabReport-Ack^^2.16.840.1.113883.9.10^ISO
PID|1||14^^^IA PHIMS Stage&2.16.840.1.114222.4.3.3.5.1.2&ISO^PI^IA Public Health Lab&2.16.840.1.114222.4.1.10411&ISO~145^^^IA PHIMS Stage&2.16.840.1.114222.4.3.3.5.1.2&ISO^PI^IA Public Health Lab&2.16.840.1.114222.4.1.10411&ISO||Finn^Huckleberry^^^^^L||19630815|M||2106-3^White^CDCREC^^^^04/24/2007~1002-5^American Indian or Alaska Native^CDCREC^^^^04/24/2007|721SPRING STREET^^GRINNELL^IA^50112^USA^H|||||M^Married^HL70002^^^^2.5.1||||||H^Hispanic orLatino^HL70189^^^^2.5.1)";

    auto message = Message(sampleMessage);
    message.parseMessage();
    qDebug()<<QString::fromStdString(message.getValue("PID.3"));
    bool bret=message.hasRepetitions("PID.3");
    bool a1=message.segments("PID")[0].fields(3).hasRepetitions;
    qDebug()<<"bret:"<<bret;
    qDebug()<<"a1:"<<a1;

    //example2 constructrue message
    Message msg=Message();
    msg.addSegmentMSH("KH", "Aurora-500i", "", "", "", "QRY^Q02", "4", "P", "2.3.1");
    auto obr = Segment("OBR", msg.encoding);
    obr.addNewField("1111");
    obr.addEmptyField();//2
    obr.addEmptyField();//3
    obr.addNewField("1");//4
    obr.addEmptyField();//5
    obr.addEmptyField();//6
    obr.addEmptyField();//7
    obr.addNewField("12345679");//8

    auto obr1 = Segment("OBR", msg.encoding);
    obr1.addNewField("1111");
    obr1.addEmptyField();//2
    obr1.addEmptyField();//3
    obr1.addNewField("1");//4
    obr1.addEmptyField();//5
    obr1.addEmptyField();//6
    obr1.addEmptyField();//7
    obr1.addNewField("111111111");//8

    msg.addNewSegment(obr);

    msg.addNewSegment(obr1);
    auto s=msg.segments("OBR");

    qDebug()<<QString::fromStdString(msg.getValue("OBR(1).8"));
    qDebug()<<QString::fromStdString(msg.getValue("OBR(2).8"));
    qDebug()<<QString::fromStdString(s[0].fields(8).getValue());
    qDebug()<<QString::fromStdString(msg.getValue("MSH.8"));

    //send the char array by tcp.
    std::vector<char> sendMessage=msg.getMLLP();
    for (int var = 0; var < sendMessage.size(); ++var) {
        qDebug()<<sendMessage[var];
    }


    //example 3 use Lis Messages
    LisMessages lisMsgs;
    // get sample info by sample id
    Message msg2=lisMsgs.SampleRequestMessage("12345");

    //send the "msg2.getMLLP()" list to Lis by tcp;
    //get the string from tcp response.
    SampleInfo sampleInfo= lisMsgs.SampleResponseMessage("a string");
    AssayInfo asy;
    lisMsgs.ResultSendMessage(asy,1);




    return a.exec();
}
