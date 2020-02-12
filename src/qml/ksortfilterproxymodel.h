/*
 *   Copyright 2010 by Marco Martin <mart@kde.org>
 *   Copyright 2019 by David Edmundson <davidedmundson@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef KSORTFILTERPROXYMODEL_H
#define KSORTFILTERPROXYMODEL_H

#include <QAbstractItemModel>
#include <QJSValue>
#include <QSortFilterProxyModel>
#include <QVector>
#include <QQmlParserStatus>

/**
 * @class SortFilterModel
 * @short Filter and sort an existing QAbstractItemModel
 *
 * @since 5.67
 */
class KSortFilterProxyModel : public QSortFilterProxyModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    /**
     * The source model of this sorting proxy model.
     */
    Q_PROPERTY(QAbstractItemModel *sourceModel READ sourceModel WRITE setModel NOTIFY sourceModelChanged)


    /**
     * The string for the filter, only rows with their filterRole matching filterString will be displayed
     */
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged)
    /**
     * A JavaScript callable that can be used to perform advanced filters on a given row.
     * The callback is passed the source row, and source parent for a given row as arguments
     *
     * The callable's return value is evaluated as boolean to determine
     * whether the row is accepted (true) or filtered out (false). It overrides the default implementation
     * that uses filterRegExp or filterString; while filterCallback is set those two properties are
     * ignored. Attempts to write a non-callable to this property are silently ignored, but you can set
     * it to null.
     *
     * @code
     * filterRowCallback: function(source_row, source_parent) {
     *   return sourceModel.data(sourceModel.index(source_row, 0, source_parent), Qt.DisplayRole) == "...";
     * };
     * @endcode
     */
    Q_PROPERTY(QJSValue filterRowCallback READ filterRowCallback WRITE setFilterRowCallback NOTIFY filterRowCallbackChanged)

    /**
     * A JavaScript callable that can be used to perform advanced filters on a given column.
     * The callback is passed the source column, and source parent for a given column as arguments.
     *
     * @see filterRowCallback
     */
    Q_PROPERTY(QJSValue filterColumnCallback READ filterColumnCallback WRITE setFilterColumnCallback NOTIFY filterColumnCallbackChanged)

    /**
     * The role of the sourceModel on which the filter will be applied.
     */
    Q_PROPERTY(QString filterRole READ filterRole WRITE setFilterRole NOTIFY filterRoleChanged)

    /**
     * The role of the sourceModel that will be used for sorting. if empty the order will be left unaltered
     */
    Q_PROPERTY(QString sortRole READ sortRole WRITE setSortRole NOTIFY sortRoleChanged)

    /**
     * One of Qt.Ascending or Qt.Descending
     */
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)

    /**
     * Specify which column shoud be used for sorting
     * The default value is -1.
     * If \a sortRole is set, the default value is 0.
     */
    Q_PROPERTY(int sortColumn READ sortColumn WRITE setSortColumn NOTIFY sortColumnChanged)

public:
    explicit KSortFilterProxyModel(QObject *parent = nullptr);
    ~KSortFilterProxyModel();

    void setModel(QAbstractItemModel *source);

    void setFilterRowCallback(const QJSValue &callback);
    QJSValue filterRowCallback() const;

    void setFilterString(const QString &filterString);
    QString filterString() const;

    void setFilterColumnCallback(const QJSValue &callback);
    QJSValue filterColumnCallback() const;

    void setFilterRole(const QString &role);
    QString filterRole() const;

    void setSortRole(const QString &role);
    QString sortRole() const;

    void setSortOrder(const Qt::SortOrder order);
    void setSortColumn(int column);

    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void filterStringChanged();
    void filterRoleChanged();
    void sortRoleChanged();
    void sortOrderChanged();
    void sortColumnChanged();
    void sourceModelChanged(QObject *);
    void filterRowCallbackChanged(const QJSValue &);
    void filterColumnCallbackChanged(const QJSValue &);


protected:
    int roleNameToId(const QString &name) const;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const override;

protected Q_SLOTS:
    void syncRoleNames();

private:
    bool m_componentCompleted = false;
    QString m_filterRole;
    QString m_filterString;
    QString m_sortRole;
    QJSValue m_filterRowCallback;
    QJSValue m_filterColumnCallback;
    QHash<QString, int> m_roleIds;
};
#endif