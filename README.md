This was a coding assignment give by one of the organisations to test my coding skills.
The purpose of the code is to accept hex, decimal or a text file as input and encode/decode the data as per user selection.
The encoding requirement is:
Accept a signed integer in the 14-bit range [-8192..+8191] and return a 4 character string.
The encoding process is as follows:
1. Add 8192 to the raw value, so its range is translated to [0..16383]1.
2. Pack that value into two bytes such that the most signiﬁcant bit of each is cleared Unencoded intermediate value (as a 16-bit integer):
  00HHHHHH HLLLLLLL  
Encoded value:
  0HHHHHHH 0LLLLLLL  
.
3. Format the two bytes as a single 4-character hexadecimal string and return it.

The decoding requirement is to revert to the 14 bit integer
