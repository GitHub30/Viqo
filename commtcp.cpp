#include "commtcp.h"
#include "mainwindow.h"

CommTcp::CommTcp(QString domain, int port, QString thread, MainWindow* mwin)
{
	this->domain = domain;
	this->port = port;
	this->thread = thread;
	this->mwin = mwin;
}

void CommTcp::doConnect()
{
	socket = new QTcpSocket(this);

	connect(socket, SIGNAL(connected()),this, SLOT(connected()));
	connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
	connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
	connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

	qDebug() << "connecting...";

	// this is not blocking call
	socket->connectToHost(domain, port);

	// we need to wait...
	if(!socket->waitForConnected(5000))
	{
		qDebug() << "Error: " << socket->errorString();
	}
}

void CommTcp::connected()
{
	qDebug() << "connected...";

	QByteArray send;
	send.append("<thread thread=\"" + thread + "\" version=\"20061206\" res_from=\"1000\"/>");
	send.append('\0');
	socket->write(send);
}

void CommTcp::disconnected()
{
	qDebug() << "disconnected...";
}

void CommTcp::bytesWritten(qint64 bytes)
{
	qDebug() << bytes << " bytes written...";
}

void CommTcp::readyRead()
{
	QByteArray rawcomm = socket->readAll();

	mwin->insLog(QString(rawcomm));

	if (rawcomm.indexOf("<thread") != -1) {
		return;
	}

	int noSt = rawcomm.indexOf("no=\"") + 4;
	int noEd = rawcomm.indexOf("\"", noSt);
	int num = rawcomm.mid(noSt, noEd-noSt).toInt();

	int dateSt = rawcomm.indexOf("date=\"") + 6;
	int dateEd = rawcomm.indexOf("\"", dateSt);
	int udate = rawcomm.mid(dateSt, dateEd-dateSt).toInt();

	QDateTime timestamp;
	timestamp.setTime_t(udate);
	QString date = timestamp.toString(Qt::SystemLocaleShortDate);

	int userSt = rawcomm.indexOf("user_id=\"") + 9;
	int userEd = rawcomm.indexOf("\"", userSt);
	QString user = QString(rawcomm.mid(userSt, userEd-userSt));

	int commSt = rawcomm.indexOf(">") + 1;
	int commEd = rawcomm.indexOf("</chat>");
	QString comm = QString(rawcomm.mid(commSt,commEd-commSt));

	//"/disconnect"

	mwin->insComment(num,user,comm,date);
}
