#include "linearReg.hpp"

#define LR_RATE 1
#define NB_ITERATIONS 1000

double	estimatedPrice(double mileage, double theta0, double theta1)
{
	return theta0 + mileage * theta1;
}

void	decreasingGradient(Vec<double> km, Vec<double> prices, double &theta0, double &theta1)
{
	double kmNorm = km.norm(), pricesNorm = prices.norm();
	km = km.normalize();
	prices = prices.normalize();
	for (size_t i = 0; i < NB_ITERATIONS; i++)
	{
		double sum1 = 0, sum2 = 0;
		for (size_t j = 0; j < km.size(); j++)
		{
			sum1 += (estimatedPrice(km[j], theta0, theta1) - prices[j]);
			sum2 += ((estimatedPrice(km[j], theta0, theta1) - prices[j]) * km[j]);
		}
		theta0 -= LR_RATE * (sum1 / (double)km.size());
		theta1 -= LR_RATE * (sum2 / (double)km.size());
	}
	double ftheta0 = pricesNorm * theta0;
	double ftheta1 = theta1 * pricesNorm / kmNorm;
	theta0 = ftheta0;
	theta1 = ftheta1;
}

double	R2(Vec<double> &km, Vec<double> &prices, double theta0, double theta1)
{
	double sum1 = 0, sum2 = 0;
	double mean = 0;
	for (size_t i = 0; i < prices.size(); i++)
		mean += prices[i];
	mean /= prices.size();
	for (size_t i = 0; i < prices.size(); i++)
	{
		double estPrice = estimatedPrice(km[i], theta0, theta1);
		sum1 += (prices[i] - estPrice) * (prices[i] - estPrice);
		sum2 += (prices[i] - mean) * (prices[i] - mean);
	}
	if (sum2 == 0.0f)
		return 0;
	return (1 - (sum1 / sum2)) * 100.f;
}

int main()
{
	csv data("data.csv");
	if (data.empty())
		return 1;

	try
	{
		Vec<double> km = data.getCol<double>(0);
		Vec<double> prices = data.getCol<double>(1);
		double	theta0 = 0, theta1 = 0;

		if (km.size() != prices.size())
			throw std::runtime_error("Error: colums prices and kilometers are diffrents in size");
			
		decreasingGradient(km, prices, theta0, theta1);

		std::cout << "Theta0 = " << theta0 << ", Theta1 = " << theta1 << std::endl;
		std::cout << "Accuracy of the model is " << R2(km, prices, theta0, theta1) << '%' << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}
