#ifndef _PATTERNS_
#define _PATTERNS_
#include <memory>
/*
 * Singleton Pattern
 */
class singleton {
public:
	static std::shared_ptr<singleton> get_instance(void){return m_instance;};
	void show(void){printf("singleton\n");};
private:
	singleton(){};
	static const std::shared_ptr<singleton> m_instance;
};
const std::shared_ptr<singleton> singleton::m_instance (new singleton);

#endif
