#ifndef EX3_HealthPoints_H
#define EX3_HealthPoints_H

#include<iostream>

class HealthPoints
{
public:
	HealthPoints(int initialHealth = 100);
	~HealthPoints() = default;
	HealthPoints(const HealthPoints&) = default;
	HealthPoints& operator=(const HealthPoints&) = default;

	bool operator ==(const HealthPoints& hp)const;
	bool operator !=(const HealthPoints& hp)const;
	bool operator >(const HealthPoints& healthPoints)const;
	bool operator >=(const HealthPoints& healthPoints)const;
	bool operator <(const HealthPoints& hp)const;
	bool operator <=(const HealthPoints& hp)const;

	HealthPoints& operator+=(const int&);
	HealthPoints& operator-=(const int&);
	HealthPoints operator-(const int&)const;
	HealthPoints operator+(const int&) const;

	friend std::ostream& operator<<(std::ostream& os, const HealthPoints& hp);
	friend bool operator ==(const int&, const HealthPoints&);
	friend bool operator<(const int& num, const HealthPoints& health);
	friend bool operator>(const int& num, const HealthPoints& health);
	friend HealthPoints operator+(const int& num, const HealthPoints& health);

	class InvalidArgument {};

private:
	int m_maxHealth;
	int m_health;
};

#endif //EX3_HealthPoints_H