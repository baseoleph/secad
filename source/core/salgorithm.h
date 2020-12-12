#ifndef SALGORITHM_H
#define SALGORITHM_H

#include <QRandomGenerator64>
#include <QDebug>

class SAlgorithm
{
public:
    SAlgorithm();
    void init();

private:
    int M = 0;
    double Y = 0;

    double generateRandomForY();
};

#endif // SALGORITHM_H
