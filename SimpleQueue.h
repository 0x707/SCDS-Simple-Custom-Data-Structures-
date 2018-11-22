#include <utility>

namespace scds {

	template<typename T>
	class SimpleQueue
	{
	public:
		SimpleQueue(int);
		~SimpleQueue();

		SimpleQueue(SimpleQueue const&) = delete;
		SimpleQueue& operator=(SimpleQueue const&) = delete;

		void enqueue();
		void dequeue();

		int front() const { return front_; }
		int rear() const { return rear_; }
		int size() const { return size_; }
		int current_length() const { return length_; }

		T* const peek_val();
		T const* const peek_val() const;
		T* const * const elems(int index) const;

		bool is_empty() const { return length_ == 0; }
		bool is_full() const { return length_ == size_; }
	private:
		T** elems_;
		int front_{ 0 };
		int rear_{ -1 };
		int length_ = 0;
		int size_;
	};

	template<typename T>
	SimpleQueue<T>::SimpleQueue(int size)
		: size_{size}
		, elems_{new T*[size_]}
	{
	}

	template<typename T>
	SimpleQueue<T>::~SimpleQueue()
	{
		while (!is_empty())
			this->dequeue();
		delete[] elems_;
	}

	template<typename T>
	void SimpleQueue<T>::enqueue()
	{
		if (is_full())
			return;

		rear_ = ++rear_ % size_;
		elems_[rear_] = new T;
		++length_;
	}

	template<typename T>
	void SimpleQueue<T>::dequeue()
	{
		if (is_empty())
			return;

		front_ = ++front_ % size_;
		delete elems_[front_];
		elems_[front_] = nullptr;
		--length_;
	}

	template<typename T>
	T* const SimpleQueue<T>::peek_val()
	{
		return is_empty() ? nullptr : elems_[front_];
	}

	template<typename T>
	T const* const SimpleQueue<T>::peek_val() const
	{
		return is_empty() ? nullptr : elems_[front_];
	}

	template<typename T>
	T* const * const SimpleQueue<T>::elems(int index) const
	{
		return is_empty() ? nullptr : elems_;
	}

} // namespace scds