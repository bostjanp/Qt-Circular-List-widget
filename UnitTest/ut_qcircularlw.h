/*! 
 \file ut_qcircularlw.h
 \brief File contains class definition for unit testing of circular list base on QListWidget
 \author Bostjan Pislar
 \version 0.1
 \date 2010
*/

#ifndef UT_QCIRCULARLW_H
#define  UT_QCIRCULARLW_H

#include <QTest>
#include <QtCore>
#include "qcircularlw.h"

/// \brief Declarations of tests and suporting functions and variables
class utQCircularLW : public QObject
{
   Q_OBJECT
private:
	QCircularLW *_ptstw;		//!< pointer to QCircularLW - the object exposed to tests!

	int _iItems;						//!< number of items
	QList <QLabel *> _lItems;		//!< container of items for tests
//	int _iMaxDisplayed;				//!< max items in viewport


private slots:

	void Count();					//!< test count() function
	
	// add functions
	void AddLabel();				//!< test addItem(QString&)	
	void AddItem();				//!< test addItem(QListWidgetItem *item)
	void AddList();				//!< test addItems(QStringList &labels)

	void InsertLabel();			//!< test insertItem(QString &label)
	void InsertItem();			//!< test insertItem(QListWidgetItem *item)
	void InsertList();			//!< test insertItems(QStringList &labels)

	void TakeItem();				//!< test takeItem(int row);

	void ChangeRow();				//!< test setCurrentRow and currentRow
	void ChangeItem();			//!< test setCurrentItem and currentItem

	void ReturnItem();			//!< test item(int row)
	void ReturnRow();				//!< test row(QLabel *item)

	void KeyTest();				//!< testing the movement

	void initTestCase(); 		//!< will be called before the first testfunction is executed.
	void cleanupTestCase();		//!< will be called after the last testfunction was executed.
	
	void init(); 					//!< will be called before each testfunction is executed.
	void cleanup(); 				//!< will be called after every testfunction.

public:
	utQCircularLW();		//!< constructor
	~utQCircularLW();		//!< destructor
};
#endif //UT_QCIRCULARLW_H

/*! \class utQCircularLW
 *
*/

/*! \var	QCirclularLW* utQCircularLW::_ptstw
 *
 * Pointer to tested class \sa QCircularLW.
*/

/*! \var	QCirclularLW* utQCircularLW::_iItems
 *
 * Variable holds the number of added/inserted items
*/

/*! \fn 	void utQCircularLW::Count()
 *
 * Test for the function #QCirclularLW::count(). Returned value shoud be the number of real items.
*/

/*! \fn 	void utQCircularLW::AddLabel()
 *
 * Testing function #QCirclularLW::addItem(QString &label) and #Count()
*/

/*! \fn 	void utQCircularLW::AddItem()
 *
 * Testing function #QCirclularLW::addItem(QLabel *item) and #Count();
*/

/*! \fn 	void utQCircularLW::AddList()
 * 
 * Testing function #QCirclularLW::addItems(QStringList &labels) and #Count();
*/

/*! \fn 	void utQCircularLW::InsertLabel()
 *
 * Testing function #QCirclularLW::insertItem(QString &label) and #Count();
*/

/*! \fn 	void utQCircularLW::InsertItem()
 *
 * Testing function #QCirclularLW::insertItem(QLabel *item) and #Count();
*/

/*! \fn 	void utQCircularLW::InsertList()
 *
 * Testing function #QCirclularLW::insertItem(QStringList &labels) and #Count();
*/


/*! \fn 	void utQCircularLW::utQCircularLW()
 *
 * Default constructor initilaize pointer.
*/

/*! \fn 	void utQCircularLW::~utQCircularLW()
 *
 * Default destructor delet pointer.
*/

/*! \fn 	void utQCircularLW::initTestCase()
 *
 * This function populate QCircularLW with elements and sets it size to (150,100)
*/

/*! \fn 	void utQCircularLW::cleanupTestCase()
*/

/*! \fn 	void utQCircularLW::init()
*/

/*! \fn 	void utQCircularLW::cleanup()
*/
