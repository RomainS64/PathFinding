#include "Observer.h"

void Subject::attach(const EventID& _ID, Observer* observer)
{
	m_hashObserver[_ID].push_back(observer);
}

void Subject::detach(const EventID& _ID, Observer* observer)
{
	for (int i = 0; i < m_hashObserver[_ID].size(); i++)
		if (m_hashObserver[_ID][i] == observer) {
			m_hashObserver[_ID].erase(m_hashObserver[_ID].begin() + i);
			break;
		}
}

void Subject::notify(const EventID& _ID)
{
	for (Observer* observer : m_hashObserver[_ID])
		observer->update();
}
