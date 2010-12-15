//
// Copyright (C) 2006-2010  by the original authors of Galaxy
// and all its contributors ("Galaxy.org").
//
// This file is part of OrbitsWriter.
//
// OrbitsWriter is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OrbitsWriter is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OrbitsWriter.  If not, see <http://www.gnu.org/licenses/>.
//

#include "visualeditor.h"

VisualEditor::VisualEditor(QWidget *parent) :
    QWebView(parent)
{
    initBlankPage();
}

void VisualEditor::initBlankPage()
{
    setHtml("<p></p>");
    setFocus();
    page()->setContentEditable(true);
}

void VisualEditor::execCommand(const QString &cmd)
{
    QString js = QString("document.execCommand(\"%1\", false, null)").arg(cmd);
    mainFrame()->evaluateJavaScript(js);
}

void VisualEditor::execCommand(const QString &cmd, const QString &arg)
{
    QString js = QString("document.execCommand(\"%1\", false, \"%2\")").arg(cmd).arg(arg);
    mainFrame()->evaluateJavaScript(js);
}
