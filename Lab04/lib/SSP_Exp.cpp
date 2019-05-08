#include <SSP_Exp.h>

   /// cake recipe to use << operator with SSP_Exp struct, e.g. cout << mySSP_Exp;
   std::ostream& operator<<(std::ostream& os, const SSP_Exp& e)
{
    os << std::endl << "SSPx" << e.repeat << " ALG[ " ;
    for (std::string s : e.algs)
        os << s << " ";
    os << "]"<<std::endl << "siz[ " ;
    for (int i : e.sizes)
        os << i << " ";
    os << "]"<<std::endl << "Dat[ " ;
    for (std::string s : e.data)
        os << s << " ";
    os << "]"<<std::endl ;
    return os;
}
