#include "syzygyexception.h"

SyzygyException::SyzygyException(QString error)
    :m_error{error}
{

}

SyzygyException::SyzygyException(QString error, bool isFatalError, bool isWarning)
    :m_error{error}, isWarning{isWarning}, isFatalError{isFatalError}
{

}

const char *SyzygyException::what() const noexcept
{
    return m_error.toStdString().c_str();
}

bool SyzygyException::GetIsWarning() const
{
    return isWarning;
}

bool SyzygyException::GetIsFatalError() const
{
    return isFatalError;
}

QMessageBox::StandardButton SyzygyException::WhatShow(const SyzygyException &ex)
{
    QString title = "Виняткова ситуація";

    if(ex.GetIsWarning()){
        return QMessageBox::warning(nullptr, title, ex.what());
    }else if(ex.GetIsFatalError()){
        return QMessageBox::critical(nullptr, title, ex.what());
    }
    else{
        return QMessageBox::information(nullptr, title, ex.what());
    }
}
