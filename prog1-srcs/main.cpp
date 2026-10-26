#include "linearReg.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: expected 1 args and got " << ac - 1 << " arguments." << std::endl;
		return 1;
	}
	int mileage = std::atoi(av[1]);
	if (mileage < 0)
	{
		std::cout << "Error: exepect a mileage >= 0, got " << mileage << std::endl;
		return 1;
	}
	double theta0 = 0, theta1 = 0;
	double price = theta0 + theta1 * mileage;
	std::cout << "The price is " << (price < 0 ? 0 : price) << "€ for a mileage of " << mileage << " kilometers" << std::endl;
	return 0;
}