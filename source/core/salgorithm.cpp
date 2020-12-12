#include "salgorithm.h"

SAlgorithm::SAlgorithm()
{

}

void SAlgorithm::init()
{
    M = 1;
    Y = generateRandomForY();
    qDebug() << Y;
}

double SAlgorithm::generateRandomForY()
{
    return QRandomGenerator::global()->bounded(-1, 1);
}
