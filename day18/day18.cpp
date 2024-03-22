// day18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include<format>

//faces of cubes (sidor på kub)


// Customized hash function for std::vector<float>
struct VectorHash {
	size_t operator()(const std::vector<int>& vec) const {
		size_t n = vec.size();
		for (const float& v : vec) {
			n ^= std::hash<float>{}(v)+0x9e3779b9 + (n << 6) + (n >> 2);
		}
		return n;
	}
};


int calcSurfaceArea(const std::vector<std::vector<int>> CORNERS, const std::vector<std::vector<int>> inputData) {

	int surfaceArea = 0;
	// Calculate number of exposed for each cube
	for (auto side : inputData) {
		int faces = 0;
		for (auto corner_ : CORNERS) {
			std::vector<int> value = { side[0] + corner_[0], side[1] + corner_[1], side[2] + corner_[2] };
			if (std::find(inputData.begin(), inputData.end(), value) == inputData.end()) {
				faces++; // count as exposed face of no neighbor cube is found
			}
		}
		surfaceArea += faces;
	}
	return surfaceArea;
}


void display(int area) {
	std::cout << std::format("The surface area if the scanned lava droplet is: {}\n", area);
}


int main() {


	const std::vector<std::vector<int>> CORNERS = { {1,0,0},
													{0,1,0},
													{0,0,1},
													{-1,0,0},
													{0,-1,0},
													{0,0,-1} };

	const std::vector<std::vector<int>> inputData = { {2,2,2},
												{1,2,2},
												{3,2,2},
												{2,1,2},
												{2,3,2},
												{2,2,1},
												{2,2,3},
												{2,2,4},
												{2,2,6},
												{1,2,5},
												{3,2,5},
												{2,1,5},
												{2,3,5} };


	int area = calcSurfaceArea(CORNERS, inputData);
	display(area);

	return 0;
}
