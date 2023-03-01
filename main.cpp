
#include <iostream>
#include <map>
#include <vector>

#define defaultSize 1

template <typename T, size_t N_size = defaultSize>
struct MyAllocator {
	using value_type = T;
	using pointer = T * ;

	MyAllocator() = default;
	~MyAllocator() = default;

	template <typename U, size_t M_size>
	MyAllocator(const MyAllocator<U, M_size> &) {}

	template<typename U>
	struct rebind
	{
		using other = MyAllocator<U, N_size>;
	};

	T *allocate(std::size_t n) {
		if (!m_startPtr) {
			auto p = std::malloc(N_size * sizeof(T));
			if (!p)
				throw std::bad_alloc();
			m_startPtr = reinterpret_cast<T *>(p);
			std::cout << "allocate:\t[n = " << N_size << "]\t" << p << std::endl;

			m_maxSize = N_size;
		}

		return m_startPtr + m_allocated++;
	}

	void deallocate(T *p, std::size_t n) {
		--m_allocated;

		//	if (m_startPtr == p)
		//	{
		std::cout << "deallocate:\t[n = " << n << "]\t" << p << std::endl;
		//		std::free(p);
		//	}
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
		std::cout << "construct\t\t" << p << std::endl;
		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U *p) {
		std::cout << "destroy\t\t\t" << p << std::endl;
		p->~U();
	}

private:
	pointer m_startPtr = nullptr;
	size_t m_allocated = 0;
	size_t m_maxSize = 0;

};

int main(int, char *[]) {
	using myAlloc = MyAllocator<std::pair<int, int>, 10>;
	auto m = std::map<int, int, std::less<int>, myAlloc>{};

	for (int i = 0; i < 3; ++i) {
		m[i] = i;
	}

	getchar();


	return 0;
}
