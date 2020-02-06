#include <utility>

#include "string"
#include "iostream"

// 使用引用计数实现 shared_ptr
// 1. 需要重载 -> 操作符
// 2. 需要重载 * 操作符

// 记录我在实现过程中犯得错误
// 1. 在使用 explicit smart_ptr(T *obj) 构造器时只初始化了 obj
//    而没有手动的去初始化 reference_count， 违背了 effective c++ 条款 04：
//    确定对象被使用前已经被初始化
// 2. 在实现拷贝构造器和拷贝=时，参数应该为 const smart_ptr<T>& 而不是 const smart_ptr&
// 3. 实现拷贝构造器时，应该通过初始参数列表初始化所有元素

class ReferenceCount
{
private:
    unsigned int _referenceCount{0};
public:
    unsigned int Increment()
    {
        return ++_referenceCount;
    }

    unsigned int Decrement()
    {
        return --_referenceCount;
    }

    unsigned int getReferenceCount() const
    {
        return _referenceCount;
    }
};

template <typename T>
class smart_ptr
{
private:
    T* _obj {nullptr};
    ReferenceCount* reference_count {nullptr};
public:
    smart_ptr() = default;

    explicit smart_ptr(T *obj)
            : _obj(obj),
              reference_count(new ReferenceCount)
    {
        unsigned int cnt = reference_count->Increment();
        std::cout << "Created smart_ptr! Ref count is " << cnt << std::endl;
    }

    smart_ptr(const smart_ptr<T> &rhs)
            : _obj(rhs._obj),
              reference_count(rhs.reference_count)
    {
        unsigned int cnt = reference_count->Increment();
        std::cout << "copy smart_ptr! Ref count is " << cnt << std::endl;
    }

    smart_ptr<T>& operator=(const smart_ptr<T>& rhs)
    {
        T *tmpObj = _obj;
        ReferenceCount *tmpRefCount = reference_count;

        _obj = rhs._obj;
        reference_count = rhs.reference_count;
        rhs.reference_count->Increment();

        unsigned int count = tmpRefCount->Decrement();
        if (count <= 0)
        {
            delete tmpObj;
            delete tmpRefCount;
        }

        std::cout << "copy assignment smart_prt! Ref count is "
                  << reference_count->getReferenceCount() << std::endl;

        return *this;
    }

    ~smart_ptr()
    {
        if (_obj == nullptr)
        {
            return;
        }
        unsigned int cnt = reference_count->Decrement();
        std::cout << "Destroyed smart_ptr! Ref count is " << cnt << std::endl;
        if (cnt > 0)
        {
            return;
        }

        // cnt == 0，执行析构
        delete reference_count;
        delete _obj;

        reference_count = nullptr;
        _obj            = nullptr;
    }

    T& operator*()
    {
        return *_obj;
    }

    T* operator->()
    {
        return _obj;
    }
};

class AirCraft
{
private:
    std::string m_Model;
public:
    AirCraft() :m_Model("Generic Model")
    {
        std::cout << "Generic model aircraft created" << std::endl;
    }

    explicit AirCraft(std::string modelName) : m_Model(std::move(modelName))
    {
        std::cout << "Aircraft type " << m_Model << "is created!" << std::endl;
    }
    void SetAirCraftModel(const std::string& modelName)
    {
        std::cout << "Aircraft model changed from  " << m_Model << " to " << modelName << std::endl;
        m_Model = modelName;
    }
    ~AirCraft()
    {
        std::cout << "Destroying Aircraft of model:" << m_Model << "!" << std::endl;
    }
};
int main()
{
    // Create two aircraft objects.
    smart_ptr<AirCraft> raptorPointer(new AirCraft("F-22 Raptor")); // Ref Count for raptorPointer = 1
    raptorPointer->SetAirCraftModel("B2 Bomber");   // rename the model using pointer access operator
    (*raptorPointer).SetAirCraftModel("B2 Spirit"); // rename the model using the pointer dereference operator
    smart_ptr<AirCraft> hornettPointer(new AirCraft("F-14 Hornet")); // Ref count for hornettPointer = 1
    raptorPointer = hornettPointer; // raptorPointer now points to "F14-Hornett".Ref count for hornett is 2. "F-22 Raptor" is destroyed. Ref count for hornett is 2
    return 0;
}