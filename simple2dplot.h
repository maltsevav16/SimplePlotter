#ifndef SIMPLEPLOTCHART_H
#define SIMPLEPLOTCHART_H
#include<functional>
#include<QVector>
#include<QPoint>
#include<QPair>
#include<QString>
#include "simpleplotterexception.h"
typedef QVector<QPair<double, double > > pointsVector;
/*! \class Simple2DPlot
* \brief Класс, хранящий информацию о графике
*
*/
class Simple2DPlot
{
public:
	/*! \fn     Simple2DPlot(std::string name, QVector<QPoint> points);
	*  \brief Конструктор по вектору точек.
	*  \param name название графика
	*  \param points вектор точек
	*/
    Simple2DPlot(std::string name, QVector<QPointF> points);
	/*! \fn         Simple2DPlot(std::string name, std::function<double(double)> func,double lower, double upper,double step);
	*  \brief Конструктор по функции.
	*  \param name название графика
	*  \param func функция double -> double
	*  \param lower нижняя граница
	*  \param upper верхняя граница
	*  \param step шаг
	*/
    Simple2DPlot(std::string name, std::function<double(double)> func,double lower, double upper,double step);
	
	//template<typename T> Simple2DPlot(std::string name, pointsVector points);
    
	/*! \fn         	template<typename T> Simple2DPlot(std::string name, QVector<QPair<T,T> > points); 
	*  \brief Конструктор по списку точек
	*  \param name название графика
	*  \param points  список точек  в виде пар x, y
	*/
	template<typename T> Simple2DPlot(std::string name, QVector<QPair<T,T> > points); 
	/*! \fn 	std::string getName() const;
	*  \brief Возвращает имя 
	*  \return имя графика
	*/
	std::string getName() const;
	/*! \fn 	    pointsVector getPoints() const;
	*  \brief Возвращает Список точек
	*  \return список точек
	*/
    pointsVector getPoints() const;
private:
	double getMinX();
	double getMaxX();
    std::string name;
    QVector<QPair<double, double> > points;
    const double LOWERBOUND = -1e18;
    const double UPPERBOUND = 1e18;
    const int MAXPOINTNUMBER = 10000000;
    const double MINIMALSTEP = 1e-6;
    void initPoints(pointsVector & points);
    static void invertX(pointsVector &a);

};

#endif // SIMPLEPLOTCHART_H
