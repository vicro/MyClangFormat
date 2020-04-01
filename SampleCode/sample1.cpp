/* =============================================================================
NAMED PARAMETER IDIOM
A way of having named parameters for constructing an object in C++
http://www.cs.technion.ac.il/users/yechiel/c++-faq/named-parameter-idiom.html
==============================================================================*/

#include <iostream>

using namespace std;


//This macro helps us declare a named parameter
// setter function + storage
#define DECL_PARAM(T, VAR, DEFAULT)                              \
                    auto& VAR(T v) { _##VAR = v; return *this; } \
                    T _##VAR = DEFAULT

//<! Forward declarations
class WidgetCreate;
class Widget;

void SuperLongFunctionName(int argument1, int argument2, int argument3, int argument4)
{

}

int main()
{
    int mySuperLongVariableNameThatIsTooVerbose = 10;
    SuperLongFunctionName(mySuperLongVariableNameThatIsTooVerbose, 
        mySuperLongVariableNameThatIsTooVerbose, 1, mySuperLongVariableNameThatIsTooVerbose);

    mySuperLongVariableNameThatIsTooVerbose = mySuperLongVariableNameThatIsTooVerbose + 145 - mySuperLongVariableNameThatIsTooVerbose;

    cout<<"Hello World\n";
    
    //Construct object with named parameter idiom
    // parameters are optional, and can come in any order
    Widget w = WidgetCreate("My Widget")
                .index(10)
                .active(true)
                .speed(10.f);
    Widget x = WidgetCreate("Another Widget")
                .speed(20.f)
                .active(false);

    // The following code will not be formatted
    // clang-format off
    Widget y = WidgetCreate("My Widget again")
                .index(10)
                .active(true)
                .speed(10.f);
    Widget z = WidgetCreate("Another Widget again")
                .speed(20.f)
                .active(false);
    // clang-format on

    cout << "Name " << w.getName() << "\n"; //Print out the name
    cout << "Index " << w.getIndex() << "\n"; //Print out the index
    cout << "Active " << w.getActive() << "\n"; //Print out if Active

    int x = 10;
    switch(x)
    {
        case 1: break;
        case 2:
            cout << "2";
            break;
        case 3:
            break;
        default: break;
    }

    if(x < 1) return 1;

    auto lambda = [](int a) {};
    auto lambda2 = [](int a) {
        return a;
    };
    sort(a.begin(), a.end(), ()[] { return x < y; });
    sort(a.begin(), a.end(), lambda2);

    while(x < 10) x++;

    return 0;
}








/*..........................................*/


class WidgetCreate
{
public:
    // Constructor (with required parameters)
    WidgetCreate(const char* name)
        : _name(name)
    {}

    // Declare optional parameter setters
    
    // With helper macro we can quickly declare 
    // setter, variable and default value
    DECL_PARAM(float, speed,  0.f);
    DECL_PARAM(bool,  active, true);

    //Declare manually
    auto& name(const char* v) { _name = v;   return *this; }
    auto& index(int v)        { _index = v;  return *this; }
    
    const char* _name   = nullptr;
    int         _index  = 0;
};

/*..........................................*/

class Widget
{
public:
    //Constructor with parameters object
    Widget(WidgetCreate parameters)
        : _name  (parameters._name)
        , _index (parameters._index)
        , _active(parameters._active)
        , _speed (parameters._speed)
    {}

    const char* getName()   const { return _name;   }
    int         getIndex()  const { return _index;  }
    bool        getActive() const { return _active; }

private:
    const char* _name = nullptr;
    int _index  = 0;
    bool _active = false;
    float _speed  = 1.f;
};