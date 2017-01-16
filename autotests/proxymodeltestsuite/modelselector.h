/*
    Copyright (c) 2009 Stephen Kelly <steveire@gmail.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef MODELSELECTOR_H
#define MODELSELECTOR_H

#include <QItemSelectionModel>

//#include <kselectionproxymodel.h>

#include "proxymodeltest.h"

#include "proxymodeltestsuite_export.h"

class ModelSpy;

class OnlySelectedChildrenTest;

class PROXYMODELTESTSUITE_EXPORT ModelSelector : public ProxyModelTestData
{
    Q_OBJECT
public:
    ModelSelector(ProxyModelTest *ProxyModelTest = nullptr);

    void setWatchedModel(QAbstractItemModel *model);

    void setSelectionModel(QItemSelectionModel *selectionModel);

    void setRootModel(DynamicTreeModel *rootModel);

    QItemSelectionModel *selectionModel() const
    {
        return m_selectionModel;
    }
    QAbstractItemModel *watchedModel()
    {
        return m_model;
    }

    void setWatch(bool watch);

    //virtual KSelectionProxyModel::FilterBehavior filterBehaviour() = 0;

public Q_SLOTS:
    void rowsInserted(const QModelIndex &parent, int start, int end);

    void testInsertWhenEmptyData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testInsertInRootData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testInsertInTopLevelData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testInsertInSecondLevelData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testRemoveFromRootData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testRemoveFromTopLevelData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testRemoveFromSecondLevelData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testMoveFromRootData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testMoveFromTopLevelData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testMoveFromSecondLevelData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testModifyInRootData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testModifyInTopLevelData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

    void testModifyInSecondLevelData() Q_DECL_OVERRIDE
    {
        dummyTestData();
    }

protected Q_SLOTS:
    void modelDestroyed()
    {
        m_model = nullptr;
        m_selectionModel = nullptr;
    }

protected:
    QAbstractItemModel *m_model;
    QItemSelectionModel *m_selectionModel;
    DynamicTreeModel *m_rootModel;
    ModelSpy *m_modelSpy;

    QList<int> m_selectedRows;
};

#endif

