template <typename T>
class vector
{
    private:
		T* vec_data;
		       
		int length; 
		int vec_size;
};

template<>
class vector < bool >
{
    private:
		unsigned int *vector_data;
		int length;
		int size;
};

