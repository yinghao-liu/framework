#ifndef _PATTERNS_
#define _PATTERNS_
#include <memory>
/***********************Creational Patterns***********************/
/*
 * Singleton Pattern
 */
class singleton {
public:
	static std::shared_ptr<singleton> get_instance(void){return m_instance;};
	void show(void){printf("singleton\n");};
private:
	singleton(){};
	singleton operator=(const singleton&) = delete;
	static const std::shared_ptr<singleton> m_instance;
};






/***********************Structural Patterns***********************/









/***********************Behavioral Patterns***********************/

/*
 * Observer Pattern
 */
class observer {

};

class subject {
public:
	int init();
protected:
	void notify_observers();
private:
	//list
};

#endif
