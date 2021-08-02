#ifndef WEBSERV_SINGLETON_H
# define WEBSERV_SINGLETON_H

template<typename T>
class Singleton
{
	public:
		static T &	get_instance(void)
		{
			static T instance;
			return (instance);
		}
	protected:
		Singleton(void) {};
		Singleton(const Singleton &) {};
		Singleton & operator=(const Singleton &) {};
};

#endif