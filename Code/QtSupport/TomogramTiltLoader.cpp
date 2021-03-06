#include "TomogramTiltLoader.h"


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
TomogramTiltLoader::TomogramTiltLoader(QWidget* parent) :
  QDialog(parent)
{
  setupUi(this);
  setupGui();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
TomogramTiltLoader::~TomogramTiltLoader()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void TomogramTiltLoader::setupGui()
{
  QDoubleValidator* dVal = new QDoubleValidator(this);
  dVal->setDecimals(6);
  pixelSize->setValidator(dVal);

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QVector<float> TomogramTiltLoader::getATilts()
{
  return aTilts->getAngles();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QVector<float> TomogramTiltLoader::getBTilts()
{
  return bTilts->getAngles();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
float TomogramTiltLoader::getPixelSize()
{
  bool ok = false;
  return pixelSize->text().toFloat(&ok);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void TomogramTiltLoader::setNumTilts(int nTilts)
{
  m_NumTilts = nTilts;
  aTilts->setNumTilts(m_NumTilts);
  bTilts->setNumTilts(m_NumTilts);
}
