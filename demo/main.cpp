#include <QApplication>
#include <QObject>
#include <QDebug>
#include <QPoint>
#include <QListWidgetItem>

#include "qcircularlw.h"

int main (int argc, char *argv[])
{
	QApplication a(argc,argv);	

	QCircularLW clv;

	clv.setGeometry(1500,100,150,200);
	clv.addItem(QObject::tr("Item 01"));
	clv.addItem(QObject::tr("Item 02"));
	clv.addItem(QObject::tr("Item 03"));
	clv.addItem(QObject::tr("Item 04"));
	clv.addItem(QObject::tr("Item 05"));
	clv.addItem(QObject::tr("Item 06"));
	clv.addItem(QObject::tr("Item 07"));
	clv.addItem(QObject::tr("Item 09"));
	clv.addItem(QObject::tr("Item 10"));
	clv.addItem(QObject::tr("Item 11"));
	clv.addItem(QObject::tr("Item 12"));
	clv.addItem(QObject::tr("Item 13"));
	clv.addItem(QObject::tr("Item 14"));
	clv.addItem(QObject::tr("Item 15"));
	clv.addItem(QObject::tr("Item 16"));
	clv.addItem(QObject::tr("Item 17"));
	clv.addItem(QObject::tr("Item 18"));
	clv.addItem(QObject::tr("Item 19"));
	clv.addItem(QObject::tr("Item 20"));
	clv.addItem(QObject::tr("Item 21"));
	clv.addItem(QObject::tr("Item 22"));
	clv.addItem(QObject::tr("Item 23"));
	clv.addItem(QObject::tr("Item 24"));
	clv.addItem(QObject::tr("Item 25"));


	clv.insertItem(0,QObject::tr("insert 0"));
	clv.insertItem(4,QObject::tr("insert 4"));
	clv.insertItem(12,QObject::tr("insert 12"));
	clv.insertItem(15,QObject::tr("insert 15"));
	clv.insertItem(23,QObject::tr("insert 23"));
#ifdef DEBUG
	qDebug()<<"contents h:"<< clv.contentsRect().height()<< " w:"<<clv.contentsRect().width();
	qDebug()<<"widget h:"<< clv.size().height()<< " w:"<<clv.size().width();
	qDebug()<<"set current row to 0";
#endif
	clv.setCurrentRow(0);
	qDebug()<<"show";
	clv.show();

	return a.exec();
}
