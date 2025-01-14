// Copyright (c) 2011-2020 The future Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef future_QT_COINCONTROLTREEWIDGET_H
#define future_QT_COINCONTROLTREEWIDGET_H

#include <QKeyEvent>
#include <QTreeWidget>

class CoinControlTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit CoinControlTreeWidget(QWidget *parent = nullptr);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // future_QT_COINCONTROLTREEWIDGET_H
