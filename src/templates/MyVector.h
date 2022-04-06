#pragma once
#include <vector>

/*!
 * \brief The MyVector class is a template that allows you to create your own vector object based on std::list
 */
template <class T>
class MyVector
{
public:
    MyVector() = default;

    /*!
     * \brief appendItemToVector add item to vector
     * \param item is item added to vector
     */
    void appendItemToVector(T item) {
        m_vector.push_back(item);
    };

    /*!
     * \brief removeAllItems removes all items from vector
     */
    void removeAllItems() {
        m_vector.clear();
    };

    /*!
     * \brief getItemAtIndex return item at index
     * \param index is index of returned item
     * \return item at index
     */
    T getItemAtIndex(int index) const {
        return m_vector[index];
    };

    /*!
     * \brief getItemsCount return number of items in vector
     * \return number of items in vector
     */
    int getItemsCount() const {
        return m_vector.size();
    }

private:
    std::vector<T> m_vector;
};

