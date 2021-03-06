/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "ApplicationAboutBoxDialog.h"


#include <iostream>

#include <QtCore/QFile>
#include <QtCore/QTextStream>



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ApplicationAboutBoxDialog::ApplicationAboutBoxDialog(QStringList files, QWidget* parent) :
  QDialog(parent)
{
  this->setupUi(this);
  setLicenseFiles(files);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ApplicationAboutBoxDialog::~ApplicationAboutBoxDialog()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ApplicationAboutBoxDialog::setApplicationInfo(QString applicationName, QString version)
{
  QString title("About ");
  title.append(applicationName);
  setWindowTitle(title);
  appName->setText(applicationName);
  appVersion->setText( version );
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ApplicationAboutBoxDialog::setLicenseFiles(QStringList files)
{
  m_licenseFiles = files;
  licenseCombo->clear();
  m_licenseFiles = files;
  for (int i = 0; i < m_licenseFiles.size(); ++i)
  {
    QString s = m_licenseFiles[i];
    s.remove(0, 2);
    s.remove(".license", Qt::CaseSensitive);
    licenseCombo->addItem(s);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ApplicationAboutBoxDialog::on_licenseCombo_currentIndexChanged(int index)
{
  QString resourceFile = m_licenseFiles[licenseCombo->currentIndex()];
  loadResourceFile(resourceFile);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ApplicationAboutBoxDialog::loadResourceFile(const QString qresourceFile)
{
  QFile inputFile(qresourceFile);
  inputFile.open(QIODevice::ReadOnly);
  QTextStream in(&inputFile);
  QString line = in.readAll();
  inputFile.close();

//  appHelpText->append(line);
  appHelpText->setPlainText(line);
  appHelpText->setUndoRedoEnabled(false);
  appHelpText->setUndoRedoEnabled(true);
}

