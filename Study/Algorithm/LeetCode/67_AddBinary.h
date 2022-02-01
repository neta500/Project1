#pragma once
#include <string>

// string binary ´õÇÏ±â
// "11" + "1" = "100"
// "1010" + "1011" = "10101"

class Solution {
public:
    std::string addBinary(std::string a, std::string b) {         
        int carry = 0;
        std::string result;

        int a_index = a.size() - 1;
        int b_index = b.size() - 1;

        while (a_index >= 0 || b_index >= 0)
        {
            int a_int = 0;
            int b_int = 0;

	        if (a_index >= 0)
	        {
                a_int = std::stoi(std::string{ a[a_index] });
                a_index--;
	        }

            if (b_index >= 0)
            {
                b_int = std::stoi(std::string{ b[b_index] });
                b_index--;
            }

            if (a_int + b_int == 2)
            {
                if (carry == 1)
                {
                    result += "1";
                }
                else
                {
                    result += "0";
                }

                carry = 1;
            }

            if (a_int + b_int == 1)
            {
                if (carry == 1)
                {
                    result += "0";
                }
                else
                {
                    result += "1";
                    carry = 0;
                }
            }

            if (a_int + b_int == 0)
            {
                if (carry == 1)
                {
                    result += "1";
                    carry = 0;
                }
                else
                {
                    result += "0";
                }
            }
        }

        if (carry == 1)
        {
            result += "1";
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
};