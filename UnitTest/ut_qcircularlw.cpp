#include "ut_qcircularlw.h"
#include <QDebug>

utQCircularLW::utQCircularLW()
{
	_ptstw = new QCircularLW();
}

utQCircularLW::~utQCircularLW()
{
	if (_ptstw != NULL ) delete _ptstw;

	_ptstw = NULL;
}

void utQCircularLW::Count()
{
	QCOMPARE(_ptstw->count(),_lItems.count());
}

void utQCircularLW::AddLabel()
{
//	qDebug()<<"addLabel";
	_lItems.append(new QLabel("addLabel 01"));
	_ptstw->addItem("addLabel 01");
	_lItems.append(new QLabel("addLabel 02"));
	_ptstw->addItem("addLabel 02");

	Count();
}

void utQCircularLW::AddItem()
{
	_lItems.append(new QLabel("addItem 01"));
	_ptstw->addItem(new QLabel("addItem 01"));
	_lItems.append(new QLabel("addItem 02"));
	_ptstw->addItem(new QLabel("addItem 02"));

	Count();
}

void utQCircularLW::AddList()
{
	QStringList list;
	list << "addList 01" << "addList 02" << "addList 03";

	_lItems.append(new QLabel(list.at(0)));
	_lItems.append(new QLabel(list.at(1)));
	_lItems.append(new QLabel(list.at(2)));
	_ptstw->addItems(list);  

	Count();
}

void utQCircularLW::InsertLabel()
{
	_lItems.insert(0,new QLabel("insertLabel 00"));
	_ptstw->insertItem(0,"insertLabel 00");
	_lItems.insert(8,new QLabel("insertLabel 08"));
	_ptstw->insertItem(8,"insertLabel 08");
	_lItems.insert(_lItems.count(),new QLabel("insertLabel count"));
	_ptstw->insertItem(_ptstw->count(),"insertLabel count");

	Count();
}

void utQCircularLW::InsertItem()
{
	_lItems.insert(0,new QLabel("insertItem 00"));
	_ptstw->insertItem(0,new QLabel("insertItem 00"));
	_lItems.insert(8,new QLabel("insertItem 08"));
	_ptstw->insertItem(8,new QLabel("insertItem 08"));
	_lItems.insert(_lItems.count(),new QLabel("insertItem count"));
	_ptstw->insertItem(_ptstw->count(),new QLabel("insertItem count"));

	Count();
}

void utQCircularLW::InsertList()
{
	QStringList list;
	list << "insertList 05" << "insertList 06" << "insertList 07";

	_lItems.insert(5,new QLabel(list.at(0)));
	_lItems.insert(6,new QLabel(list.at(1)));
	_lItems.insert(7,new QLabel(list.at(1)));
	_ptstw->insertItems(5,list);  

	Count();
}

void utQCircularLW::TakeItem()
{

	QCOMPARE(_ptstw->takeItem(0), _lItems.takeFirst());
	QCOMPARE(_ptstw->takeItem(5), _lItems.takeAt(5));
	QCOMPARE(_ptstw->takeItem(_ptstw->count()-1), _lItems.takeLast());
	QCOMPARE(_ptstw->takeItem(_ptstw->count()-3), _lItems.takeAt(_lItems.count()-3));

	Count();
}

void utQCircularLW::ChangeRow()
{
	for (int i=0; i<_ptstw->count(); i++)
	{
		_ptstw->setCurrentRow(i);
		QCOMPARE(_ptstw->currentRow(),i);
	}

	_ptstw->setCurrentRow(_ptstw->count()+3);
	QCOMPARE(_ptstw->currentRow(), _ptstw->count()-1);

	_ptstw->setCurrentRow(-2);
	QCOMPARE(_ptstw->currentRow(),0);
}

void utQCircularLW::ChangeItem()
{
	QListIterator<QLabel *> i(_lItems);

	while (i.hasNext())
	{
		_ptstw->setCurrentItem(i.peekNext());
		QCOMPARE(_ptstw->currentItem(),i.next());
	}

	QLabel tmp("eroror");
	_ptstw->setCurrentItem(&tmp);

	QEXPECT_FAIL("","item does not exitst",Continue);
	QCOMPARE(_ptstw->currentItem(),&tmp);
//	QCOMPARE(_ptstw->currentItem(),i.previous());
}

void utQCircularLW::ReturnItem()
{
	for (int i=0;i<_lItems.count(); i++)
		QCOMPARE(_ptstw->item(i),_lItems.at(i));
}

void utQCircularLW::ReturnRow()
{
	QListIterator<QLabel *> i(_lItems);

	i.toFront();
	while (i.hasNext())
	{
		QCOMPARE(_ptstw->row( i.peekNext() ), _lItems.indexOf( i.peekNext() ) );
		i.next();
	}
}

void utQCircularLW::KeyTest()
{
	int row=0, i=0;
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

	qDebug()<<"current row: " <<_ptstw->currentRow();
	_ptstw->setCurrentRow(0);
	QTest::keyClick(_ptstw,Qt::Key_Up);
	QCOMPARE(_ptstw->currentRow(),_ptstw->count()-1);
	QTest::keyClick(_ptstw,Qt::Key_Up);
	QCOMPARE(_ptstw->currentRow(),_ptstw->count()-2);
	_ptstw->setCurrentRow(_ptstw->count()-1);
	QTest::keyClick(_ptstw,Qt::Key_Down);
	QCOMPARE(_ptstw->currentRow(),0);
	QTest::keyClick(_ptstw,Qt::Key_Down);
	QCOMPARE(_ptstw->currentRow(),1);


	_ptstw->setCurrentRow(0);
	while (i<1000)
	{
		if (qrand()%2)
		{
			QTest::keyClick(_ptstw,Qt::Key_Down);
			row++;			
			if(row==_ptstw->count()) row=0;
		}
		else
		{
			QTest::keyClick(_ptstw,Qt::Key_Up);
			row--;
			if (row<0)row=_lItems.count()-1;
		}

		QCOMPARE(_ptstw->currentRow(),row);
		i++;
	}

}

void utQCircularLW::initTestCase() 
{
//	_ptstw->setGeometry(100,100,150,100);
//	_iMaxDisplayed=12;
//	_ptstw->show();
}

void utQCircularLW::cleanupTestCase()
{
	_lItems.clear();
	_ptstw->clear();
	Count();
}

void utQCircularLW::init()
{
//	qDebug()<<" init...";
	_lItems.append(new QLabel("init 00"));
	_lItems.append(new QLabel("init 01"));
	_lItems.append(new QLabel("init 02"));
	_lItems.append(new QLabel("init 03"));
	_lItems.append(new QLabel("init 04"));
	_lItems.append(new QLabel("init 05"));
	_lItems.append(new QLabel("init 06"));
	_lItems.append(new QLabel("init 07"));
	_lItems.append(new QLabel("init 08"));
	_lItems.append(new QLabel("init 09"));
	_lItems.append(new QLabel("init 10"));
	_lItems.append(new QLabel("init 11"));
	_lItems.append(new QLabel("init 12"));
	_lItems.append(new QLabel("init 13"));
	_lItems.append(new QLabel("init 14"));

	for(int i=0;i<_lItems.count();i++)
	_ptstw->addItem(_lItems.at(i));
	_ptstw->setCurrentRow(0);
}

void utQCircularLW::cleanup()
{
//	qDebug()<<" cleanup...";
	_lItems.clear();
	_ptstw->clear();
}

QTEST_MAIN(utQCircularLW)
