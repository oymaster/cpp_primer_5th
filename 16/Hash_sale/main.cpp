#include <unordered_map>
#include <iostream>
#include <string>
#include "Sales_data.h"
#include <unordered_set>

namespace std {
    template <>
    struct hash<Sales_data> {
        typedef size_t result_type;
        typedef Sales_data argument_type;
        size_t operator()(const Sales_data& s) const {
            return hash<std::string>()(s.bookNo) ^
                   hash<unsigned>()(s.units_sold) ^
                   hash<double>()(s.revenue);
        }
    };
}

int main() {
    std::unordered_map<Sales_data, double> sales_map;

    Sales_data item1("12345", 10, 100.0);
    Sales_data item2("67890", 20, 200.0);

    sales_map[item1] = 100.0;
    sales_map[item2] = 200.0;

    std::cout << "Revenue for item1: " << sales_map[item1] << std::endl;
    std::cout << "Revenue for item2: " << sales_map[item2] << std::endl;

    std::unordered_multiset<Sales_data>st;
    st.insert(item1);
    st.insert(item2);
    for(auto &i :st){
        std::cout<<i<<"\n";
    }

    return 0;
}
