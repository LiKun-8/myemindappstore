#ifndef SOFTWARECENTERWINDOWH
#define SOFTWARECENTERWINDOWH


#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QLineEdit>
#include <QScrollArea>
#include <QTableWidget>

#include <ClassAndMorePage/classwidget.h>
#include <ClassAndMorePage/showmore.h>
#include "updatepage/taskbar.h"
#include "updatepage/appwidget.h"
#include "updatepage/funcwidget.h"
#include "managerpage/managerwidget.h"

#define HOMEPAGE 0
#define CLASSPAGE 1
#define UPDATEPAGE 2
#define MANAGERPAGE 3
#define MOREPAGE 4

class SoftwareCenterWindow : public QWidget
{
    Q_OBJECT

public:
    SoftwareCenterWindow(QWidget *parent = 0);
    ~SoftwareCenterWindow();

protected slots:
    void OnBtnHome();
    void OnBtnClass();
    void OnBtnUpdate();
    void OnBtnManager();
    void PageUpdateBtnClicked();
    void SetMoreShow(int category);
    void StrLenChanged();
    void TextAreaChanged(int hig);

private:
    QPushButton *btnReturn;
    QPushButton *btnNext;
    QPushButton *btnRefresh;
    QPushButton *btnHome;
    QPushButton *btnClass;
    QPushButton *btnUpdate;
    QPushButton *btnManager;

    QStackedWidget *stwWindow;


    //临时使用的三个label，根据需要随时删除
    QLabel *label1;
    QLabel *label2;

    QLineEdit *lineSearch;
    QVBoxLayout *vbLayout;//整体垂直布局
    QHBoxLayout *hbLayout;//上部水平布局
    QHBoxLayout *hbBtnLayout;//上部按钮水平布局


    QSpacerItem *leftSpace;
    QSpacerItem *rightSpace;

    QWidget *pageHome;
    QWidget *pageClass;
    QWidget *pageUpdate;
    QWidget *pageManager;
    QWidget *pageMore;

    //class page
    ClassWidget *classWidget;//分类对象
    QSpacerItem *pageClassSpacer;
    QVBoxLayout *vbClasslayout;
    QWidget *pageClassWidget;
    QScrollArea  *scrollClass;

    //more page
    ShowMore *moreClassWidget;
    QWidget *pageMoreWidget;
    QVBoxLayout *vbClasslayoutMore;
    QScrollArea *scrollMore;
    QSpacerItem *pageMoreSpacer;

    void InitMainWindow();
    void SetCurrentPage(int page);
    void CreateClassWindow();
    void CreateUpdateWindow();
    void CreateManagerWindow();

    /*** updatepage variable ***/
    QWidget *pageUpdateWidget;
    TaskBar *updTaskBar;
    QTableWidget *updateTable;
    QVBoxLayout *upVLayout;
    QScrollArea *upScroArea;

    //managerpage
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *vboxLayout2;
    TaskBar *manTaskBar;
    TaskBar *manCompBar;
    QTableWidget *installTable;
    QTableWidget *compTable;
    QLabel *splitLabel;
    ManagerWidget *compManager;
    QScrollArea *manScroArea;

    void CreateMorewindow();
    bool event(QEvent *event);
    void StwwindowMove();
};

#endif // SoftwareCenterWindowH
