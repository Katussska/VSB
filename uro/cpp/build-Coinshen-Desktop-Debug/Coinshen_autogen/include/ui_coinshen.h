/********************************************************************************
** Form generated from reading UI file 'coinshen.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COINSHEN_H
#define UI_COINSHEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Coinshen
{
public:
    QAction *actionExit;
    QAction *actionCreator;
    QAction *actionDescription;
    QWidget *centralwidget;
    QTabWidget *tabs;
    QWidget *tab_add;
    QLabel *l_addNew;
    QTabWidget *tabs_add;
    QWidget *tab_transaction;
    QLabel *l_transaction;
    QRadioButton *rt_income;
    QRadioButton *rt_expense;
    QComboBox *boxt_accounts;
    QLabel *lt_account;
    QComboBox *boxt_category;
    QLabel *lt_category;
    QLabel *lt_amount;
    QLineEdit *tt_description;
    QLabel *lt_description;
    QDateEdit *et_date;
    QLabel *lt_date;
    QPushButton *bt_add;
    QLineEdit *tt_amount;
    QWidget *tab_category;
    QLabel *l_category;
    QLabel *l_account;
    QLineEdit *ta_name;
    QLabel *la_name;
    QLabel *la_balance;
    QPushButton *bc_add;
    QPushButton *ba_add;
    QLineEdit *ta_balance;
    QLineEdit *tc_name;
    QLabel *lc_budget;
    QLineEdit *tc_budget;
    QLabel *lc_name;
    QWidget *tab_filter;
    QLabel *l_filter;
    QLabel *lf_account;
    QPushButton *bf_filter;
    QDateEdit *ef_untilDate;
    QComboBox *boxf_accounts;
    QRadioButton *rf_expense;
    QLabel *lf_category;
    QLabel *lf_until;
    QComboBox *boxf_categories;
    QRadioButton *rf_income;
    QDateEdit *ef_sinceDate;
    QLabel *lf_since;
    QLabel *lf_date;
    QTableView *tableView;
    QCalendarWidget *calendar;
    QMenuBar *menubar;
    QMenu *menuInfo;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Coinshen)
    {
        if (Coinshen->objectName().isEmpty())
            Coinshen->setObjectName("Coinshen");
        Coinshen->resize(806, 599);
        actionExit = new QAction(Coinshen);
        actionExit->setObjectName("actionExit");
        actionCreator = new QAction(Coinshen);
        actionCreator->setObjectName("actionCreator");
        actionDescription = new QAction(Coinshen);
        actionDescription->setObjectName("actionDescription");
        centralwidget = new QWidget(Coinshen);
        centralwidget->setObjectName("centralwidget");
        tabs = new QTabWidget(centralwidget);
        tabs->setObjectName("tabs");
        tabs->setGeometry(QRect(20, 30, 231, 521));
        tab_add = new QWidget();
        tab_add->setObjectName("tab_add");
        l_addNew = new QLabel(tab_add);
        l_addNew->setObjectName("l_addNew");
        l_addNew->setGeometry(QRect(90, 20, 61, 31));
        tabs_add = new QTabWidget(tab_add);
        tabs_add->setObjectName("tabs_add");
        tabs_add->setGeometry(QRect(-10, 60, 261, 461));
        tab_transaction = new QWidget();
        tab_transaction->setObjectName("tab_transaction");
        l_transaction = new QLabel(tab_transaction);
        l_transaction->setObjectName("l_transaction");
        l_transaction->setGeometry(QRect(80, 10, 81, 31));
        rt_income = new QRadioButton(tab_transaction);
        rt_income->setObjectName("rt_income");
        rt_income->setGeometry(QRect(30, 50, 71, 24));
        rt_expense = new QRadioButton(tab_transaction);
        rt_expense->setObjectName("rt_expense");
        rt_expense->setGeometry(QRect(120, 50, 81, 24));
        boxt_accounts = new QComboBox(tab_transaction);
        boxt_accounts->setObjectName("boxt_accounts");
        boxt_accounts->setGeometry(QRect(30, 130, 79, 26));
        lt_account = new QLabel(tab_transaction);
        lt_account->setObjectName("lt_account");
        lt_account->setGeometry(QRect(40, 90, 61, 31));
        boxt_category = new QComboBox(tab_transaction);
        boxt_category->setObjectName("boxt_category");
        boxt_category->setGeometry(QRect(130, 130, 79, 26));
        lt_category = new QLabel(tab_transaction);
        lt_category->setObjectName("lt_category");
        lt_category->setGeometry(QRect(140, 90, 61, 31));
        lt_amount = new QLabel(tab_transaction);
        lt_amount->setObjectName("lt_amount");
        lt_amount->setGeometry(QRect(40, 180, 61, 31));
        tt_description = new QLineEdit(tab_transaction);
        tt_description->setObjectName("tt_description");
        tt_description->setGeometry(QRect(70, 260, 113, 26));
        lt_description = new QLabel(tab_transaction);
        lt_description->setObjectName("lt_description");
        lt_description->setGeometry(QRect(90, 220, 81, 31));
        et_date = new QDateEdit(tab_transaction);
        et_date->setObjectName("et_date");
        et_date->setGeometry(QRect(100, 310, 110, 27));
        lt_date = new QLabel(tab_transaction);
        lt_date->setObjectName("lt_date");
        lt_date->setGeometry(QRect(40, 310, 31, 31));
        bt_add = new QPushButton(tab_transaction);
        bt_add->setObjectName("bt_add");
        bt_add->setGeometry(QRect(80, 360, 87, 26));
        tt_amount = new QLineEdit(tab_transaction);
        tt_amount->setObjectName("tt_amount");
        tt_amount->setGeometry(QRect(110, 180, 101, 26));
        tabs_add->addTab(tab_transaction, QString());
        tab_category = new QWidget();
        tab_category->setObjectName("tab_category");
        l_category = new QLabel(tab_category);
        l_category->setObjectName("l_category");
        l_category->setGeometry(QRect(90, 10, 61, 31));
        l_account = new QLabel(tab_category);
        l_account->setObjectName("l_account");
        l_account->setGeometry(QRect(90, 210, 61, 31));
        ta_name = new QLineEdit(tab_category);
        ta_name->setObjectName("ta_name");
        ta_name->setGeometry(QRect(90, 260, 121, 26));
        la_name = new QLabel(tab_category);
        la_name->setObjectName("la_name");
        la_name->setGeometry(QRect(30, 260, 41, 31));
        la_balance = new QLabel(tab_category);
        la_balance->setObjectName("la_balance");
        la_balance->setGeometry(QRect(30, 310, 61, 31));
        bc_add = new QPushButton(tab_category);
        bc_add->setObjectName("bc_add");
        bc_add->setGeometry(QRect(80, 160, 87, 26));
        ba_add = new QPushButton(tab_category);
        ba_add->setObjectName("ba_add");
        ba_add->setGeometry(QRect(80, 360, 87, 26));
        ta_balance = new QLineEdit(tab_category);
        ta_balance->setObjectName("ta_balance");
        ta_balance->setGeometry(QRect(90, 310, 121, 26));
        tc_name = new QLineEdit(tab_category);
        tc_name->setObjectName("tc_name");
        tc_name->setGeometry(QRect(90, 60, 121, 26));
        lc_budget = new QLabel(tab_category);
        lc_budget->setObjectName("lc_budget");
        lc_budget->setGeometry(QRect(30, 110, 61, 31));
        tc_budget = new QLineEdit(tab_category);
        tc_budget->setObjectName("tc_budget");
        tc_budget->setGeometry(QRect(90, 110, 121, 26));
        lc_name = new QLabel(tab_category);
        lc_name->setObjectName("lc_name");
        lc_name->setGeometry(QRect(30, 60, 41, 31));
        tabs_add->addTab(tab_category, QString());
        tabs->addTab(tab_add, QString());
        tab_filter = new QWidget();
        tab_filter->setObjectName("tab_filter");
        l_filter = new QLabel(tab_filter);
        l_filter->setObjectName("l_filter");
        l_filter->setGeometry(QRect(90, 20, 41, 31));
        lf_account = new QLabel(tab_filter);
        lf_account->setObjectName("lf_account");
        lf_account->setGeometry(QRect(40, 140, 61, 31));
        bf_filter = new QPushButton(tab_filter);
        bf_filter->setObjectName("bf_filter");
        bf_filter->setGeometry(QRect(70, 430, 87, 26));
        ef_untilDate = new QDateEdit(tab_filter);
        ef_untilDate->setObjectName("ef_untilDate");
        ef_untilDate->setGeometry(QRect(90, 350, 110, 27));
        boxf_accounts = new QComboBox(tab_filter);
        boxf_accounts->setObjectName("boxf_accounts");
        boxf_accounts->setGeometry(QRect(30, 180, 79, 26));
        rf_expense = new QRadioButton(tab_filter);
        rf_expense->setObjectName("rf_expense");
        rf_expense->setGeometry(QRect(120, 80, 81, 24));
        lf_category = new QLabel(tab_filter);
        lf_category->setObjectName("lf_category");
        lf_category->setGeometry(QRect(130, 140, 61, 31));
        lf_until = new QLabel(tab_filter);
        lf_until->setObjectName("lf_until");
        lf_until->setGeometry(QRect(30, 350, 41, 31));
        boxf_categories = new QComboBox(tab_filter);
        boxf_categories->setObjectName("boxf_categories");
        boxf_categories->setGeometry(QRect(120, 180, 79, 26));
        rf_income = new QRadioButton(tab_filter);
        rf_income->setObjectName("rf_income");
        rf_income->setGeometry(QRect(30, 80, 71, 24));
        ef_sinceDate = new QDateEdit(tab_filter);
        ef_sinceDate->setObjectName("ef_sinceDate");
        ef_sinceDate->setGeometry(QRect(90, 290, 110, 27));
        lf_since = new QLabel(tab_filter);
        lf_since->setObjectName("lf_since");
        lf_since->setGeometry(QRect(30, 290, 41, 31));
        lf_date = new QLabel(tab_filter);
        lf_date->setObjectName("lf_date");
        lf_date->setGeometry(QRect(100, 240, 31, 31));
        tabs->addTab(tab_filter, QString());
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(260, 200, 521, 351));
        calendar = new QCalendarWidget(centralwidget);
        calendar->setObjectName("calendar");
        calendar->setGeometry(QRect(360, 10, 304, 179));
        Coinshen->setCentralWidget(centralwidget);
        tableView->raise();
        tabs->raise();
        calendar->raise();
        menubar = new QMenuBar(Coinshen);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 806, 23));
        menuInfo = new QMenu(menubar);
        menuInfo->setObjectName("menuInfo");
        menuAbout = new QMenu(menuInfo);
        menuAbout->setObjectName("menuAbout");
        Coinshen->setMenuBar(menubar);
        statusbar = new QStatusBar(Coinshen);
        statusbar->setObjectName("statusbar");
        Coinshen->setStatusBar(statusbar);

        menubar->addAction(menuInfo->menuAction());
        menuInfo->addAction(menuAbout->menuAction());
        menuInfo->addSeparator();
        menuInfo->addAction(actionExit);
        menuAbout->addAction(actionCreator);
        menuAbout->addAction(actionDescription);

        retranslateUi(Coinshen);

        tabs->setCurrentIndex(0);
        tabs_add->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Coinshen);
    } // setupUi

    void retranslateUi(QMainWindow *Coinshen)
    {
        Coinshen->setWindowTitle(QCoreApplication::translate("Coinshen", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("Coinshen", "Exit", nullptr));
        actionCreator->setText(QCoreApplication::translate("Coinshen", "Creator", nullptr));
        actionDescription->setText(QCoreApplication::translate("Coinshen", "Description", nullptr));
        l_addNew->setText(QCoreApplication::translate("Coinshen", "Add new:", nullptr));
        l_transaction->setText(QCoreApplication::translate("Coinshen", "Transaction", nullptr));
        rt_income->setText(QCoreApplication::translate("Coinshen", "Income", nullptr));
        rt_expense->setText(QCoreApplication::translate("Coinshen", "Expense", nullptr));
        lt_account->setText(QCoreApplication::translate("Coinshen", "Account", nullptr));
        lt_category->setText(QCoreApplication::translate("Coinshen", "Category", nullptr));
        lt_amount->setText(QCoreApplication::translate("Coinshen", "Amount", nullptr));
        lt_description->setText(QCoreApplication::translate("Coinshen", "Description", nullptr));
        lt_date->setText(QCoreApplication::translate("Coinshen", "Date", nullptr));
        bt_add->setText(QCoreApplication::translate("Coinshen", "Add", nullptr));
        tabs_add->setTabText(tabs_add->indexOf(tab_transaction), QCoreApplication::translate("Coinshen", "Tab 1", nullptr));
        l_category->setText(QCoreApplication::translate("Coinshen", "Category", nullptr));
        l_account->setText(QCoreApplication::translate("Coinshen", "Account", nullptr));
        la_name->setText(QCoreApplication::translate("Coinshen", "Name", nullptr));
        la_balance->setText(QCoreApplication::translate("Coinshen", "Balance", nullptr));
        bc_add->setText(QCoreApplication::translate("Coinshen", "Add", nullptr));
        ba_add->setText(QCoreApplication::translate("Coinshen", "Add", nullptr));
        lc_budget->setText(QCoreApplication::translate("Coinshen", "Budget", nullptr));
        lc_name->setText(QCoreApplication::translate("Coinshen", "Name", nullptr));
        tabs_add->setTabText(tabs_add->indexOf(tab_category), QCoreApplication::translate("Coinshen", "Tab 2", nullptr));
        tabs->setTabText(tabs->indexOf(tab_add), QCoreApplication::translate("Coinshen", "Tab 1", nullptr));
        l_filter->setText(QCoreApplication::translate("Coinshen", "Filter", nullptr));
        lf_account->setText(QCoreApplication::translate("Coinshen", "Account", nullptr));
        bf_filter->setText(QCoreApplication::translate("Coinshen", "Filter", nullptr));
        rf_expense->setText(QCoreApplication::translate("Coinshen", "Expense", nullptr));
        lf_category->setText(QCoreApplication::translate("Coinshen", "Category", nullptr));
        lf_until->setText(QCoreApplication::translate("Coinshen", "Until", nullptr));
        rf_income->setText(QCoreApplication::translate("Coinshen", "Income", nullptr));
        lf_since->setText(QCoreApplication::translate("Coinshen", "Since", nullptr));
        lf_date->setText(QCoreApplication::translate("Coinshen", "Date", nullptr));
        tabs->setTabText(tabs->indexOf(tab_filter), QCoreApplication::translate("Coinshen", "Tab 2", nullptr));
        menuInfo->setTitle(QCoreApplication::translate("Coinshen", "Info", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("Coinshen", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Coinshen: public Ui_Coinshen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COINSHEN_H
