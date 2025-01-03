/*
A polynomial linked list is a special type of linked list where every node represents a term in a polynomial expression.

Each node has three attributes:

    coefficient: an integer representing the number multiplier of the term. The coefficient of the term 9x4 is 9.
    power: an integer representing the exponent. The power of the term 9x4 is 4.
    next: a pointer to the next node in the list, or null if it is the last node of the list.

For example, the polynomial 5x3 + 4x - 7 is represented by the polynomial linked list illustrated below:

The polynomial linked list must be in its standard form: the polynomial must be in strictly descending order by its power value. Also, terms with a coefficient of 0 are omitted.

Given two polynomial linked list heads, poly1 and poly2, add the polynomials together and return the head of the sum of the polynomials.

PolyNode format:

The input/output format is as a list of n nodes, where each node is represented as its [coefficient, power]. For example, the polynomial 5x3 + 4x - 7 would be represented as: [[5,3],[4,1],[-7,0]].

 

Example 1:

Input: poly1 = [[1,1]], poly2 = [[1,0]]
Output: [[1,1],[1,0]]
Explanation: poly1 = x. poly2 = 1. The sum is x + 1.

Example 2:

Input: poly1 = [[2,2],[4,1],[3,0]], poly2 = [[3,2],[-4,1],[-1,0]]
Output: [[5,2],[2,0]]
Explanation: poly1 = 2x2 + 4x + 3. poly2 = 3x2 - 4x - 1. The sum is 5x2 + 2. Notice that we omit the "0x" term.

Example 3:

Input: poly1 = [[1,2]], poly2 = [[-1,2]]
Output: []
Explanation: The sum is 0. We return an empty list.

 

Constraints:

    0 <= n <= 10^4
    -109 <= PolyNode.coefficient <= 10^9
    PolyNode.coefficient != 0
    0 <= PolyNode.power <= 10^9
    PolyNode.power > PolyNode.next.power

*/

/**
 * Definition for polynomial singly-linked list.
 * struct PolyNode {
 *     int coefficient, power;
 *     PolyNode *next;
 *     PolyNode(): coefficient(0), power(0), next(nullptr) {};
 *     PolyNode(int x, int y): coefficient(x), power(y), next(nullptr) {};
 *     PolyNode(int x, int y, PolyNode* next): coefficient(x), power(y), next(next) {};
 * };
 */

class Solution {
public:
    PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2) {
        //return by_vector(poly1, poly2);
        return by_two_ptr(poly1, poly2);
    }
private:
    PolyNode* by_two_ptr(PolyNode* poly1, PolyNode* poly2) {
        PolyNode* p1 = poly1;
        PolyNode* p2 = poly2;
        PolyNode* dummy = new PolyNode();
        PolyNode* curr = dummy;

        while (p1 != nullptr && p2 != nullptr) {

            if (p1->power == p2->power) {
                if (p1->coefficient + p2->coefficient != 0) {
                    curr->next = new PolyNode(p1->coefficient + p2->coefficient, p1->power);
                    curr = curr->next;
                }

                p1 = p1->next;
                p2 = p2->next;
            } else if (p1->power > p2->power) {
                curr->next = p1;
                p1 = p1->next;
                curr = curr->next;

            } else {
                curr->next = p2;
                p2 = p2->next;
                curr = curr->next;
            }
        }

        if (p1 == nullptr) {
            curr->next = p2;
        } else {
            curr->next = p1;
        }

        return dummy->next;
    }

    PolyNode* by_vector(PolyNode* poly1, PolyNode* poly2) {
        std::vector<std::pair<int, int>> v;

        while (poly1 != nullptr && poly2 != nullptr) {

            if (poly1->power > poly2->power) {
                v.push_back({poly1->coefficient, poly1->power});
                poly1 = poly1->next;

            } else if (poly1->power < poly2->power) {
                v.push_back({poly2->coefficient, poly2->power});
                poly2 = poly2->next;

            } else {

                int coe = poly1->coefficient + poly2->coefficient;
                if (coe != 0) {
                    v.push_back({coe, poly1->power});
                }
                poly1 = poly1->next;
                poly2 = poly2->next;
            }
        }

        while (poly1 != nullptr) {
            v.push_back({poly1->coefficient, poly1->power});
            poly1 = poly1->next;
        }

        while (poly2 != nullptr) {
            v.push_back({poly2->coefficient, poly2->power});
            poly2 = poly2->next;
        }

        if (v.empty()) {
            return {};
        }

        PolyNode* head = new PolyNode(v[0].first, v[0].second);
        PolyNode* now = head;
        for (int i = 1; i < v.size(); ++i) {
            now->next = new PolyNode(v[i].first, v[i].second);
            now = now->next;
        }

        return head;
    }
};