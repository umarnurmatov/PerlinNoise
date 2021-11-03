#pragma once
#include <vector>

class PerlinNoise1D
{
	int size; // Number of all generates points

	// Generates random line coeffs
	void generateCoeff();
	std::vector<std::vector<float>> coeff; // Vector of random line coefficients

	// Smootherstep function
	float smootherstep(float x) { return pow(x, 3) * (x * (x * 6.0f - 15.0f) + 10.0f); }
	// Simple linear interpolation of x between a and b
	float interpolation(float x, float a, float b) { return a + x * (b - a); }

	float generateNoisePoint(float x);

	// Amplitude and curvature of final curve
	float amplitudeFactor = 7500.f, stepFactor = 3.f;
	// Number of noise octaves
	int octaves = 3;

	std::vector<float> curve; // Vector of curve points

public:
	// Generates noise curve and returns it
	std::vector<float> generateNoise1D(int size);

	// Set the amplitude of final curve,
	void setAmplFactor(float amplitudeFactor) { this->amplitudeFactor = amplitudeFactor; }

	// Set the curvature of final curve
	void setStepFactor(float stepFactor) { this->stepFactor = stepFactor; }

	// Set the curvature of final curve
	void setOctaves(float octaves) { this->octaves = octaves; }
};
