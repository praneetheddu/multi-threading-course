/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>


int copy_value(int&& val) {
    std::cout << "RValue func called \n";
    val += 8;
    return val;
}

int copy_value(int& val) {
    std::cout << "LValue func called \n";
    val += 8;
    return val;
}


int main()
{
    int a = 8;
    auto value = copy_value(a);
    
    std::cout << "Lvalue call returns = " << value << "\n";
    

    value = copy_value(10);
    
    std::cout << "rvalue literal call returns = " << value << "\n";
    
    
    value = std::move(copy_value(std::move(a)));
    
    std::cout << "rvalue move call returns = " << value << "\n";
    std::cout << "a = " << a << "\n";

    return 0;
}