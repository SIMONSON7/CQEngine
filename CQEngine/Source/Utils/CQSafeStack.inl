template<typename TYPE>
CQSafeStack<TYPE>::CQSafeStack()
{}

template<typename TYPE>
CQSafeStack<TYPE>::CQSafeStack(const CQSafeStack& _other)
{
	std::lock_guard<mutex> lg(_other.mut_);
	stack_ = _other.stack_;
}

template<typename TYPE>
CQSafeStack<TYPE>::~CQSafeStack()
{}

template <typename TYPE>
void CQSafeStack<TYPE>::push(TYPE _val)
{
	std::lock_guard<std::mutex> lg(mut_);
	stack_.push(_val);
	data_cond_.notify_one();
}

template <typename TYPE>
bool CQSafeStack<TYPE>::try_pop(TYPE& _val)
{
	std::lock_guard<std::mutex> lg(mut_);
	if (stack_.empty())
	{
		return false;
	}
	_val = stack_.top();
	stack_.pop();
	return true;
}

template <typename TYPE>
std::shared_ptr<TYPE> CQSafeStack<TYPE>::try_pop()
{
	std::lock_guard<std::mutex> lg(mut_);
	if (stack_.empty())
	{
		return std::shared_ptr<TYPE>();
	}
	std::shared_ptr<TYPE> res(std::make_shared<TYPE>(stack_.top()));
	stack_.pop();
	return res;
}

template <typename TYPE>
void CQSafeStack<TYPE>::wait_and_pop(TYPE& _val)
{
	std::unique_lock<std::mutex> ul(mut_);
	data_cond_.wait(ul, [this] {return !stack_.empty(); });
	_val = stack_.top();
	stack_.pop();
}

template <typename TYPE>
bool CQSafeStack<TYPE>::empty() const
{
	std::lock_guard<std::mutex> lg(mut_);
	return stack_.empty();
}


