template <typename T>
class sortedVector
{
    public:
		void insert (T val)
		{
		    if ( length == vec_size )
		    {
		        vec_size *= 2;    
		        vec_data = new T[vec_size];
		    }
		    ++length; 
		    
		    int pos;
		    for( pos = length; pos > 0 && val > vec_data[pos - 1]; --pos )
		    {
		        vec_data[pos] = vec_data[pos - 1];
		    }
		    vec_data[pos] = val;
		}

    private:
		T *vec_data;
		int length;
		int size;
};


template <typename T>
class sortedVector<T *>
{
    public:
		insert( T *val )
		{
		    if ( length == vec_size ) 
		    {
		        vec_size *= 2;   
		        vec_data = new T[vec_size];
		    }
		    ++length;  
		    
		    int pos;
		    for( pos = length; pos > 0 && *val > *vec_data[pos - 1]; --pos )
		    {
		        vec_data[pos] = vec_data[pos - 1];
		    }
		    vec_data[pos] = val;
		}

    private:
		T** vec_data;
		int length;
		int size;
};

