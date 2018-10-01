/**
 * CS 2110 Fall 2018 HW2
 * Part 2 - Coding with bases
 *
 * @author Abhinav Tirath
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, else-if statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum. Boolean
 *   expressions outside of if-statements, else-if statements and ternary
 *   expressions do not count toward this sum either.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt.
 * - You may declare exactly one String variable each in intToBinaryString and
 *   and intToHexString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int conversion = 0;
        for (int i = 0; i < binary.length(); i++) {
            conversion = conversion << 1;
            if (binary.charAt(i) == '1') {
                conversion = conversion + 0x1;
            }
        }
        return conversion;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("123"); // => 123
     *
     * You may use multiplication, division, and modulus in this method.
     */
    public static int decimalStringToInt(String decimal)
    {
        int conversion = 0;
        int multiplier = 1;
        for (int i = decimal.length() - 1; i >= 0 ; i--) {
            conversion += (decimal.charAt(i) - 48) * multiplier;
            multiplier *= 10;
        }
        return conversion;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     * The input string will only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("A6"); // => 166
     */
    public static int hexStringToInt(String hex)
    {
        int conversion = 0;
        for (int i = 0; i < hex.length(); i++) {
            char hexDigit = hex.charAt(i);
            conversion = conversion << 4;
            if (hexDigit > 58) {
                int adding = (hexDigit - 65) + 10;
                conversion = conversion | adding;
            } else {
                conversion = conversion | (hex.charAt(i) - 48);
            }

        }
        return conversion;
    }

    /**
     * Convert a int into a String containing ASCII characters (in binary).
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToBinaryString(7); // => "111"
     *
     * You may declare one String variable in this method.
     */
    public static String intToBinaryString(int binary)
    {
        String conversion = "";
        for (int i = 31; i >= 0; i--) {
             if ((binary & (0x1 << i)) == 0) {
                 if (conversion != "" || i == 0) {
                     conversion += 0;
                 }
             } else {
                 conversion += 1;
             }
        }
        return conversion;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hexadecimal).
     * The output string should only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToHexString(166); // => "A6"
     *
     * You may declare one String variable in this method.
     */
    public static String intToHexString(int hex)
    {
        String conversion = "";
        for (int i = 28; i >= 0; i -= 4) {
            int idk = ((hex & (0xF << i)) >> i);
            if (idk > 9) {
                char digit = (char) ('A' + idk - 10);
                conversion += digit;
            } else {
                char digit = (char) ('0' + idk);
                if (digit == '0' && conversion == "" && i != 0) {

                } else {
                    conversion += digit;
                }

            }
        }

        return conversion;
    }
}
