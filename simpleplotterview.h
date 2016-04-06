#ifndef SIMPLEPLOTTERVIEW_H
#define SIMPLEPLOTTERVIEW_H
#include<QGraphicsView>
#include<QVector>
#include<QTimer>
#include<QGraphicsItem>
#include<QMessageBox>
#include<QMouseEvent>
#include<QString>
#include<QGLWidget>
#include<algorithm>
#include <QInputDialog>
#include <QGraphicsItemGroup>
#include <QDir>
#include<cmath>
#include<QtAlgorithms>
#include<functional>
#include<iostream>
#include<QDrag>
#include "lepton/include/Lepton.h"
//#include "simple2dplot.h"
#include "lepton/include/Lepton.h"
/*! \class SimplePlotterView
* \brief �������� ����� �������
*
* �������� �����, ������� QGraphicsView
*/
class SimplePlotterView : public QGraphicsView
{
	Q_OBJECT
public:
	/*! \fn explicit SimplePlotterView(QWidget * parent = 0)
	*  \brief �����������
	*  \param parent ������������ ������
	*/
	explicit SimplePlotterView(QWidget * parent = 0);
	/*! \fn ~SimplePlotterView()
	*   \brief ����������
	*/
	~SimplePlotterView();
	/*! \fn void appendPlot(Simple2DPlot a, QColor color = Qt::red);
	*  \brief �������� ����� ������
	*  \param a ������ ���� Simple2DPlot, �������� ���������� � �������
	*  \param color ����
	*/
	//	void appendPlot(Simple2DPlot a, QColor color = Qt::red);
		/*! \fn removePlot(std::string  name);
		*  \brief ������� ������
		*  \param name ��� �������
		*/
	void removePlot(std::string  name);
private:
	void hidePoints();
	void hidePaths();

	QGraphicsScene *scene;
	QTimer *timer;
	//	QVector<Simple2DPlot> data;
	qreal radius = 0.05;
    const int POINTSONSCREEN = 1000;
    qreal MAXCOORD = 50000;
	const qreal MINCOORD = 0.1;
	QVector<QPair<std::string, QGraphicsItemGroup*> > pointGroups;
	QVector<QGraphicsPathItem*> pathGroups;
	QVector<QPair<std::string, Lepton::CompiledExpression> > expressions;
    QVector<QPair<std::string, Lepton::CompiledExpression> > diffs;

	const QString HELPSTRING = "This is a simple plotter QT plugin.\nHotkeys: ZX - Zoom x2, QE - Rotate 15 degrees,\nH - Help, numbers - to remove plots ";
	QGraphicsSimpleTextItem * board;
	QPen coordPen;
	const int MAXPLOTCOUNT = 8;
	QVector<QColor> Colors = { Qt::red, Qt::cyan, Qt::magenta,Qt::blue, Qt::darkMagenta, Qt::darkRed, Qt::darkBlue, Qt::darkCyan };
	int plotCount = 0;
	bool dialogOpen = false;
private:
	void wheelEvent(QWheelEvent *event);
	void updatePlotScene();
	void keyReleaseEvent(QKeyEvent *event);
	void moveCamera(int dx, int dy);
	void showHelp();
	void zoom(qreal factor);
	void initCoordSystem();
	void mouseMoveEvent(QMouseEvent *e);
	void paintEvent(QPaintEvent *e);
	void addUserPlot();
	void redraw();
	void showError(QString text);
	void mouseReleaseEvent(QMouseEvent * e);
	void updateBoard(QPointF scenePos);
    QPair<bool, double> testLimit(bool plus, Lepton::CompiledExpression  expr, double x0, double step);
    void dragEnterEvent(QDragEnterEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *e);
};

#endif // SIMPLEPLOTTERVIEW_H
