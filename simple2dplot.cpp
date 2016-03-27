#include "simple2dplot.h"



Simple2DPlot::Simple2DPlot(std::string name, QVector<QPointF> points) {
	this->name = name;
	QVector<QPair<double, double> > points2;
	for (auto p : points) {
		points2.append(QPair<double, double>(p.x(), p.y()));
	}
	initPoints(points2);
}

Simple2DPlot::Simple2DPlot(std::string name, std::function<double(double)> func, double lower, double upper, double step) {
	this->name = name;
	if (lower<LOWERBOUND || upper>UPPERBOUND) {
		throw SimplePlotterException("wrong lower bound");
	}
	if (lower >= upper) {
		throw SimplePlotterException("lower > upper");
	}
	if (step < MINIMALSTEP) {
		throw SimplePlotterException("step is too low");
	}
	int pointNumber = (upper - lower) / step + 1;
	if (pointNumber > MAXPOINTNUMBER) {
		throw SimplePlotterException("maximal feasible amount of points exceeded");
	}

	QVector<QPair<double, double> > points;
	points.reserve(pointNumber);
	double x = lower;
	for (int i = 0;i < pointNumber; ++i) {
		try {
			double value = func(x);
            //if (isnan(value)) continue;
			points.push_back(QPair<double, double>(x, func(x)));
		}
		catch (...) {
			throw SimplePlotterException("Error while calculating function value");
		}
		x += step;
	}
	initPoints(points);
}

template<typename T> Simple2DPlot::Simple2DPlot(std::string name, QVector<QPair<T, T> > points) {
	this->name = name;
	initPoints(points);
}

void Simple2DPlot::initPoints(pointsVector & points) {
	this->points = points;
	invertX(this->points);
	std::sort(std::begin(this->points), std::end(this->points));
}
double Simple2DPlot::getMaxX() {
	return points.last().first;
}
double Simple2DPlot::getMinX() {
	return points.begin()->first;
}


std::string Simple2DPlot::getName() const {
	return name;
}
pointsVector Simple2DPlot::getPoints() const {
	return points;
}
void Simple2DPlot::invertX(pointsVector &a) {
	for (int i = 0;i < a.size();++i)
		a[i].second = -a[i].second;
}
