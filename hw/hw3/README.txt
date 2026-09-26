# MyBitManipulation.c

### ToggleBit(int num, int pos)

The code first checks for if the input pos is greater than 31, as there are only 32 bits and indexing starts at 0. If there is, the original number is returned as the position is deemed invalid. If the position is valid, a mask is created by left shifting 1 to the input pos. The mask is applied to the number using the XOR operator, as if the bit is 0 the XOR operator sets it to 1 and if the bit is 1 the XOR operator sets it to 0. 

ToggleBit(0, 3), 8
	This test case is the default provided by the starter zip file.

ToggleBit(5, 33), 5
	This test case tests for if the code properly returns the original number if the given number of positions is greater than the amount of bits.

ToggleBit(0, 31), -2147483648
	This test case tests for if the code is able to toggle the largest possible bit. It will always be printed as a negative number because the toggled bit at the index 31 is also read as the sign bit.

ToogleBit(3, 0), 2
	This testcase tests for if the code is not only able to toggle bits from 0 to 1, also 1 to 0.

### GetMSB(int num)

The code first checks for if the number is negative or 0, as negative numbers will always return 31 and 0 will always return 1. If the number is neither, the code uses a for loop that divides the number by 2 for every loop. The amount of loops is counted with the variable count and represents where the largest bit of the given number is. As the bit index starts at 0, 1 has to be subtracted from the final count for an accurate index.

GetMSB(16), 4
	This test case is the default provided by the starter zip file.

GetMSB(2147483648), 31
	This test case tests for if the code is able to return the index of 2147483648, which is the largest possible representation of a decimal using only one bit in a 32-bit representation.

GetMSB(0), -1
	This is test case tests for if the code is able to return -1 when the special circumstance where the input is 0 is met.

GetMSB(-1), 31
  This test case tests for if the code is able to return the correct index for a negative number, as all negative numbers have a MSB of 31.

### ClearBitRange(int num, int start, int end)

The code starts by checking for any of the 3 special circumstances that can happen, start < 0, end > 31, or start > end. If any of these circumstances are detected, the code returns the original number. If none are true, the code uses a for loop to count how many bits are in the given number. If the amount of bits is less than end - start and start == 0, a 0 is returned because every bit of the number would be cleared. If not, then, for each bit in the target range, a 1 is shifted to the bit position and the NOT operator is used to flip the 1 to a 0 and every 0 to a 1. This gives us a mask that will only interact with the target bit. Using the AND operator on the number and the mask, the target bit is cleared because any (1 | 0) & 0 will be 0. At the end the number is returned.

ClearBitRange(10, -1, 5), 10
  This test case tests for if the code is able to return the original input number when the special circumstance where start < 0 is met.

ClearBitRange(27, 6, 33), 27
  This test case tests for if the code is able to return the original input number when the special circumstance where end > 31 is met.

ClearBitRange(223, 6, 3), 223
  This test case tests for if the code is able to return the original input number when the special circumstance where start > end is met.

ClearBitRange(31, 0, 4), 0
  This test case tests for if the code is able to clear the entire range of a given integer.

### RotateLeft(int num, int d)

The code first checks for if d is 0, if so then nothing needs to be done and the original number is returned. If it's not 0, then the code checks for if d is greater than 32 if so d is set to d %= 32, as rotating left by 35 positions is the same as rotating left by 3 positions. The initial rotation is done through shifting the number d positions left, causing a 0 to be inserted at the end for every bit discarded at the front during the shift. The discarded bits are obtained by shifting num 32 - d times, thus getting only the discarded bits. The two binary numbers are combined with an OR operator, as 0 | (1 | 0) will reflect the second input, in our case the discarded bits. 

RotateLeft(1, 31), 2147483648
  This test case tests for if the code is able to rotate a single bit by the largest possible rotation allowed by the function.

RotateLeft(10, 35), 80
  This test case tests for if the code is able to properly deal with a rotation by a number of bits larger than 31.

RotateLeft(19, 0), 19
  This test case tests for if the code is able to return the original numbers when asked to do a rotation by zero bits.

### SwapOddEvenBits(int num)

The code runs a for loop that increments by 2. The ith bit of the number is obtained through shifting the number right by i positions and using the AND operator. The right shift removes any bits to the right of the ith bit and the AND operator removes any bits to the right of the ith bit. This same process is done to the i+1th bit, so both bits are isolated. The ith bit is then cleared from num through subtraction and the i+1th bit is added in its place, both bits are shifted left by i positions. The same is done for the i+1th bit, with the 1+1th bit shifted left i + 1 positions subtracted from num and the ith bit shifted left i + 1 positions is added to num. This is done for every group of 2 bits in the given number and the final number is returned.

SwapOddEvenBits(127), 127
  This test case tests for if the code is able to return the original number when faced with an integer that is the same after swapping. 

SwapOddEvenBits(2), 1
  This test case tests for if the code is able to do the bare minimum swap between 2 bits.

SwapOddEvenBits(21), 42
  This test case tests for if the code can properly swap multiple groups of bits.

SwapOddEvenBits(0), 0
  This test case tests for if the code is able to deal with the input 0, where there is no swapping necessary.

# Myfloat.c 

This code isolates the sign bit by first masking the char sign-bit with the AND operator and 0x01, which isolates the bit that is then casted to an unsigned int so we can work with it as a binary number. Lastly, it is shifted 31 positions to the left so it sits as the most significant bit of the number. A similar process is done to the exponent, but it is masked with 0xFF because the exponent encompasses the range from bits 31 to 23. The result is shifted 23 positions left, so it's within range. Lastly, the fraction is masked with 0x7FFFFF to obtain bits 22 to 0. With the three portions of the number isolated, they're combined using the OR operator This works because our previous shifting has left all spaces not occupied by relevant bits empty. If the result is equal to 0, the sign pit is set to positive so the result is 0 and not -0.

construct_float_sf(0x00, 0x81, 0x300000), 5.5, 1e-6
  This test case is the default provided by the starter zip file.

construct_float_sf(0x01, 0x81, 0x300000). -5.5, 1e-6
  This test case tests for if the code functions with a signbit larger than 0, outputting a negative number. 

construct_float_sf(0x00, 0x90, 0x7973C0), 255439, 1e-6
  This test case tests for if the code still works with whole numbers.

construct_float_sf(0x01, 0x90, 0x7973C0), -255439, 1e-6
  This test case tests for if the code still works with negative whole numbers.
  
construct_float_sf(0x00, 0x76, 0x299B6F), 0.002588, 1e-6
  This test case tests for if the code still works with numbers that are less than 1.

construct_float_sf(0x10, 0x76, 0x299B6F), -0.002588, 1e-6
  This test case tests for if the code still works with negative numbers that are less than 1.

construct_float_sf(0x00, 0x00, 0x000000), 0, 1e-6
  This test case tests for if the code will work with 0.

construct_float_sf(0x01, 0x00, 0x000000), 0, 1e-6
  This test case tests for if the code will work with a negative 0.

construct_float_sf(0x00, 0x80, 0x490FDB), 3.141593, 1e-6
  This test case tests for if the code can convert the irrational number pi.

construct_float_sf(0x01, 0x80, 0x490FDB), 3.141593, 1e-6
  This test case tests for if the code can convert a negative version of the irrational number pi.

# MyIntegers.c

The code uses an if statement to check whether the user wants to convert from sign/magnitude to 2's complement or 2's complement to sign/magnitude. 
If the user wants to do the former, the code isolates the sign bit by shifting repr right 31 positions. Using the sign bit, the code checks for if the number is negative or positive. If the number is positive there is no need to convert. If the number is negative, repr is shifted right 1 position to remove the sign bit and then shifted left 1 position to reset the bits back to their original position. Then, the mask 0xFFFFFFFF is used with the XOR operator to toggle every bit, flipping them. To make it 2's complement and not 1's complement 1 is added to repr. Lastly, the sign bit is reinstated with the OR operator. I chose not to use the XOR operator, as if addition caused the sign bit to flip then the answer would incorrectly show as positive. The code additionally checks if the input repr is 0x80000000, and if it is 0 is printed and the function ends.
If the user wants the latter, the code first checks if the input is 0x80000000. If it is, undefined is printed. If it isn't, the code isolates the sign bit by shifting repr right 31 positions. Using the sign bit, the code checks for if the number is negative or positive. If the number is negative, repr is shifted right 1 position to remove the sign bit and then shifted left 1 position to reset the bits back to their original position. Then, the mask 0xFFFFFFFF is used with the XOR operator to toggle every bit, flipping them. Lastly, 1 is added to the repr. 

repr_convert('S', '2', 0x80000001)
	This test case is the default provided by the starter zip file.

repr_convert('S', 'S', 0x80000000)
  This test case tests for if the code is able to properly present negative 0, 0x80000000, as 0.

repr_convert('2', 'S', 0x7fffffff)
  This test case tests for if the code is able to properly convert a two's complement number to sign/magnitude representation.

repr_convert('S', '2', 0x7fffffff)
  This test case tests for if the code is able to properly convert from sign/magnitude number to two's complement representation.

repr_convert('F', '2', 0x00394812)
  This test cases tests for if the code is able to properly detect an invalid input in the source_repr.

repr_convert('2', 'F', 0x00394812)
  This test case tests for if the code is able to properly detect an invalid input in the target-repr.

repr_convert('2', '2', 0x59f2ca50)
  This test case tests for if the code is able to properly detect a request to convert from two's complement to two's complement and return the original number.

repr_convert('2', 'S', 0x80000000)
  This test case tests for if the code able to properly detect that converting 0x80000000 from two's complement to sign/magnitude is undefined.

repr_convert('S', 'S', 0x00000000)
  This test case tests for if the code is able to detect a conversion from sign/magnitude to aign/magnitude and returnt he original number.

repr_convert('S','2',0x80000005)
  This test case tests for if the code is able to properly convert a sign/magnitude number to two's complement representation.