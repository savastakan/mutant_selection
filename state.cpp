#include "state.h"

void state::to_string() {
	cout << input << "=";
	for (const auto& node : nodes) {
		cout << node.parent << "->" + node.current << ",";
	}
	cout << "\n";

}

