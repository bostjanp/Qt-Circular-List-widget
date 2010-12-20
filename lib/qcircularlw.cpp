/****************************************************************************
**
** Copyright (C) 2010 Bostjan Pislar.
** All rights reserved.
** Contact: Bostjan Pislar (bostjan.pislar@gmail.com)
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
****************************************************************************/

#include <QDebug>
#include <QScrollBar>
#include <QPainter>
#include "qcircularlw.h"

QCircularLW::QCircularLW(QWidget *parent)
	:QAbstractScrollArea(parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	initData();
	initUi();
}

QCircularLW::~QCircularLW()
{
	_lItems.clear();
	_iMaxItemsDisplay	= 666;
	_iScrollOffset		= 2;
	_iCurrentRow		= -1;
}

// data section 
void QCircularLW::addItem(QLabel *item)
{
	_lItems.append(item);
	qDebug() <<"item h: " << item->height() << " w: " << item->width();
	addToFrame(_lItems.count() - 1);
	_bNewItem=true;
}

void QCircularLW::addItem(const QString &label)
{
	addItem(new QLabel(label));
}

void QCircularLW::addItems (const QStringList & labels)
{
	QListIterator<QString> it(labels);
	while (it.hasNext()) addItem(it.next());	
}

void QCircularLW::insertItem(int row,QLabel *item)
{
	if (row <0) row=0;
	else if (row > _lItems.count()) row=_lItems.count();

	_lItems.insert(row,item);
	addToFrame(row);
	_bNewItem=true;
}

void QCircularLW::insertItem(int row,const QString &label)
{
	insertItem(row,new QLabel(label));
}

void QCircularLW::insertItems(int row,const QStringList &labels)
{
	if (row <0) row=0;
	else if (row > _lItems.count()) row=_lItems.count();

	QListIterator<QString> it(labels);
	while (it.hasNext()) insertItem(row++,it.next());	
}

QLabel *QCircularLW::takeItem(int row)
{
	if ( _lItems.isEmpty() ) return NULL;

	_bNewItem=true;
	if (row < 0) return _lItems.takeFirst();
	else if ( row > _lItems.count() ) return _lItems.takeLast();
	else return _lItems.takeAt(row);
}

void QCircularLW::clear()
{
	if (!_lItems.isEmpty())	_lItems.clear();
	_iCurrentRow=-1;
}

int QCircularLW::count() const
{
	return _lItems.count();
}

void QCircularLW::initData()
{
	_lItems.clear();
	_lFakeE.clear();
	_lFakeS.clear();
	_iCurrentRow		= -1;
}

void QCircularLW::setCurrentRow(int row)
{
	if (_lItems.isEmpty()) return;

	if (row < 0) row=0;
	else if ( row >= _lItems.count() ) row=_lItems.count()-1;
	
	if (_iCurrentRow<0) currentItemChanged(_lItems.at(row),0);
	else  currentItemChanged(_lItems.at(row),_lItems.at(_iCurrentRow));
	_iCurrentRow=row;
}

int QCircularLW::currentRow()
{
	return _iCurrentRow;
}

void QCircularLW::setCurrentItem(QLabel *item)
{
	if (_lItems.isEmpty()) return;

	int i= _lItems.indexOf(item);

	if (i<0) return;

	setCurrentRow(i);
}

QLabel *QCircularLW::currentItem()
{
	return _lItems.at(_iCurrentRow);
}

QLabel *QCircularLW::item(int row)
{
	if (_lItems.isEmpty()) return NULL;
	if (row>=0 && row < _lItems.count()) return _lItems.at(row);
	else return NULL;
}

int QCircularLW::row(QLabel *item)
{
	if (_lItems.isEmpty()) return -1;

	return _lItems.indexOf(item,0);
}

void QCircularLW::updateFakeData()
{
	if (_iMaxItemsDisplay > _lItems.count()) 
	{
		qDebug() << "items: " << _lItems.count() << " max disp: " << _iMaxItemsDisplay;
		while(_lFakeS.count()>0) delete _lFakeS.takeFirst();
		while(_lFakeE.count()>0) delete _lFakeE.takeFirst();
		return;
	}

	_bNewItem=true;
	QListIterator<QLabel *>i(_lItems);
	QLabel *item;
	// at start
	while(_lFakeS.count()>0) delete _lFakeS.takeFirst();

	i.findNext(this->item(_lItems.count() - _iMaxItemsDisplay/2));
	i.previous();
	item=i.peekPrevious();

	qDebug()<< "starting item: " << item->text();
	while(i.hasNext())
	{
		item = i.next();
		_lFakeS.append(new QLabel(_pfCanvas));
		(_lFakeS.last())->setText(item->text());
		(_lFakeS.last())->setGeometry(item->geometry());
	}

	// at end
	while(_lFakeE.count()>0) delete _lFakeE.takeFirst();
	i.toFront();
	while(i.hasNext() && i.peekNext() != this->item(_iMaxItemsDisplay/2) )
	{
		item = i.next();
		_lFakeE.append(new QLabel(_pfCanvas));
		(_lFakeE.last())->setText(item->text());
		(_lFakeE.last())->setGeometry(item->geometry());
	}
}
// data section 

// ui section
void QCircularLW::initUi()
{
	_iMaxItemsDisplay	= 666;
	_iScrollOffset		= 2;
	_bNewItem			= false;
	
	_pfCanvas = new QFrame(viewport());
	_pfCanvas->setFrameRect(viewport()->rect());

}

QPoint QCircularLW::drawItems(QList <QLabel *> list, QPoint startPos)
{
	QListIterator<QLabel *>i(list);
	QLabel *item;

	i.toFront();
	while(i.hasNext())
	{
		item = i.next();
//		qDebug()<<item->pos() << "FB.item: " <<item->text() << startPos;
		item->move(startPos);
		item->show();
		startPos.setY(startPos.y()+item->height());
	}

	return startPos;
}

void QCircularLW::paintEvent(QPaintEvent *event)
{
	if (_bNewItem)
	{
		_bNewItem=false;
		
		QListIterator<QLabel *>i(_lFakeS);
		QPoint p(0,0);
		// fake start
		p=drawItems(_lFakeS,p);
		// real
		p=drawItems(_lItems,p);
		// fake end
		p=drawItems(_lFakeE,p);
		
		_pfCanvas->setFixedHeight(p.y()+_lFakeE.last()->height());
	}
	centerPosition(currentItem());
}

void QCircularLW::keyPressEvent(QKeyEvent *event)
{
	bool DoBase = true;

	switch(event->key())
	{
		case Qt::Key_Down:
//	qDebug() << "keyPressEvent Down";
			//scrollContentsBy(0,10);
			//_pfCanvas->move(0,10);
			if (currentRow()==_lItems.count()-1) 
			{
				if(_iMaxItemsDisplay<_lItems.count()) setCurrentRow(0);
			}
			else setCurrentRow(currentRow()+1);
			DoBase=false;
			break;
		case Qt::Key_Up:
//	qDebug() << "keyPressEvent Up";
			//scrollContentsBy(0,-10);
			//_pfCanvas->move(0,-10);
			if (currentRow()==0) 
			{
				if(_iMaxItemsDisplay<_lItems.count()) setCurrentRow(_lItems.count()-1);
			}
			else setCurrentRow(currentRow()-1);
			DoBase = false;
			break;
		case Qt::Key_F:
			{
				qDebug()<<"rm item: " << takeItem(currentRow())->text();
				setCurrentRow(currentRow());
				_bNewItem=true;
				
			break;
			}
		default:
		break;
	}

	// perform the normal behavior
	if (DoBase)	QAbstractScrollArea::keyPressEvent(event);
}

void QCircularLW::resizeEvent(QResizeEvent *event)
{
	qDebug()<<"resizeEvent";
	QRect r=_pfCanvas->geometry();	

	r=_pfCanvas->geometry();
	if (r.width() < viewport()->width())
	{
		r.setWidth(viewport()->width());
		_pfCanvas->setGeometry(r);

		QListIterator<QLabel *>i(_lItems);
		QLabel *item;
		while(i.hasNext())
		{
			item = i.next();
			r=item->geometry();
			r.setWidth(_pfCanvas->width());
			item->setGeometry(r);
		}
	}
//	qDebug()<<"frame: " << _pfCanvas->geometry() << " view: " << viewport()->geometry();
//	centerPosition(currentItem());
	setMaxItemDisplay();
	updateFakeData();
	QAbstractScrollArea::resizeEvent(event);
}

void QCircularLW::wheelEvent(QWheelEvent *event)
{
	int iStep = (event->delta()/8)/15;
	
	qDebug() << "weelEvent: delta=" << event->delta() << " step= " << iStep;
	if (iStep==1)	keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier,""));
	else 				keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier,""));
}

void QCircularLW::addToFrame(int row)
{
	QLabel *item = _lItems.at(row);
//	qDebug()<< " item: " <<item->text() << " frame size: " << _pfCanvas->size();
	item->setParent(_pfCanvas);
	QFontMetrics fm(item->font());
	item->setGeometry(0,-20,_pfCanvas->width(),fm.height());
//	item->hide();
}

void	QCircularLW::currentItemChanged (QLabel *current, QLabel *previous)
{
	if (previous !=NULL)
	{
		previous->setBackgroundRole(QPalette::Base);
		previous->setForegroundRole(QPalette::Text);
		previous->setAutoFillBackground(true);
	}	

	current->setBackgroundRole(QPalette::Highlight);
	current->setForegroundRole(QPalette::HighlightedText);
	current->setAutoFillBackground(true);

	centerPosition(current);
}

void QCircularLW::centerPosition(QLabel *item)
{
	int iCenter= viewport()->size().height()/2 - item->size().height()/2;
//	qDebug() <<"center: " << iCenter << "frame: " << _pfCanvas->pos() << "item: " << item->pos();

	_pfCanvas->move(0,iCenter - item->pos().y());
}

void QCircularLW::setMaxItemDisplay()
{
	int old = _iMaxItemsDisplay;
	_iMaxItemsDisplay=viewport()->size().height()/currentItem()->size().height() +1;
	if (old != _iMaxItemsDisplay) _bNewItem=true;
//	qDebug() << "max item: " << _iMaxItemsDisplay << " count: " << _lItems.count();
}
// ui section
