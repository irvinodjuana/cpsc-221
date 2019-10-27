/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

/* No argument constructor */
template <class T>
Deque<T>::Deque():n1(0),n2(0){}



/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    if (data.size() == 0) {
        data.push_back(newItem);
        n1 = n2 = 0;
    } else { // data.size() > 0
        if (n2 == n1) { 
            // capacity reached, double size of data vector
            int dsize = data.size();
            vector<T> copy (dsize * 2); 
            for (int i = n1; i < dsize; i++)
                copy[i - n1] = data[i];
            for (int i = 0; i < n1; i++)
                copy[i + dsize - n1] = data[i];
            
            // reassign indices and data
            data = copy;
            n1 = 0;
            n2 = dsize;
        }
        data[n2] = newItem;
        n2 = (n2 + 1) % data.size();
    }
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T result = data[n1];
    n1 = (n1 + 1) % data.size();

    int size;
    if (n2 < n1) {
        size = data.size() + n2 - n1;
    } else {
        size = n2 - n1;
    }
    if (size <= data.size() / 4) {
        // data occupies < 1/4 of space, resize down to 1/2
        int dsize = data.size();
        vector<T> copy (size * 2);
        if (n2 < n1) {
            for (int i = n1; i < data.size(); i++)
                copy[i-n1] = data[i];
            for (int i = 0; i < n2; i++)
                copy[i + dsize - n1] = data[i];
        } else {
            for (int i = n1; i < n2; i++)
                copy[i-n1] = data[i];
        }
        // reassign indices and data
        data = copy;
        n1 = 0;
        n2 = size;
    }
    return result;
}



/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    n2 = (n2 + data.size() -1) % data.size();
    T result = data[n2];

    int size;
    if (n2 < n1) {
        size = data.size() + n2 - n1;
    } else {
        size = n2 - n1;
    }
    if (size <= (data.size() / 4)) {
        // data occupies < 1/4 of space, resize down to 1/2
        int dsize = data.size();
        vector<T> copy (size * 2);
        if (n2 < n1) {
            for (int i = n1; i < data.size(); i++)
                copy[i-n1] = data[i];
            for (int i = 0; i < n2; i++)
                copy[i + dsize - n1] = data[i];
        } else {
            for (int i = n1; i < n2; i++)
                copy[i-n1] = data[i];
        }
        // reassign indices and data
        data = copy;
        n1 = 0;
        n2 = size;
    }
    return result;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    /**
     * @todo Your code here! 
     */
    return data[n1];
}



/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    /**
     * @todo Your code here! 
     */
    return data[(n2 + data.size() - 1) % data.size()];
}



/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return data.size() == 0;
}

