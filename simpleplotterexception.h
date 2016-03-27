#ifndef SIMPLEPLOTTEREXCEPTION_H
#define SIMPLEPLOTTEREXCEPTION_H
#include<QException>
#include<QString>
/*! \class SimplePlotterException
* \brief ����� ����������
*
* ����������, ������������ ��� ��������� � �����������������
*/
class SimplePlotterException : public QException
{
private:
	QString message;
public:
	/*! \fn 	SimplePlotterException(QString message);
	*  \brief ����������� �� QString
	*  \param message ����� ����������
	*/
	SimplePlotterException(QString message);
	/*! \fn 	QString getMessage();
	*  \return ����� ����������
	*/
	QString getMessage();
	/*! \fn 	SimplePlotterException(std::string message);
	*  \brief ����������� �� std::string
	*  \param message ����� ����������
	*/
	SimplePlotterException(std::string message);
	/*! \fn 	SimplePlotterException(char* message);
	*  \brief ����������� �� char*
	*  \param message ����� ����������
	*/
	SimplePlotterException(char * message);
};

#endif // SIMPLEPLOTTEREXCEPTION_H
