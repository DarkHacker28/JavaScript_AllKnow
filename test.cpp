#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

// Function to toggle valid digits
vector<int> toggle_valid_digits(const map<int, string>& valid_digits, const string& faulty_digit) {
    vector<int> possible_digits;
    // Use iterator-based loop instead of structured bindings
    for (map<int, string>::const_iterator it = valid_digits.begin(); it != valid_digits.end(); ++it) {
        int diff = 0;
        const string& valid = it->second; // Accessing valid string representation
        for (size_t i = 0; i < faulty_digit.size(); ++i) {
            if (faulty_digit[i] != valid[i]) {
                ++diff;
            }
        }
        if (diff == 0 || diff == 1) {
            possible_digits.push_back(it->first); // Accessing digit key
        }
    }
    return possible_digits;
}

// Function to solve the problem
void solve() {
    vector<string> segment_display(3);
    for (int i = 0; i < 3; ++i) {
        cin >> segment_display[i];
    }

    vector<string> faulty_display(3);
    for (int i = 0; i < 3; ++i) {
        cin >> faulty_display[i];
    }

    // Create valid digits mapping
    map<int, string> valid_digits;
    for (int i = 0; i < 10; ++i) {
        string digit_representation;
        for (int j = 0; j < 3; ++j) {
            digit_representation += segment_display[j].substr(i * 3, 3);
        }
        valid_digits[i] = digit_representation;
    }

    // Process faulty display digits
    vector< vector<int> > faulty_number; // Added a space between >> to resolve the issue
    int faulty_length = faulty_display[0].size() / 3;
    for (int i = 0; i < faulty_length; ++i) {
        string faulty_digit;
        for (int j = 0; j < 3; ++j) {
            faulty_digit += faulty_display[j].substr(i * 3, 3);
        }
        vector<int> possible_digits = toggle_valid_digits(valid_digits, faulty_digit);
        if (possible_digits.empty()) {
            cout << "Invalid";
            return;
        }
        faulty_number.push_back(possible_digits);
    }

    // Calculate total sum of all possible numbers
    long long total_sum = 0;
    vector<int> indices(faulty_number.size(), 0);
    while (true) {
        string num;
        for (size_t i = 0; i < faulty_number.size(); ++i) {
            num += to_string(faulty_number[i][indices[i]]);
        }
        total_sum += stoll(num);

        // Move to the next combination
        size_t pos = faulty_number.size();
        while (pos > 0) {
            --pos;
            if (++indices[pos] < static_cast<int>(faulty_number[pos].size())) { // Fixed signed-unsigned comparison
                break;
            }
            indices[pos] = 0;
        }
        if (pos == 0 && indices[0] == 0) {
            break;
        }
    }

    cout << total_sum;
}

int main() {
    solve();
    return 0;
}
