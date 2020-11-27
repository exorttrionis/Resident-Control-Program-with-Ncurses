// Để đơn giản hãy khai báo thư viện vector.
#include <cstdlib>
using namespace std;
#define ll long long

template <typename DataType>
class vector // dinh nghia kieu du lieu vector
{
public:
    DataType *ArrayData;
    ll length, capacity;

    explicit vector()
    {
        ArrayData = new DataType[10];
        capacity = 10;
        length = 0;
    }
    ~vector()
    {
        delete[] ArrayData;
    }

    ll size()
    {
        return length;
    }

    bool empty()
    {
        if (length == 0)
            return true;
        else
            return false;
    }

    DataType &operator[](int index)
    {
        if (index >= length)
        {
            exit(0);
            // return 0;
        }

        // else return value at that index
        return ArrayData[index];
    }

    void push_back(DataType data)
    {
        // neu so luong phan tu == dung luong (capacity)
        // ta gap doi dung luong
        if (length == capacity)
        {
            DataType *temp = new DataType[2 * capacity];
            for (int i = 0; i <= capacity; i++)
            {
                temp[i] = ArrayData[i]; // copy data tu array cu
            }
            delete[] ArrayData;      // xoa array cu
            capacity = capacity * 2; // gap doi dung luong
            ArrayData = temp;
            delete[] temp; //xoa temp
        }
        ArrayData[length] = data;
        length++;
    };

    void clear()
    {
        length = 0;
    }
};
