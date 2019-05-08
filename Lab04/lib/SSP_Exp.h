#ifndef SSP_EXP_DESCRIPTION
#define SSP_EXP_DESCRIPTION


#include <ostream>
#include <vector>

struct SSP_Exp {
    SSP_Exp(std::vector<std::string> _algs, 
            std::vector<int> _sizes,
            std::vector<std::string> _data, int _rep) : algs(_algs), sizes(_sizes), data(_data), repeat(_rep) { }
    
    std::vector<std::string> algs;
    std::vector<int> sizes;
    std::vector<std::string> data;
    int repeat;
    
    
}; // class

std::ostream& operator<<(std::ostream& os, const SSP_Exp& e);


#endif
