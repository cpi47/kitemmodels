/*
    SPDX-FileCopyrightText: 2019 David Edmundson <davidedmundson@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

//This class exposes KConcatenateRowsProxyModel in a more QML friendly way

#pragma once

#include <QObject>
#include <QQmlListProperty>
#include <KConcatenateRowsProxyModel>

class KConcatenateRowsProxyModelQml : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QAbstractItemModel> sources READ sources)
    Q_CLASSINFO("DefaultProperty", "sources")
public:
    explicit KConcatenateRowsProxyModelQml(QObject *wrappedObject = nullptr);
    ~KConcatenateRowsProxyModelQml();

    QQmlListProperty<QAbstractItemModel> sources();

    static void appendSource(QQmlListProperty<QAbstractItemModel>*, QAbstractItemModel*);
    static int sourceCount(QQmlListProperty<QAbstractItemModel>*);
    static QAbstractItemModel* source(QQmlListProperty<QAbstractItemModel>*, int);
    static void clear(QQmlListProperty<QAbstractItemModel>*);

private:
    KConcatenateRowsProxyModel *q;
};
