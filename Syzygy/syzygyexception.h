#ifndef SYZYGYEXCEPTION_H
#define SYZYGYEXCEPTION_H

#include <exception>
#include <QString>
#include <QMessageBox>

class SyzygyException: std::exception
{
public:
    SyzygyException(QString error);
    SyzygyException(QString error, bool isFatalError, bool isWarning);

    const char* what() const noexcept;

    bool GetIsWarning() const;
    bool GetIsFatalError() const;

    static QMessageBox::StandardButton WhatShow(const SyzygyException& ex);
private:
    QString m_error;

    bool isWarning;
    bool isFatalError;
};

#endif // SYZYGYEXCEPTION_H
