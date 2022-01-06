#include "featureFunctions.h"

unsigned int identity(unsigned int featureCount)
{
	return featureCount;
}

unsigned int const1(unsigned int featureCount)
{
	return 1;
}

unsigned int squareRoot(unsigned int featureCount)
{
	return (unsigned int)std::sqrt(featureCount);
}

unsigned int cubeRoot(unsigned int featureCount)
{
	return (unsigned int)std::cbrt(featureCount);
}

unsigned int lg2(unsigned int featureCount)
{
	return (unsigned int)std::log2(featureCount);
}

unsigned int lg10(unsigned int featureCount)
{
	return (unsigned int)std::log10(featureCount);
}

unsigned int ln(unsigned int featureCount)
{
	return (unsigned int)std::log(featureCount);
}