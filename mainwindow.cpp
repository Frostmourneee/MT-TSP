#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO укрупнение сетки
//TODO после clear нужно добавить text = Переместите курсор
//TODO подумать над плавностью смены сотых долей в координатах
//TODO из-за симметрий быть может можно перебор уменьшить когда M = 2
//TODO прямоугольник ограничивающий происходящее
//TODO тесты
//TODO сортировка по иксам работает?
//TODO нельзя задать план из двузначной цели
//TODO позволить при большом N не искать оптимум, а просто летать
//TODO при M = 2 в графе идеального плана для одного считает видимо лучший для облёта именно первым! Если из разных точек стартуют, то может вторым лучше

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
