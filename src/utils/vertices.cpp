#include <array>
#include <iostream>

using namespace std;

namespace utils::vertex {
    template<size_t n, size_t n_attr, size_t offset>
    array<float, n_attr*n> getAttributes(const array<float, n>& data){
        array<float, n_attr*n> attribute;
        int stride = 8;
        for (int i=0, cont=0, j=offset; j < data.size()-offset; i++, cont++, j++) {
            if (cont < n_attr) {
                cout << data[j] << " | ";
                attribute[i] = data[j];
            }
            else {
                cont = -1;
                j += (stride-n_attr-1);
            }
        }
        cout << endl;
    }
}