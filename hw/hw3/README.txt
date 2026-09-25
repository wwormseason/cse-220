# MyBitManipulation.c

### ToggleBit(int num, int pos)

ToggleBit(0, 3), 8

	This test case is the default provided by the starter zip file.

ToggleBit(5, 33), 5

	This test case tests for if the code properly returns the original number if the given number of positions is greater thant he amount of bits.

ToggleBit(0, 31), 2147483648

	This test case tests for if the code is able to toggle the largest possible bit without flipping signs or overflowing.

ToogleBit(3, 0), 2

	This testcase tests for if the code is not only able to toggle bits from 0 to 1, also 1 to 0.

### GetMSB(int num)

GetMSB(16), 4

	This test case is the default provided by the starter zip file.

GetMSB(2147483648), 31

	This is test case tests for if the code is able to return the index of 2147483648, which is the largest possible representation of a decimal using only one bit in a 32-bit representation.

GetMSB(0), -1

	This is test case tests for if the code is able to return -1 when the special circumstace where the input is 0 is met.

GetMSB(1), 1
  This is test case tests for if the code is able to return the index of 1, which is the smallest possible representation of a decimal using only one bit in a 32-bit representation.

### ClearBitRange(int num, int start, int end)

ClearBitRange(10, -1, 5), 10
  This test case tests for if the code is able to return the original input number when the special circumstance where start < 0 is met.

ClearBitRange(27, 6, 33), 27
  This test case tests for if the code is able to return the original input number when the special circumstance where end > 31 is met.

ClearBitRange(223, 6, 3), 223
  This test case tests for if the code is able to return the original input number when the special circumstance where start > end is met.

ClearBitRange(31, 0, 4), 0
  This test case tests for if the code is able to clear the entire range of a given integer.

### RotateLeft(int num, int d)

RotateLeft(1, 31), 2147483648
  This test case tests for if the code is able to rotate a single bit by the largest possible rotation allowed by the function.

RotateLeft(10, 35), 80
  This test case tests for if the code is able to properly deal with a rotation by a number of bits larger than 31.

RotateLeft(19, 0), 19
  This test case tests for if the code is able to return the original numebrs when, asked to do a rotation by zero bits.

### SwapOddEvenBits(int num)

SwapOddEvenBits(127), 127
  This test case tests for if a the code is able to return the original number when faced with an integer that is the same after swapping. 

SwapOddEvenBits(2), 1
  This test case tests for if the code is able to do the bare minimum swap between 2 bits.

SwapOddEvenBits(21), 42
  This test case tests for if the code can properly swap multiple groups of bits.

SwapOddEvenBits(0), 0
  This test case tests for if the code is able to deal with the input 0, where there is no swapping necessary.

# Myfloat.c 

### test_float.c 

construct_float_sf(0x00, 0x81, 0x300000), 5.5, 1e-6
  This test case is the default provided by teh starter zip file.

construct_float_sf()
test