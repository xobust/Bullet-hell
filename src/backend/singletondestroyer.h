#ifndef SV11_UTILITY_SINGLETON_DESTROYER_H
#define SV11_UTILITY_SINGLETON_DESTROYER_H

		template<class T>
		class SingletonDestroyer
		{
		public:
			 SingletonDestroyer();
			 virtual ~SingletonDestroyer();
			 inline void setSingleton(T* pSingleton) { mpSingleton = pSingleton; }

		private:
			 SingletonDestroyer(const SingletonDestroyer& ref);
			 const SingletonDestroyer &operator=(const SingletonDestroyer &ref);

			T* mpSingleton;
		};

		template<class T>
		SingletonDestroyer<T>::SingletonDestroyer()
		{
			mpSingleton = 0;
		}

		template<class T>
		SingletonDestroyer<T>::~SingletonDestroyer()
		{
			delete (mpSingleton);
		}

		template<class T>
		SingletonDestroyer<T>::SingletonDestroyer(const SingletonDestroyer<T>& ref)
		{
			*(ref);
		}

		template<class T>
		const SingletonDestroyer<T>& SingletonDestroyer<T>::operator=(const SingletonDestroyer<T>& ref)
		{
			*(ref);
			return *this;
		}


#endif