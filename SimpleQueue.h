#include <utility>

namespace scds {

	template<typename T>
	struct Node
	{
		explicit Node(T* val) : pValue{ val } {}
		Node(Node const&) = delete;
		Node& operator=(Node const&) = delete;

		Node<T>* pNext = nullptr;
		Node<T>* pPrev = nullptr;
		T* pValue;
		~Node() { delete pValue; }
	};

	template<typename T>
	class SimpleQueue
	{
	public:
		SimpleQueue();
		~SimpleQueue();

		SimpleQueue(SimpleQueue&&);
		SimpleQueue& operator=(SimpleQueue&&);

		SimpleQueue(SimpleQueue const&) = delete;
		SimpleQueue<T>& operator=(SimpleQueue<T> const&) = delete;

		T* const push(T const*);
		void pop();
		bool is_empty() const { return counter_ < 1; }

	private:
		Node<T>* pFront_ = nullptr;
		Node<T>* pRear_ = nullptr;
		int counter_;

		friend void swap(SimpleQueue<T>&, SimpleQueue<T>&);
	};

	template<typename T>
	SimpleQueue<T>::SimpleQueue()
		: pFront_{ nullptr }, pRear_{ nullptr }
		, counter_{ 0 }
	{
	}

	template<typename T>
	SimpleQueue<T>::~SimpleQueue()
	{
		while (pFront_ != pRear_)
			pop();
		delete pFront_;
	}

	template<typename T>
	SimpleQueue<T>::SimpleQueue(SimpleQueue&& other)
		: SimpleQueue{}
	{
		*this = other;
	}

	template<typename T>
	SimpleQueue<T>& SimpleQueue<T>::operator=(SimpleQueue<T>&& other)
	{
		swap(*this, other);
		return *this;
	}

	template<typename T>
	T* const SimpleQueue<T>::push(T const* val)
	{
		if (!is_empty()) {
			Node<T>* temp = pRear_;
			pRear_ = new Node<T>{ val };
			temp->pPrev = pRear_;
			pRear_->pNext = temp;
		}
		else {
			pFront_ = new Node<T>{ val };
			pFront_->pPrev = pRear_;
			pRear_->pNext = pFront_;
		}
		++counter_;
		return val;
	}

	template<typename T>
	void SimpleQueue<T>::pop()
	{
		Node<T>* temp = pFront_;
		pFront_ = pFront_->pPrev;
		delete temp;

		--counter_;
	}

	template<typename T>
	void swap(SimpleQueue<T>& first, SimpleQueue<T>& second)
	{
		using std::swap;
		swap(first.pFront_, second.pFront_);
		swap(first.pRear_, second.pRear_);
		swap(first.counter_, second.counter_);
	}

} // namespace scds
