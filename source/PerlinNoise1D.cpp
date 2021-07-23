#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "PerlinNoise1D.h"

void PerlinNoise1D::generateCoeff() {
    if (coeff.size() == 0) {
        for (int n = 0; n < octaves; n++) {
            coeff.push_back(std::vector<float>());
            for (int i = 0; i <= size * (n + 1); i++) {
                if (rand() % 2 == 0) coeff.at(n).push_back(static_cast<float>(rand()) / RAND_MAX * 2);
                else coeff.at(n).push_back(-1 * static_cast<float>(rand()) / RAND_MAX * 2);
            }
        }
    }
    else {
        for (int n = 0; n < octaves; n++) {
            for (int i = 0; i <= size * (n + 1); i++) {
                if (rand() % 2 == 0) coeff.at(n).at(i) = static_cast<float>(rand()) / RAND_MAX * 2;
                else coeff.at(n).at(i) = -1 * static_cast<float>(rand()) / RAND_MAX * 2;
            }
        }
    }
}

float PerlinNoise1D::generateNoisePoint(float x) {
    int integerX;
    float fractionX, newX;
    float fractionXSmooth;
    float y = 0, amplitude;

    for (int octNum = 1; octNum <= octaves; octNum++) {
        newX = x * octNum;
        integerX = static_cast<int>(newX);
        fractionX = newX - static_cast<float>(integerX);
        fractionXSmooth = smootherstep(fractionX);
        y += interpolation(fractionXSmooth, coeff.at(octNum - 1).at(integerX) * fractionX, coeff.at(octNum - 1).at(integerX + 1) * (fractionX - 1)) / octNum;
    }
    y *= amplitudeFactor / static_cast<float>(size);
    return y;
}

std::vector<float> PerlinNoise1D::generateNoise1D(int size) {
    this->size = size;

    // Setup random generator
    srand(static_cast<unsigned int>(time(NULL)));

    // Generating Noise
    generateCoeff();
    float step = stepFactor / static_cast<float>(size);
    if (curve.size() == 0) {
        for (float f = 0; f < size * step; f += step) {
            curve.push_back(generateNoisePoint(f));
        }
    }
    else {
        float f = 0;
        for (int i = 0; i < curve.size(); i++) {
            curve.at(i) = generateNoisePoint(f);
            f += step;
        }
    }
    return curve;
}