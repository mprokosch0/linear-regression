#include "linearReg.hpp"

#define LR_RATE 0.02

float	estimatedPrice(int mileage, int theta0, int theta1)
{
	return theta0 + mileage * theta1;
}

int main()
{
	csv data("data.csv");
	if (!data.empty())
	{
		try
		{
			std::cout << data << std::endl;
			std::vector<int> km = data.getCol<int>(0);
			std::vector<int> prices = data.getCol<int>(1);
			float theta0 = 0, theta1 = 0;
			size_t limit = 1000000;
			for (size_t i = 0; i < limit; i++)
			{
				float sum1 = 0, sum2 = 0;
				for (size_t j = 0; j < km.size(); j++)
					sum1 += (estimatedPrice(km[j], theta0, theta1) - prices[j]);
				for (size_t j = 0; j < km.size(); j++)
					sum2 += ((estimatedPrice(km[j], theta0, theta1) - prices[j]) * km[j]);
				theta0 = (LR_RATE / (float)km.size()) * sum1;
				theta1 = (LR_RATE / (float)km.size()) * sum2;
			}
			std::cout << theta0 << ", " << theta1 << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
}

