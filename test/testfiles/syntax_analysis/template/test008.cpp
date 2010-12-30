template <class _TypeT, class _Container>
class stack;

template <class _TypeT, class _Container>
inline bool operator==(const stack<_TypeT, _Container>&, const stack<_TypeT, _Container>&)
{
	return true;
}

template <class _TypeT, class _Container>
class stack
{
	friend bool operator==<>(const stack&, const stack&);
};

