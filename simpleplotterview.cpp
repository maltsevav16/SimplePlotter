#include "simpleplotterview.h"
#include <QInputDialog>
#include <QGraphicsItemGroup>
#include <QDir>
#include<cmath>
#include<QtAlgorithms>
#include<functional>
#include "lepton/include/Lepton.h"
SimplePlotterView::SimplePlotterView(QWidget * parent)
	:QGraphicsView(parent) {
	this->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setAlignment(Qt::AlignCenter);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->scene = new QGraphicsScene();
	this->setScene(this->scene);
	this->setDragMode(QGraphicsView::ScrollHandDrag);
	this->setMouseTracking(true);
	initCoordSystem();
    scale(100,100);
}

void SimplePlotterView::wheelEvent(QWheelEvent *event) {
	//centerOn(event->x(), event->y());
	if (event->delta() > 0) {
		zoom(2);
	}
	else {
		zoom(0.5);
	}
}

//void SimplePlotterView::appendPlot(Simple2DPlot chart, QColor color) {
//	QGraphicsItemGroup *group1 = new QGraphicsItemGroup();
//	auto points = chart.getPoints();
//	QPen pointPen(color);
//	pointPen.setCosmetic(true);
//	pointPen.setWidthF(1);
//	//for (auto pp : points) {
//	//	QGraphicsItem * item = scene->addEllipse(pp.first - radius, pp.second - radius, radius*2.0, radius*2.0, pointPen, QBrush(Qt::SolidPattern));
//	//	group1->addToGroup(item);
//	//}

//	QPainterPath path(QPointF(points[0].first, points[0].second));
//	for (int i = 1;i < points.size();++i) {
//		path.lineTo(points[i].first, points[i].second);
//	}
//	QPen pathPen(color);
//	pathPen.setCosmetic(true);
//	pathPen.setWidthF(2);
//	auto pathItem = scene->addPath(path, pathPen);
//	scene->addItem(group1);
//	pathGroups.push_back(QPair<std::string, QGraphicsPathItem*>(chart.getName(), pathItem));
//	pointGroups.append(QPair<std::string, QGraphicsItemGroup*>(chart.getName(), group1));
//}

void SimplePlotterView::hidePaths() {
	for (int i = 0;i < pathGroups.size();++i) {
		if (pathGroups[i]->isVisible()) {
			pathGroups[i]->hide();
		}
		else {
			pathGroups[i]->show();
		}
	}
}
void SimplePlotterView::hidePoints() {
	for (int i = 0;i < pointGroups.size();++i) {
		if (pointGroups[i].second->isVisible()) {
			pointGroups[i].second->hide();
		}
		else {
			pointGroups[i].second->show();
		}
	}
}
void SimplePlotterView::showHelp() {
	QMessageBox::information(this, "Simple Plotter help", HELPSTRING);
}
void SimplePlotterView::zoom(qreal factor) {
	radius = std::max(1.0, radius*factor);
	auto rect = viewport()->rect();
	QPointF sceneBotRight = mapToScene(rect.bottomRight());
	QPointF sceneTopLeft = mapToScene(rect.topLeft());
	//max(|x|,|y|)
	std::function<qreal(QPointF)> getMaxCoord = [&](QPointF  point) {
		return qMax(qAbs(point.x()), qAbs(point.y()));
	};

    if (factor<1 && qMax(getMaxCoord(sceneBotRight), getMaxCoord(sceneTopLeft))>MAXCOORD/2) {
		return;
	}
	if (factor > 1) {
		double minDelta = qMin(qAbs(sceneBotRight.x() - sceneTopLeft.x()),
			qAbs(sceneBotRight.y() - sceneTopLeft.y()));
        if (minDelta < MINCOORD)
		{
			return;
		}
	}
	scale(factor, factor);
	redraw();
}
void SimplePlotterView::keyReleaseEvent(QKeyEvent *event) {
	switch (event->key()) {
	case Qt::Key_Z:
		zoom(2);
		break;
	case Qt::Key_X:
		zoom(0.5);
		break;
	case Qt::Key_Q:
		centerOn(0, 0);
		rotate(-15);
		break;
	case Qt::Key_E:
		centerOn(0, 0);
		rotate(15);
		break;
	case Qt::Key_H:
		showHelp();
		break;
	case Qt::Key_R:
		centerOn(0, 0);
		break;
	case Qt::Key_A:
		addUserPlot();
		break;
	default:
		if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9 && !dialogOpen) {
			int key = event->key() - Qt::Key_1 + 1;
			if (key <= 0 || plotCount < key)
				return;
			expressions.remove(key - 1);
			plotCount--;
			redraw();
			updateBoard(QPointF(0.0, 0.0));
		}
	}
}

void SimplePlotterView::initCoordSystem() {
	board = scene->addSimpleText("");
	board->setFlag(QGraphicsItem::ItemIgnoresTransformations);
	board->setPos(mapToScene(QPoint(0, 0)));
	coordPen = QPen(Qt::black);
	coordPen.setCosmetic(true);
	coordPen.setWidthF(3);
	scene->addLine(-2 * MAXCOORD, 0, 2 * MAXCOORD, 0, coordPen);
	scene->addLine(0, -2 * MAXCOORD, 0, 2 * MAXCOORD, coordPen);
}


void SimplePlotterView::paintEvent(QPaintEvent *e) {
	QGraphicsView::paintEvent(e);
	board->setPos(mapToScene(QPoint(0, 0)));

}
void SimplePlotterView::mouseMoveEvent(QMouseEvent *event) {
	QGraphicsView::mouseMoveEvent(event);
	updateBoard(mapToScene(event->pos()));
}
void SimplePlotterView::removePlot(std::string name) {
	for (int i = 0;i < pointGroups.size();++i) {
		if (pointGroups[i].first == name) {
			pointGroups[i].second->hide();
			scene->removeItem(pointGroups[i].second);
			delete pointGroups[i].second;
		}
	}
}

SimplePlotterView::~SimplePlotterView() {
	for (auto x : pointGroups) {
		scene->removeItem(x.second);
		delete x.second;
	}
	for (auto x : pathGroups) {
		scene->removeItem(x);
		delete x;
	}
	qDeleteAll(scene->items());
	pointGroups.clear();
	pathGroups.clear();
	scene->clear();
	this->setScene(0);
	delete scene;

}

void SimplePlotterView::addUserPlot() {
	if (plotCount == MAXPLOTCOUNT) {
		showError("Maximal amount of plots reached");
		return;
	}
	bool ok;
	dialogOpen = true;
	std::string expr = QInputDialog::getText(this, "Enter function", "Function:", QLineEdit::Normal, "x", &ok).toStdString();
	dialogOpen = false;
	if (!ok) return;
	try {
		Lepton::CompiledExpression  expression = Lepton::Parser::parse(expr).optimize().createCompiledExpression();
        auto vars = expression.getVariables();
        if(vars.size()>1 || (vars.size()==1&& !vars.count("x"))){
            showError("Wrong variable name");
            return;
        }

        expressions.push_back(QPair<std::string, Lepton::CompiledExpression>(expr, expression));
		plotCount++;
		redraw();
	}
	catch (...) {
		showError("Expression can't be compiled");
	}

}

void SimplePlotterView::redraw() {
    MAXCOORD = 10000;
	auto rect = viewport()->rect();
	for (int i = 0;i < pathGroups.size();++i) {
		scene->removeItem(pathGroups[i]);
		delete pathGroups[i];
	}
	pathGroups.clear();
	pathGroups.reserve(POINTSONSCREEN * 4);
	QPointF topLeft = mapToScene(rect.topLeft());
	QPointF botRight = mapToScene(rect.bottomRight());
	double delta = (botRight.x() - topLeft.x());
	double deltaDiv = delta / POINTSONSCREEN;
    bool prevInfinity;
    int maxCount = 0;
	for (int i = 0;i < plotCount;++i) {
        prevInfinity = false;
		Lepton::CompiledExpression expression = expressions[i].second;
		QVector<QPointF> points;
		if (!expression.getVariables().count("x")) {
            for (double x = topLeft.x() - delta/2;x <= botRight.x() + delta/2;x += deltaDiv) {
				points.push_back(QPointF(x, -expression.evaluate()));
			}
		}
		else {
			double & x = expression.getVariableReference("x");

            x = topLeft.x() - delta/2;
            for (;x <= botRight.x() + delta/2;x += deltaDiv) {
                   auto maxV = testLimit(true, expression, x, deltaDiv);
                   if(maxV.first){
                       maxCount++;
                       if(!prevInfinity)
                                              points.push_back(QPointF(x,-MAXCOORD * 2));
                               prevInfinity = true;
                                continue;
                   }
                   auto minV = testLimit(false, expression, x, deltaDiv);
                   if(minV.first){
                       maxCount++;
                       if(!prevInfinity)
                           points.push_back(QPointF(x,MAXCOORD * 2));
                       prevInfinity = true;
                       continue;
                   }
                  prevInfinity = false;
                  if(qAbs(maxV.second)>qAbs(minV.second)){
                      points.push_back(QPointF(x, -maxV.second));
                  }
                  else{
                      points.push_back(QPointF(x, -minV.second));
                  }
                }
		}
		QPainterPath path(points[0]);
		for (int i = 1;i < points.size();++i) {
			path.lineTo(points[i]);
		}
		QPen pathPen(Colors[i]);//FIX
		pathPen.setCosmetic(true);
		pathPen.setWidthF(2);
		auto pathItem = scene->addPath(path, pathPen);
		pathGroups.push_back(pathItem);
        if(maxCount > 20){
            //to prevent big red square
            limitZoom();

        }
	}
}


void SimplePlotterView::showError(QString text) {
	QMessageBox::critical(this, "Error", text);
}

void SimplePlotterView::mouseReleaseEvent(QMouseEvent *e) {
	QGraphicsView::mouseReleaseEvent(e);

	redraw();
}

void SimplePlotterView::updateBoard(QPointF scenePos) {
	QString formatted = QString("(%1 ; %2)").arg(QString::number(scenePos.x()), QString::number(scenePos.y()));
	formatted.append("\nPress H for Help");
	for (int i = 0;i < plotCount;++i) {
		formatted.append(QString("\n%1 : %2").arg(QString::number(i + 1), QString::fromStdString(expressions[i].first)));
	}
	board->setText(formatted);
}

QPair<bool, double> SimplePlotterView::testLimit(bool plus, Lepton::CompiledExpression expr, double x0, double step){
    //ternary search for max |x|
    double & x = expr.getVariableReference("x");
    double L = x0 + step/2, R = x0 + step;

    for(int it = 0;it<100; ++it){
        double m1 = L + (R-L) /3;
        double m2 = R - (R-L) /3;
        x = m1;
        double v1 = expr.evaluate();
        x = m2;
        double v2 = expr.evaluate();
        if (plus){
            if (v1 < v2){
                L = m1;
             }
            else{
                R = m2;
            }
        }
        else{
            if(v1 > v2)
            {
                L = m1;
            }
            else{
                R = m2;
            }
        }
    }
    x = L;
    if(qAbs(expr.evaluate())>MAXCOORD)
        return QPair<bool, double> (true, expr.evaluate());
    return QPair<bool, double> (false, expr.evaluate());
}

void SimplePlotterView::limitZoom(){
    if(MAXCOORD < 100)
        return;
    scale(10,10);
    MAXCOORD/=10;
}

