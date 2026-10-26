#ifndef VEC_HPP

# define VEC_HPP

# include <vector>
# include <iostream>
# include <cmath>

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GRAY "\033[90m"
# define PINK "\033[35m"

template<typename K>
class Vec
{
	private:
		std::vector<K> _data;

	
	public:
		Vec(std::initializer_list<K> list): _data(list){};
		Vec(std::vector<K> const &list): _data(list){};
		Vec(size_t size, K value = K()): _data(size, value){};
		Vec(Vec const &rhs): _data(rhs._data){};
		~Vec(){};

	public:
		Vec<K>		&operator=(Vec<K> const &rhs);
		Vec<K>		operator+(Vec<K> const &rhs) const;
		Vec<K>		operator-(Vec<K> const &rhs) const;
		Vec<K>		operator*(K const &rhs) const;
		Vec<K>		operator/(K const &rhs) const;
		bool		operator==(Vec<K> const &rhs) const;
		bool		operator!=(Vec<K> const &rhs) const;
		K			&operator[](size_t index);
		const K		&operator[](size_t index) const;

	public:
		static Vec<K>			linear_combination(std::vector<Vec<K>> &vList, std::vector<K> &sList);
		static K				cos_angle(Vec<K> const &v1, Vec<K> const &v2);
		static Vec<K>			cross_product(Vec<K> const &v1, Vec<K> const &v2);
		Vec<K>					normalize(void) const;
		size_t					size(void) const;
		K						norm_1(void) const;
		K						norm(void) const;
		K						squareNorm(void) const;
		K						norm_inf(void) const;
		K						dot(Vec<K> const &rhs) const;
		std::vector<K> const	&getData(void) const;
		void					print(void) const;
};

template<typename K, typename S>
Vec<K>	operator*(S const &lhs, Vec<K> const &rhs);

template<typename K, typename S>
Vec<K>	operator*(Vec<S> const &lhs, K const &rhs);

template<typename K, typename S>
Vec<K>	operator/(S const &lhs, Vec<K> const &rhs);

template<typename K, typename S>
Vec<K>	operator/(Vec<S> const &lhs, K const &rhs);

template<typename K, typename S>
Vec<K>	operator+(S const &lhs, Vec<K> const &rhs);

template<typename K, typename S>
Vec<K>	operator+(Vec<S> const &lhs, K const &rhs);

template<typename K, typename S>
Vec<K>	operator-(S const &lhs, Vec<K> const &rhs);

template<typename K, typename S>
Vec<K>	operator-(Vec<S> const &lhs, K const &rhs);

template<typename T>
Vec<T>	lerp(Vec<T> const &u, Vec<T> const &v, float t)
{
	// if (t < 0 || t > 1)
	// 	throw std::runtime_error("Error: t must be between 0 and 1 ([0, 1]).");
	if (u.size() != v.size())
		throw std::runtime_error("Error: the two object are of a different sizes.");
	
	Vec<T> res(u);

	for (size_t i = 0; i < res.size(); i++)
		res[i] = static_cast<T>(fma(v[i] - res[i], t, res[i]));
	return res;
}

template<typename K>
Vec<K>	Vec<K>::cross_product(Vec<K> const &v1, Vec<K> const &v2)
{
	if (v1.size() != 3)
		throw std::runtime_error("Error: Vec v1 has not a size of 3");
	if (v2.size() != 3)
		throw std::runtime_error("Error: Vec v2 has not a size of 3");
	Vec<K> res(3);
	res[0] = fma(v1[1], v2[2], -(v1[2] * v2[1]));
	res[1] = fma(v1[2], v2[0], -(v1[0] * v2[2]));
	res[2] = fma(v1[0], v2[1], -(v1[1] * v2[0]));
	return res;
}

template<typename K>
Vec<K>	&Vec<K>::operator=(Vec<K> const &rhs)
{
	if (this == &rhs)
		return *this;
	this->_data = rhs._data;
	return *this;
}

template<typename K>
K	&Vec<K>::operator[](size_t index)
{
	if (index >= _data.size())
		throw std::runtime_error("Error: index access out of bounds");
	return _data[index];
}

template<typename K>
const K	&Vec<K>::operator[](size_t index) const
{
	if (index >= _data.size())
		throw std::runtime_error("Error: index access out of bounds");
	return _data[index];
}

template<typename K>
bool	Vec<K>::operator==(Vec<K> const &rhs) const
{
	if (this->_data.size() != rhs._data.size())
		throw std::runtime_error("Error: The vectors are of a different size");
	for (size_t i = 0; i < this->_data.size(); i++)
		if (this->_data[i] != rhs._data[i])
			return false;
	return true;
}

template<typename K>
bool	Vec<K>::operator!=(Vec<K> const &rhs) const
{
	return !(*this == rhs);
}

template<typename K>
Vec<K>	Vec<K>::operator+(Vec<K> const &rhs) const
{
	if (rhs.size() != this->_data.size())
		throw std::runtime_error("Error: try to sum 2 vectors of different sizes");
	Vec<K> res(rhs.size());
	for (size_t i = 0; i < rhs.size(); i++)
		res._data[i] = this->_data[i] + rhs._data[i];
	return res;
}

template<typename K>
Vec<K>	Vec<K>::operator-(Vec<K> const &rhs) const
{
	if (rhs.size() != this->_data.size())
		throw std::runtime_error("Error: try to sub 2 vectors of different sizes");
	Vec<K> res(rhs.size());
	for (size_t i = 0; i < rhs.size(); i++)
		res._data[i] = this->_data[i] - rhs._data[i];
	return res;
}

template<typename K>
Vec<K>	Vec<K>::operator*(K const &rhs) const
{
	Vec<K> res(_data.size());
	for (size_t i = 0; i < _data.size(); i++)
		res._data[i] = this->_data[i] * rhs;
	return res;
}

template<typename K>
Vec<K>	Vec<K>::operator/(K const &rhs) const
{
	if (rhs == K{0})
		throw std::runtime_error("Error: Can't divide by 0");
	Vec<K> res(_data.size());
	for (size_t i = 0; i < _data.size(); i++)
		res._data[i] = this->_data[i] / rhs;
	return res;
}

template<typename K, typename S>
Vec<K>	operator*(S const &lhs, Vec<K> const &rhs)
{
	const std::vector<K> &data = rhs.getData();
	Vec<K> res(data.size());
	for (size_t i = 0; i < data.size(); i++)
		res[i] = data[i] * lhs;
	return res;
}

template<typename K, typename S>
Vec<K>	operator*(Vec<S> const &lhs, K const &rhs)
{
	const std::vector<S> &data = lhs.getData();
	Vec<S> res(data.size());
	for (size_t i = 0; i < data.size(); i++)
		res[i] = data[i] * rhs;
	return res;
}

template<typename K, typename S>
Vec<S>	operator/(S const &lhs, Vec<K> const &rhs)
{
	if (lhs == S{0})
		throw std::runtime_error("Error: Can't divide by 0");
	const std::vector<K> &data = rhs.getData();
	Vec<K> res(data.size());
	for (size_t i = 0; i < data.size(); i++)
		res[i] = lhs / data[i];
	return res;
}

template<typename K, typename S>
Vec<S>	operator/(Vec<S> const &lhs, K const &rhs)
{
	if (rhs == K{0})
		throw std::runtime_error("Error: Can't divide by 0");
	const std::vector<S> &data = lhs.getData();
	K res(data.size());
	for (size_t i = 0; i < data.size(); i++)
		res[i] = rhs / data[i];
	return res;
}

template<typename K, typename S>
Vec<K>	operator+(S const &lhs, Vec<K> const &rhs)
{
	const std::vector<K> &data = rhs.getData();
	Vec<K> res(data.size());
	for (size_t i = 0; i < data.size(); i++)
		res[i] = data[i] + lhs;
	return res;
}

template<typename K, typename S>
Vec<S>	operator+(Vec<S> const &lhs, K const &rhs)
{
	const std::vector<S> &data = lhs.getData();
	Vec<S> res(data.size());
	for (size_t i = 0; i < data.size(); i++)
		res[i] = data[i] + rhs;
	return res;
}

template<typename K, typename S>
Vec<K>	operator-(S const &lhs, Vec<K> const &rhs)
{
	const std::vector<K> &data = rhs.getData();
	Vec<K> res(data.size());
	for (size_t i = 0; i < data.size(); i++)
		res[i] = lhs -  data[i];
	return res;
}

template<typename K, typename S>
Vec<S>	operator-(Vec<S> const &lhs, K const &rhs)
{
	const std::vector<S> &data = lhs.getData();
	Vec<S> res(data.size());
	for (size_t i = 0; i < data.size(); i++)
		res[i] = rhs -  data[i];
	return res;
}

//Functions-------------------------------------------

template<typename K>
K Vec<K>::cos_angle(Vec<K> const &v1, Vec<K> const &v2)
{
    K denom = v1.norm() * v2.norm();
    if (denom < 1e-9)
        throw std::runtime_error("Error: Can't compute angle with zero vector");

    K dot = v1.dot(v2);

    return dot / denom;
}

template<typename K>
Vec<K>	Vec<K>::normalize(void) const
{
	K val = this->norm();
	if (std::abs(val) <= 1e-6)
		return *this;
	Vec<K> res = *this / val;
	return res;
}

template<typename K>
K	Vec<K>::norm_1(void) const
{
	K res = {};
	for (const K &val : _data)
		res += std::abs(val);
	return res;
}

template<typename K>
K	Vec<K>::norm(void) const
{
	K res = {};
	for (const K &val : _data)
		res += pow(std::abs(val), 2);
	return pow(res, 0.5f);
}

template<typename K>
K	Vec<K>::squareNorm(void) const
{
	K res = {};
	for (const K &val : _data)
		res += pow(std::abs(val), 2);
	return res;
}

template<typename K>
K	Vec<K>::norm_inf(void) const
{
	K res = _data[0];
	for (const K &val : _data)
		res = std::max(res, std::abs(val));
	return res;
}

template<typename K>
K	Vec<K>::dot(Vec<K> const &rhs) const
{
	if (rhs.size() != this->_data.size())
		throw std::runtime_error("Error: the vector are of a different size.");
	K res = {};
	for (size_t i = 0; i < rhs.size(); i++)
        res = fma(this->_data[i], rhs[i], res);
	return res;
}

template<typename K>
Vec<K>	Vec<K>::linear_combination(std::vector<Vec<K>> &vList, std::vector<K> &sList)
{
	if (vList.size() != sList.size())
		throw std::runtime_error("Error: The vector list and the scalar list are not the same size.");
	Vec<K> res(vList[0].size());
	for (size_t i = 0; i < sList.size(); i++)
	{
		for (size_t j = 0; j < vList[i].size(); j++)
		{
			if (vList[i].size() != res.size())
				throw std::runtime_error("Error: The vectors in the vector list are of a different size.");
			res[j] = fma(vList[i][j], sList[i], res[j]);
		}
	}
	return res;
}
template<typename K>
size_t	Vec<K>::size(void) const
{
	return this->_data.size();
}

template<typename K>
std::vector<K> const	&Vec<K>::getData(void) const
{
	return this->_data;
}

template<typename K>
void	Vec<K>::print(void) const
{
	std::cout << '(';
	for (size_t i = 0; i < _data.size(); i++)
	{
        std::cout << _data[i];
		if (i + 1 != _data.size())
			std::cout << ", ";
	}
    std::cout << ')' << std::endl;
}

#endif