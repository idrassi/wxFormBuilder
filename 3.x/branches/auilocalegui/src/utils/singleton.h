/** 
 * @file singleton.h
 * @brief Singleton template
 * @author Nicolas Macherey (nicolas.macherey@scifony.com, http://www.scifony.com) 
 * @date 2011-02-24 10:49:08 
 */
#ifndef SINGLETON_H
#define SINGLETON_H

/**
 * @class Singleton
 * A template class that implements the Singleton pattern.
 * If you want to make your class singleton simply make your class
 * public of this pattern :
 * 
 * @code
 * class MyClass : public Singleton<MyClass>
 * {
 * ...
 * };
 * @endcode
 *
 * @author Nicolas Macherey (nicolas.macherey@scifony.com, http://www.scifony.com) 
 * @date 2011-02-24 10:49:08 
 */
template <class T> class Singleton
{
	static T* ms_instance;
	static bool m_isAlive;
	explicit Singleton(const Singleton<T>&){};
    Singleton<T>& operator=(Singleton<T> const&){};
	
public:
	/**
	 * Static method to access the only pointer of this instance.
	 * @return a pointer to the only instance of this 
	 */
	static T* Get();

	/**
	 * Release resources.
	 */
	static void Free();
	
	/** Check if the singleton is alive or not */
	static bool IsAlive();

protected:
	/**
	 * Default constructor.
	 */
	Singleton();

	/**
	 * Destructor.
	 */
	virtual ~Singleton();
};

#ifndef SWIG
/** global instance declaration */
template <class T> T* Singleton<T>::ms_instance = 0;

/** global instance isAlive */
template <class T> bool Singleton<T>::m_isAlive = false;

/** constrcutor */
template <class T> Singleton<T>::Singleton()
{
}

/** destructor */
template <class T> Singleton<T>::~Singleton()
{
}

/** get method */
template <class T> T* Singleton<T>::Get()
{
	if(!ms_instance) {
		ms_instance = new T();
		m_isAlive = true;
	}
	return ms_instance;
}

/** free method */
template <class T> void Singleton<T>::Free()
{
	if( ms_instance )
	{
		delete ms_instance;
		ms_instance = 0;
	}
	
	m_isAlive = false;
}

template <class T> bool Singleton<T>::IsAlive() {
	return m_isAlive;
}
#endif

#endif
