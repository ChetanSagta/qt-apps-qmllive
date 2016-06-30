/****************************************************************************
**
** Copyright (C) 2016 Pelagicore AG
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QmlLive tool.
**
** $QT_BEGIN_LICENSE:GPL-QTAS$
** Commercial License Usage
** Licensees holding valid commercial Qt Automotive Suite licenses may use
** this file in accordance with the commercial license agreement provided
** with the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and The Qt Company.  For
** licensing terms and conditions see https://www.qt.io/terms-conditions.
** For further information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
** SPDX-License-Identifier: GPL-3.0
**
****************************************************************************/

#include "imageadapter.h"
#include <QImageReader>
#include <QDebug>
#include <QFileInfo>
#include <QQmlContext>

ImageAdapter::ImageAdapter(QObject *parent) :
    QObject(parent)
{
}

bool ImageAdapter::canPreview(const QString &path) const
{
    QString format = QImageReader::imageFormat(path);
    if (!format.isEmpty()) {
        if (format == "pcx") {
            if (QFileInfo(path).suffix() == "pcx")
                return true;
        } else {
            return true;
        }
    }

    return false;
}

QImage ImageAdapter::preview(const QString &path, const QSize &requestedSize)
{
    QImage img(path);

    if (requestedSize.isValid())
        return img.scaled(requestedSize, Qt::KeepAspectRatio);
    return img;
}

bool ImageAdapter::canAdapt(const QUrl &url) const
{
    return !QImageReader::imageFormat(url.toLocalFile()).isEmpty();
}

QUrl ImageAdapter::adapt(const QUrl &url, QQmlContext *context)
{
    context->setContextProperty("imageViewerBackgroundColor", "black");
    context->setContextProperty("imageViewerSource", url);

    return QUrl("qrc:/livert/imageviewer_qt5.qml");
}