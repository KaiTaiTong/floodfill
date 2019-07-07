/**
 * Author: Alan Tong
 * Date: June 5, 2019
 */
/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque():num(0),L(-1){}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T const& newItem)
{
    data.push_back(newItem); // add element to the end of vector
    num++; // update num of elements in deque

    if (data.size() == 1){
        L = 0;
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
    /* O(n) Approach */
//    auto firstelem = data[0];
//    data.erase(data.begin());
//    num--;

//    if (data.size() == 0){
//        // vector is empty
//        L = -1;
//    }else {
//        L = 0;
//    }

//    return firstelem;

    /* O(1) Approach */
    // compare wheter it is time to resize vector

    auto firstelem = data[L];
    L++;
    num--;

    int distance_02L = L; // number of NULL elements before L(ex)
    int distance_L2end = data.size()-L; // number of contents after L(in) to end(in)

    if (distance_02L >= distance_L2end){
        // meaning we can fit the sub vector to the first half
        data = vector<T>(data.begin()+L, data.end());
        L = 0;
    }else {
        // no need to reinitialize
    }

    return firstelem;

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
    auto lastelem = data[data.size()-1];
    data.pop_back();
    num--;

    int distance_02L = L; // number of NULL elements before L(ex)
    int distance_L2end = data.size()-L; // number of contents after L(in) to end(in)

    if (distance_02L >= distance_L2end){
        // meaning we can fit the sub vector to the first half
        data = vector<T>(data.begin()+L, data.end());
        L = 0;
    }else {
        // no need to reinitialize
    }

    return lastelem;
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
    // deque is not empty when called
    return data[L];
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
    return data[data.size()-1];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    if (data.size() == 0 || L > data.size()){
        return true;
    }else {
        return false;
    }

    return false;
}
