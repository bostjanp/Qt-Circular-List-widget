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

/*! 
 \file qcircularlw.h
 \brief class definition for circular list base on QListWidget
 \author Bostjan Pislar
 \version 0.1
 \date 2010

 \todo remove item last first 
 \todo sort items
*/

#ifndef _CIRCULARLW_H_
#define _CIRCULARLW_H_

#include <QAbstractScrollArea>
#include <QScrollArea>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QLabel>

/// \brief Declarations for manipulating QCircularLW widget
class QCircularLW : public QAbstractScrollArea
{
	Q_OBJECT
private:
	QList<QLabel *> _lItems;		//!< container of elements
	QList<QLabel *> _lFakeS;		//!< container of elements - fake at start
	QList<QLabel *> _lFakeE;		//!< container of elements - fake at end
	QFrame *_pfCanvas;				//!< widget that holds items

	int _iScrollOffset;					//!< number of items to add to pageStep
	int _iMaxItemsDisplay;				//!< number of elements in viewport
	int _iCurrentRow;						//!< row number of selected item
	bool _bNewItem;						//!< new item added

public:
	QCircularLW(QWidget *parent =0);	//!< default constructor
	virtual ~QCircularLW();

//	data section
	void addItem(QLabel *item);							//!< append an item at the end of the list
	void addItem(const QString &label);					//!< append an item at the end of the list
	void addItems (const QStringList & labels);		//!< append a list of items at the end of the list

	void insertItem(int row, QLabel *item);						//!< insert an item at specified position
	void insertItem(int row,const QString &label);				//!< insert an item at specified position
	void insertItems(int row,const QStringList &labels);		//!< insert an item at specified position

	QLabel *takeItem(int row);		//!< function remove selected item from list and returns it
	void clear();						//!< function removes all elements from list
	int count() const;				//!< function returns number of elements

	void setCurrentRow(int row);			//!< set current selected row
	int currentRow();							//!< return selected item row

	void setCurrentItem(QLabel *item);	//!< set current selected item
	QLabel *currentItem();					//!< return current selected item

	QLabel *item(int row);					//!< return item at row
	int row(QLabel *item);			//!< return row of item

//	data section
private:
	void initData();		//!< initialization of data variables
	void initUi();			//!< initialization of UI elements
	void updateFakeData();	//!< update fake items
//	data section
// ui section
	void addToFrame(int row);	//!< function add item at row position to frame
protected:
	virtual void keyPressEvent(QKeyEvent *event);		//!< overridden function
	virtual void paintEvent(QPaintEvent *event);			//!< overridden function
	virtual void resizeEvent(QResizeEvent *event);		//!< overridden function
	virtual void wheelEvent(QWheelEvent *event);			//!< overridden function

	virtual void centerPosition(QLabel *item);		//!< selected item put in center of viewport 
	virtual void setMaxItemDisplay();					//!< max numbert of items in viewport
//private slots:
//signals:
	void	currentItemChanged ( QLabel * current, QLabel * previous );		//!< visual fx when changing selection
// ui section
};
#endif //_CIRCULARLW_H_

/*! \class QCircularLW
 *
 * The QCircularLW class derivered from QListWidget class ( Qt 4.6.3 ). Its purpose is to have a circular list.\n
 * The view is a cilinder style - infinitum scroll up and down. Selected item is always at the center of viewport.\n
 * A few words about the logic:\n
 * it has two kind of items - real and fake. Real items are like in QListWidget. Fake items are clones of real items and they are 
 * inserted at the begining and at the end of the list of real items. That's how you get an infinitum scroll.\n
 *	For example: Viewport can display 5 items. The list needs 3 fake items at the begining of the list (befor first real item) and 
 *	3 fake items at the end (after the last real item) of the list. No matter how many real items are in the list! That means that 
 *	the number of fake items depends on size of the viewport.
 *
 * \todo error if there are less real items than the number of items that could be displayed in viewport - size of the verticalScroll()->pageSize()
 * \todo hidden items not suported
 * \todo movement of the mouse while button is pressed 
*/

/*! \var int QCircularLW::_iMaxItemsDisplay
 *
 * This vartiable holds the number of items that can be displayed - the number of items in the viewport
*/

/*! \fn void QCircularLW::addItem(QLabel *item)
 *
 * \param item pointer to QLabel
 *
 * This function adds an item at the end of the list of real items.
 * It appends an item to the #_lItems list.\n
 * Then appends the item to the  #_pfCanvas with function #addToFrame.
*/

/*! \fn void QCircularLW::addItem(const QString &label)
 * 
 * \param label text that will be displayed in the list
 *
 * This function is a wrapper of #addItem(QLabel *item).
*/

/*! \fn void QCircularLW::addItems (const QStringList & labels)
 * 
 * \param labels text that will be display in the list
 *
 * This function appends a list of QStrring items to the list #_lItems.\n
 * It takes items from QStringList one by one and appends them to the list #_lItems with the function #addItem(QLabel *item)
 *
*/

/*! \fn void QCircularLW::addToFrame(int row)
 * 
 * \param row index of the item in #_lItems
 * 
 * Function take the item at position row of the _lItems and inserts it tho the frame #_pfCanvas
*/

/*! \fn virtual void QCircularLW::centerPosition(QLabel *item)
 * 
 * \param item to be set in the middle of the widget
 *
 * Function moves the #_pfCanvas so the selected item is in the middle of the viewport
*/

/*! \fn 	void QCircularLW::clear()
 *
 * Function clears all items from the #_lItems list and sets the #_iCurrentRow to -1.
*/

/*! \fn int QCircularLW::count() const;
 *
 * \returns number of items in the list
 *
 * Function returns the number of items in #_lItems.
*/

/*! \fn 	QLabel *QCircularLW::currentItem()
 *
 * \return pointer to item
 *
 * Function returns a pointer to the current selected item.
*/

/*! \fn 	void QCircularLW::currentItemChanged ( QLabel * current, QLabel * previous )
 *
 * Function chane the visual fx of selected item and set the current selected item position at the center of viewport.\n
 * At this point it is implemented setBackgroundRole and setForegroundRole
*/

/*! \fn 	int QCircularLW::currentRow()
 *
 * \returns row number of the item
 *
 * Function returns row position of the selected item.
*/

/*! \fn 	void QCircularLW::initData()
 *
 * Function initialize data part of widget
*/

/*! \fn 	void QCircularLW::initUi()
 *
 * Function initialize UI part of the widget
 */

/*! \fn 	void QCircularLW::insertItems(int row, QLabel *item)
 *
 * \param row index of the row to insert an item to the list
 * \param Qlabel text that will be display in the list
 *
 * Function inserts an item at the position row in the #_lItems. 
 * Then inserts the item to the  #_pfCanvas with function #addToFrame.
*/

/*! \fn 	void QCircularLW::insertItem(int row,const QString &label)
 *
 * \param row index of the row to insert an item \param label text that will be
 * display in the list
 *
 * This function is a wrapper to the #insertItem(int row, const QLabel *item)
*/

/*! \fn 	void QCircularLW::insertItem(int row,QListWidgetItem *item)
 *
 * \param row index of the row to insert an item 
 * \param item pointer to QListWidgetItem
 *
 * This function is a wrapper to the #insertItem(int row, const QLabel *item)
 * It takes items from QStringList one by one and inserts them to the list #_lItems with the function #insertItem(int row,Qlabel *item)
 * startin at position row.
*/

/*! \fn 	QLabel *QCircularLW::item(int row)
 *
 * \returns pointer to item
 *
 * Function return a pointer to item at position row.
 */

/*! \fn 	virtual void QCircularLW::keyPressEvent(QKeyEvent *event)
 *
 * \param event event from keyboard that has to be porcessed
 *
 * Function catchs up and down keys and moves the #_pfCanvas frame up or down of the size of an item.
*/

/*! \fn virtual void QCircularLW::paintEvent(QPaintEvent *event)
 *
 * \event paint event
 *
 * Function repaints the #_pfCanvas if it has an new item and position the selected item to the center of viewport.
 * How does it work?
 * - draw the fake list of items from #_lFakeS at the begining of the #_pfCanvas
 * - draw the real list of items from the #_lItems
 * - draw the real list of items from the #_lFakeE
 * 
 */

/*! \fn 	virtual void QCircularLW::resizeEvent(QResizeEvent *event)
 *
 * \param event resize event
 *
 * Function resize the viewport and its items width. After that calculate the number of max items in viewport #setMaxItemDisplay.
 * At the end updates the fake items.
*/

/*! \fn int QCircularLW::row(QLabel *item)
 *
 * \param item pointer to item 
 * \returns position of item
 *
 * Function gets the item position in the list #_lItems.
*/

/*! \fn void QCircularLW::setCurrentRow(int row)
 * 
 * \param number of the item row
 *
 * Function sets the item at row position as selected.
 */

/*! \fn 	virtual void QCircularLW::setMaxItemDisplay()
 *
 * Function calculates the number of items displayed in the viewport.
 */

/*! \fn 	QLabel *QCircularLW::takeItem(int row)
 *
 * \param row row number of item
 * \returns	QLabel removed item
 *
 * This function remove an item from the list #_lItems. If this item has a fake item it removes the fake item too 
 * and inserts another item in fake list (#_lFakeS, #_lFakeE).
*/

/*! \fn void QCircularLW::updateFakeData()
 *
 * Function updates items in fake lists (#_lFakeS, #_lFakeE).
 */

/*! \fn 	virtual void QCircularLW::wheelEvent(QWheelEvent *event)
 *
 * \param event event created by the mouse wheel
 *
 * This function scroll the items by one up/down while the selected item stays in the center of the viewport.
*/
