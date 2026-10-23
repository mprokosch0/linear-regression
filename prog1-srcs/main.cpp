#include "linearReg.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: expected 1 args and got " << ac - 1 << " arguments." << std::endl;
		return 1;
	}
	int theta0 = -26021624, theta1 = -29105728;
	int mileage = std::atoi(av[1]);

	std::cout << "The price is " << theta0 + theta1 * mileage << "€ for a mileage of " << mileage << " kilometers" << std::endl;
	return 0;
}