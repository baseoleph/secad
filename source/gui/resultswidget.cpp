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
    int righest_xuaf = 0;
    foreach (auto e, m->blocks)
    {
        if (e->X_U_A > righest_xuaf) righest_xuaf = e->X_U_A;
    }
    double scale = (scene->sceneRect().width()/m->general->L) - 0.3;
    p *= scale;

    new_p = QPointF(scene->sceneRect().width() - p.x() - 20, scene->sceneRect().height() - p.y());
    return new_p;
}

QPolygonF ResultsWidget::createBlock(SBlockData *e)
{
    QPolygonF pol;
    pol << fromDataToScene(QPointF(e->X.av, e->Z));
    pol << fromDataToScene(QPointF(e->X.av + e->a, e->Z));
    pol << fromDataToScene(QPointF(e->X_U_A, e->Z + e->h));
    pol << fromDataToScene(QPointF(e->X_U_F, e->Z + e->h));
    pol << fromDataToScene(QPointF(e->X.av, e->Z));

    return pol;
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
   scene->setSceneRect(0, 0, ui->graphicsView->width() - margin, ui->graphicsView->height() - margin);

   QPainterPath path;
   path.moveTo(fromDataToScene(QPointF(0, m->general->sef_function(0))));
   for (double i = 0; i <= m->general->L; ++i)
   {
       path.lineTo(fromDataToScene(QPointF(i, m->general->sef_function(i))));
   }

   scene->addPath(path);
   QBrush brush;
   brush.setColor(Qt::black);
   brush.setStyle(Qt::SolidPattern);
   QPen pen(Qt::black);

   foreach (auto e, m->blocks)
   {
       scene->addPolygon(createBlock(e), pen, brush);
   }


}

void ResultsWidget::on_pushButton_opt_clicked()
{
   ui->label->clear();
   ui->pushButton_stop->setEnabled(true);
   m->prepareToOptimize();
   while (m->alg->optimizationSteps())
   {
       qApp->processEvents();
       if (m->alg->goodTry || m->alg->EC_cnt == 0)
       {
           m->alg->goodTry = false;
           drawShip();
       }
   }

   drawShip();
   ui->label->setText("EC = " + QString::number(m->general->ECB) + "; " + m->alg->log_data);
   ui->pushButton_stop->setEnabled(false);
}

void ResultsWidget::on_pushButton_stop_clicked()
{
    m->alg->stopOpt = true;
    ui->pushButton_stop->setEnabled(false);
}
