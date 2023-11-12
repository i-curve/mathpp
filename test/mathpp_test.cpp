/* c++
 * @Author: i-curve
 * @Date: 2023-11-12 23:30:39
 * @Last Modified by: i-curve
 * @Name:
 */
#include <cassert>
#include "mathpp/mathpp.hh"

int main() {
    assert(sum(3, 4) == 7);
    assert(sub(5, 3) == 2);
    assert(mul(4, 5) == 20);
    assert(div(9, 3) == 3);
    return 0;
}