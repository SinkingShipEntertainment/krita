/*
 * Copyright (C) 2018 Boudewijn Rempt <boud@valdyas.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "KisAbrStorage.h"
#include "KisResourceStorage.h"

class AbrTagIterator : public KisResourceStorage::TagIterator
{
public:
    AbrTagIterator(const QString &location, const QString &resourceType)
        : m_location(location)
        , m_resourceType(resourceType)
    {}

    bool hasNext() const override {return false; }
    void next() const override {}

    QString url() const override { return QString(); }
    QString name() const override { return QString(); }
    QString comment() const override {return QString(); }
    KisTagSP tag() const override { return 0; }
private:

    QString m_location;
    QString m_resourceType;
};

class AbrIterator : public KisResourceStorage::ResourceIterator
{
public:
    bool hasNext() const override {return false; }
    void next() const override {}

    QString url() const override { return QString(); }
    QString type() const override { return QString(); }
    QDateTime lastModified() const override { return QDateTime(); }
    /// This only loads the resource when called
    QByteArray md5sum() const override { return QByteArray(); }
    /// This only loads the resource when called
    KoResourceSP resource() const override { return 0; }
};

KisAbrStorage::KisAbrStorage(const QString &location)
    : KisStoragePlugin(location)
{

}

KisAbrStorage::~KisAbrStorage()
{

}

KisResourceStorage::ResourceItem KisAbrStorage::resourceItem(const QString &url)
{
    return KisResourceStorage::ResourceItem();
}


KoResourceSP KisAbrStorage::resource(const QString &url)
{
    return 0;
}

QSharedPointer<KisResourceStorage::ResourceIterator> KisAbrStorage::resources(const QString &resourceType)
{
    return QSharedPointer<KisResourceStorage::ResourceIterator>(new AbrIterator);
}

QSharedPointer<KisResourceStorage::TagIterator> KisAbrStorage::tags(const QString &resourceType)
{
    return QSharedPointer<KisResourceStorage::TagIterator>(new AbrTagIterator(location(), resourceType));
}
