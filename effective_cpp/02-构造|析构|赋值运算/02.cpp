#include "iostream"

class Item05
{
public:
    virtual ~Item05();
};

Item05::~Item05()
{
    std::cout << "Item05 destructor is running!" << std::endl;
}

class Item05D: public Item05
{
    ~Item05D() override
    {
        std::cout << "Item05D destructor is running!" << std::endl;
    }
};

int main(int argc, char **argv)
{
    Item05 *item_05 = new Item05D();
    delete item_05;
}