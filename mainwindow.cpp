#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO укрупнение сетки
//TODO после clear нужно добавить text = Переместите курсор
//TODO подумать над плавностью смены сотых долей в координатах

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(QSize(1440, 900));
    setFixedSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    view = new MyQGraphicsView(this);
    ui->vLScene->addWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionStart_triggered()
{

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_I:
        case 1064: {
            if (!e->modifiers().testFlag(Qt::ControlModifier)) return; // +Ctrl pressed

            view->info();
            break;
        }
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent * e)
{
    Q_UNUSED(e);

    view->hideText();
}
