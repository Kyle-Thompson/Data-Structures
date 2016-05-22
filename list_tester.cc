#include <iosteam>
#include "list.h"

using namespace std;

int main() {
	list<int> ll {11, 22, 33, 44, 55, 66, 77};

	for (auto it = ll.cbegin(); it != ll.cend(); ++it) cout << *it << "\n";
}
