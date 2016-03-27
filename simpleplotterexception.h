#ifndef SIMPLEPLOTTEREXCEPTION_H
#define SIMPLEPLOTTEREXCEPTION_H
#include<QException>
#include<QString>
/*! \class SimplePlotterException
* \brief Класс исключения
*
* Исключения, получающиеся при проблемах с графопостроителем
*/
class SimplePlotterException : public QException
{
private:
	QString message;
public:
	/*! \fn 	SimplePlotterException(QString message);
	*  \brief Конструктор по QString
	*  \param message текст исключения
	*/
	SimplePlotterException(QString message);
	/*! \fn 	QString getMessage();
	*  \return текст исключения
	*/
	QString getMessage();
	/*! \fn 	SimplePlotterException(std::string message);
	*  \brief Конструктор по std::string
	*  \param message текст исключения
	*/
	SimplePlotterException(std::string message);
	/*! \fn 	SimplePlotterException(char* message);
	*  \brief Конструктор по char*
	*  \param message текст исключения
	*/
	SimplePlotterException(char * message);
};

#endif // SIMPLEPLOTTEREXCEPTION_H
