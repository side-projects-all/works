/*
Given the radius and the position of the center of a circle, implement the function randPoint which generates a uniform random point inside the circle.

Implement the Solution class:

    Solution(double radius, double x_center, double y_center) initializes the object with the radius of the circle radius and the position of the center (x_center, y_center).
    randPoint() returns a random point inside the circle. A point on the circumference of the circle is considered to be in the circle. The answer is returned as an array [x, y].

 

Example 1:

Input
["Solution", "randPoint", "randPoint", "randPoint"]
[[1.0, 0.0, 0.0], [], [], []]
Output
[null, [-0.02493, -0.38077], [0.82314, 0.38945], [0.36572, 0.17248]]

Explanation
Solution solution = new Solution(1.0, 0.0, 0.0);
solution.randPoint(); // return [-0.02493, -0.38077]
solution.randPoint(); // return [0.82314, 0.38945]
solution.randPoint(); // return [0.36572, 0.17248]

 

Constraints:

    0 < radius <= 10^8
    -10^7 <= x_center, y_center <= 10^7
    At most 3 * 104 calls will be made to randPoint.


*/

class Solution {
public:
    Solution(double radius, double x_center, double y_center) {
        rad = radius;
        xc = x_center;
        yc = y_center;
    }
    
    vector<double> randPoint() {
        double x0 = xc - rad;
        double y0 = yc - rad;

        while (true) {
            double xg = x0 + uni(rng) * 2 * rad;
            double yg = y0 + uni(rng) * 2 * rad;

            if (std::sqrt(std::pow((xg - xc), 2) + std::pow((yg - yc), 2)) <= rad) {
                return {xg, yg};
            }
        }
    }
private:
    double rad;
    double xc;
    double yc;
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> uni{0, 1};

};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */