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
* \brief �����, �������� ���������� � �������
*
*/
class Simple2DPlot
{
public:
	/*! \fn     Simple2DPlot(std::string name, QVector<QPoint> points);
	*  \brief ����������� �� ������� �����.
	*  \param name �������� �������
	*  \param points ������ �����
	*/
    Simple2DPlot(std::string name, QVector<QPointF> points);
	/*! \fn         Simple2DPlot(std::string name, std::function<double(double)> func,double lower, double upper,double step);
	*  \brief ����������� �� �������.
	*  \param name �������� �������
	*  \param func ������� double -> double
	*  \param lower ������ �������
	*  \param upper ������� �������
	*  \param step ���
	*/
    Simple2DPlot(std::string name, std::function<double(double)> func,double lower, double upper,double step);
	
	//template<typename T> Simple2DPlot(std::string name, pointsVector points);
    
	/*! \fn         	template<typename T> Simple2DPlot(std::string name, QVector<QPair<T,T> > points); 
	*  \brief ����������� �� ������ �����
	*  \param name �������� �������
	*  \param points  ������ �����  � ���� ��� x, y
	*/
	template<typename T> Simple2DPlot(std::string name, QVector<QPair<T,T> > points); 
	/*! \fn 	std::string getName() const;
	*  \brief ���������� ��� 
	*  \return ��� �������
	*/
	std::string getName() const;
	/*! \fn 	    pointsVector getPoints() const;
	*  \brief ���������� ������ �����
	*  \return ������ �����
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
