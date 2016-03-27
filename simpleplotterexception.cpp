#include "simpleplotterexception.h"

SimplePlotterException::SimplePlotterException(QString message)
{
	this->message = message;
}
SimplePlotterException::SimplePlotterException(std::string message) {
	this->message = QString::fromStdString(message);
}

QString SimplePlotterException::getMessage() {
	return message;
}
SimplePlotterException::SimplePlotterException(char *message) {
	this->message = QString();
}
