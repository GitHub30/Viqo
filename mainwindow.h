#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkCookie>
#include <QList>
#include <QVariant>
#include <QNetworkReply>
#include <QIODevice>
#include <QtNetwork>

#include "commtcp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void insComment(int num, QString user, QString comm, QString date);
	void insLog(QString log);

private slots:
	void on_pushButton_clicked();
	void finished();

private:
	void getAPI(QString user_id, QString broad_id);
	void getComment();

	CommTcp* commtcp;

	Ui::MainWindow *ui;
	QNetworkReply* reply;
	QByteArray m_data;
	QNetworkAccessManager* mManager;
	QString addr, thread;
	int port;
};

#endif // MAINWINDOW_H
