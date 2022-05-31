
#include "HealthPoints.h"

HealthPoints::HealthPoints(int inititalHp)
{
	if (inititalHp <= 0)
	{
		throw InvalidArgument();
	}
		
	m_maxHealth = inititalHp;
	m_health = m_maxHealth;
}


bool HealthPoints::operator==(const HealthPoints& hp)const
{
	return m_health == hp;
}

bool HealthPoints::operator!=(const HealthPoints& hp)const
{
	if (m_health == hp)
	{
		return false;
	}

	return true;
}

bool HealthPoints::operator>(const HealthPoints& healthPoints)const
{
	return m_health > healthPoints;
}

bool HealthPoints::operator>=(const HealthPoints& healthPoints) const
{
	if (m_health > healthPoints || m_health == healthPoints)
	{
		return true;
	}

	return false;
}

bool HealthPoints::operator<(const HealthPoints& hp)const
{
	return m_health < hp;
}

bool HealthPoints::operator<=(const HealthPoints& hp)const
{
	if (m_health == hp || m_health < hp)
	{
		return true;
	}

	return false;
}

HealthPoints& HealthPoints::operator+=(const int& health)
{
	m_health += health;

	if (m_health >= m_maxHealth)
	{
		m_health = m_maxHealth;
	}

	if (m_health < 0)
	{
		m_health = 0;
	}

	return *this;
}

HealthPoints& HealthPoints::operator-=(const int& health)
{
	m_health -= health;

	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}

	if (m_health < 0)
	{
		m_health = 0;
	}

	return *this;
}

HealthPoints HealthPoints::operator+(const int& healthAddition) const
{
	HealthPoints result = healthAddition + *this;

	return result;
}

HealthPoints HealthPoints::operator-(const int& health)const
{
	HealthPoints result = *this;
	return(result -= health);
}

bool operator==(const int& num, const HealthPoints& health)
{
	if (health.m_health == num)
	{
		return true;
	}

	return false;
}

bool operator<(const int& num, const HealthPoints& health)
{
	if (num < health.m_health)
		return true;
	return false;
}

bool operator>(const int& num, const HealthPoints& health)
{
	if (num > health.m_health)
		return true;
	return false;
}

HealthPoints operator+(const int& num, const HealthPoints& health)
{
	HealthPoints result = health;
	return(result += num);
}


std::ostream& operator<<(std::ostream& os, const HealthPoints& hp)
{
	return os << hp.m_health << "(" << hp.m_maxHealth << ")";
}


