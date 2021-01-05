#include "resultswidget.h"
#include "ui_resultswidget.h"

ResultsWidget::ResultsWidget(QWidget *parent, SMainClass *m_new) :
    QWidget(parent),
    ui(new Ui::ResultsWidget)
{
    this->m = m_new;
    ui->setupUi(this);

    tm = new QTimer();
    item = new QGraphicsPathItem;
    connect(tm, &QTimer::timeout, this, &ResultsWidget::setScene);
    tm->start(100);
}

ResultsWidget::~ResultsWidget()
{
    delete item;
    delete tm;
    delete scene;
    delete ui;
}

void ResultsWidget::resizeEvent(QResizeEvent *event)
{
   Q_UNUSED(event)
   if (is_clicked) drawShip();
}

QPointF ResultsWidget::fromDataToScene(QPointF p)
{
    QPointF new_p;
    double scale = (scene->sceneRect().width()/m->general->L);
    p *= scale;

    new_p = QPointF(scene->sceneRect().width() - p.x(), scene->sceneRect().height() - p.y());
    return new_p;
}

QPainterPath ResultsWidget::createBlock(SBlockData *e)
{
    QPainterPath path;
    path.moveTo(fromDataToScene(QPointF(e->X.av, e->Z)));
    path.lineTo(fromDataToScene(QPointF(e->X.av + e->a, e->Z)));
    path.lineTo(fromDataToScene(QPointF(e->X_U_A, e->Z + e->h)));
    path.lineTo(fromDataToScene(QPointF(e->X_U_F, e->Z + e->h)));
    path.lineTo(fromDataToScene(QPointF(e->X.av, e->Z)));

    return path;
}

void ResultsWidget::setScene()
{
    tm->stop();

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ResultsWidget::drawShip()
{
   is_clicked = true;
   scene->clear();
   int margin = 40;
//   scene->setSceneRect(-margin, margin, ui->graphicsView->width(), ui->graphicsView->height() + margin);
   scene->setSceneRect(0, 0, ui->graphicsView->width()-margin, ui->graphicsView->height()-margin);
//   scene->addRect(scene->sceneRect());

   QPainterPath path;
   path.moveTo(fromDataToScene(QPointF(0, m->general->sef_function(0))));
   for (double i = 0; i <= m->general->L; ++i)
   {
       path.lineTo(fromDataToScene(QPointF(i, m->general->sef_function(i))));
   }

   scene->addPath(path);

   foreach (auto e, m->blocks)
   {
        scene->addPath(createBlock(e));
   }


}

void ResultsWidget::on_pushButton_opt_clicked()
{
   ui->pushButton_stop->setEnabled(true);
   m->prepareToOptimize();
   while (m->alg->startOpt())
   {
       qApp->processEvents();
       drawShip();
   }

   drawShip();
   ui->label->setText(QString::number(m->general->ECB));
}

void ResultsWidget::on_pushButton_stop_clicked()
{
    m->alg->stopOpt = true;
    ui->pushButton_stop->setEnabled(false);
}
